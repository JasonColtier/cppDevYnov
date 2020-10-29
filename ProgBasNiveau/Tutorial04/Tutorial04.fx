//--------------------------------------------------------------------------------------
// File: Tutorial04.fx
//
// Copyright (c) Microsoft Corporation. All rights reserved.
//--------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------
// Constant Buffer Variables
//--------------------------------------------------------------------------------------
cbuffer ConstantBuffer : register( b0 )
{
	matrix World;
	matrix View;
	matrix Projection;
}

//--------------------------------------------------------------------------------------
struct VS_OUTPUT
{
    float4 Pos 			: SV_POSITION;
	float4 WPos 		: WORLDPOS;
    float4 Color 		: COLOR0;
	float3 WNormal 		: NORMAL;
};



//--------------------------------------------------------------------------------------
// Vertex Shader
//--------------------------------------------------------------------------------------
VS_OUTPUT VS( float4 Pos : POSITION, float4 Color : COLOR, float3 Normal : NORMAL, float2 uv : TEXCOORD)
{
    VS_OUTPUT output = (VS_OUTPUT)0;
	
 	output.WPos 	= mul(Pos, World);
	output.WNormal = mul(normalize(Normal), World);
	
    output.Pos = mul( output.WPos, View );
    output.Pos = mul( output.Pos, Projection );
	
	output.Color = Color;
	
    return output;
}

struct LightContribution
{
	float4 Diffuse;
	float4 Specular;
};

float GetLightAttenuation(float Distance)
{
	float attenuation = 1.0f/max(0.001f,Distance* Distance);
	return attenuation;
}

LightContribution Phong(float3 View, float3 InputNormalW, float3 LightDirW, float Distance, float SpecularPower)
{
	LightContribution res = (LightContribution) 0;
	
	float attenuation = GetLightAttenuation(Distance);	

	float NDotL = saturate(dot(LightDirW, InputNormalW));
	
	float3 R = normalize(LightDirW - 2 * NDotL * InputNormalW);
	
	res.Diffuse = attenuation * NDotL; //dépend de la normale de la surface et de sa distance à la source de lumière
	res.Specular = attenuation * pow(saturate(dot(View, R)), SpecularPower); // vecteur réflexion
	return res;
}

LightContribution PhongAngle(float3 View, float3 InputNormalW, float3 LightDirW, float SpotRadius, float3 SpotLightDir, float Distance, float SpecularPower)
{
	LightContribution res = (LightContribution)0;//la light contribution globale

	float attenuation = GetLightAttenuation(Distance);//je calcule la luminosité de mon pixel en fonction de sa distance à la source lumineuse

	attenuation = attenuation * dot(LightDirW, SpotLightDir);//ce dot correspond juste à un cache : le rapport entre le vecteur direction vers ma lumière et l'angle de mon spot

	//trouver la formule mathématique pour déterminer le vecteur direction à un angle par rapport à un autre vecteur
	//multiplier par le dot product de ce vecteur

	float NDotL = saturate(dot(LightDirW, InputNormalW));

	float3 R = normalize(LightDirW - 2 * NDotL * InputNormalW);


	res.Diffuse = attenuation * NDotL; //dépend de la normale de la surface et de sa distance à la source de lumière
	res.Specular = attenuation * pow(saturate(dot(View, R)), SpecularPower); // vecteur réflexion
	return res;
}

LightContribution PointLight_Phong(float3 View, float3 InputPosW, float3 InputNormalW, float3 LightPosW, float SpecularPower)
{
	LightContribution res = (LightContribution) 0;
	
	float3 direction = LightPosW - InputPosW;
	float distance = length(direction);
	
	res = Phong(View, InputNormalW, direction, distance, SpecularPower);
	
	return res;
}

LightContribution DirectionalLight_Phong(float3 View, float3 InputNormalW, float3 LightDirW, float SpecularPower)
{
	LightContribution res = (LightContribution) 0;
	
	res = Phong(View, InputNormalW, LightDirW, 1.0f, SpecularPower);

	return res;
}

LightContribution SpotLight_Phong(float3 View, float3 InputPosW, float3 InputNormalW, float3 LightPosW, float3 SpotLightDir, float SpecularPower, float Radius) {
	
	LightContribution res = (LightContribution)0;

	//float3 direction = LightPosW - InputPosW;//l'orientation de mon vertex du vertex shader vers la lumière  (B-A) 
	float3 direction = LightPosW - InputPosW;//l'orientation de mon vertex du vertex shader vers la lumière
	float distance = length(direction);



	res = PhongAngle(View, InputNormalW, direction,Radius,SpotLightDir,distance, SpecularPower);

	return res;
}

float3 GetViewVector(float4x4 ViewMatrix)
{
	float3 v = mul(float4(0.0f, 0.0f, 1.0f, 0), ViewMatrix).xyz;
	return v;
}

float3 GetSunDirection()
{
	return normalize(float3(1.0f, 1.0f, -1.0f));
}

float3 GetPointLightPos()
{
	return float4(1.0f, 2.0f, -1.0f, 1.0f);
}

float3 GetSpotLightPos()
{
	return float4(-3.f, 1.0f, 3.0f, 1.0f);//je place mon spot en haut à gauche de mon image
}

float3 GetSpotLightDir()
{
	//return normalize(float3(1.0f, 1.0f, -1.0f));
	return normalize(float3(-1.0f, 1.0f, 1.0f));
}

float4 GetAmbientColor()
{
	return float4(0.001f, 0.001f, 0.001f, 1.0f);
}

float4 AccumulateLightContrib(LightContribution contrib[3],float4 LightColors[3])
{
	float4 color = GetAmbientColor();
	for(int i = 1;i<3;++i)
	{
		color = color + contrib[i].Diffuse * LightColors[i] + contrib[i].Specular * LightColors[i];
	}
	return color;
}

//--------------------------------------------------------------------------------------
// Pixel Shader
//--------------------------------------------------------------------------------------
float4 PS(VS_OUTPUT input) : SV_Target
{
	float3 WNormal = normalize(input.WNormal);

	float MaterialSpecPower = 70;
	
	float4 color = GetAmbientColor();
	
	LightContribution allLights[3];
	float4 allLightColors[3];
	
	allLightColors[0] = float4(1,1,1,1);//ma lumière ! 
	allLightColors[1] = float4(1,0,0,1);
	allLightColors[2] = float4(0,1,1,1);
		
	//Compute Lighting
	allLights[0] = DirectionalLight_Phong(GetViewVector(View), WNormal, GetSunDirection(), MaterialSpecPower);
	allLights[1] = PointLight_Phong(GetViewVector(View), input.WPos, WNormal, GetPointLightPos(), MaterialSpecPower);
	allLights[2] = SpotLight_Phong(GetViewVector(View), input.WPos, WNormal, GetSpotLightPos(), GetSpotLightDir(), MaterialSpecPower, 1);

	//écrire spotligh_phong qui prend en param la view, la position la direction 
	
	// Accumulate and return lighting
	return AccumulateLightContrib(allLights,allLightColors) * input.Color;
}
