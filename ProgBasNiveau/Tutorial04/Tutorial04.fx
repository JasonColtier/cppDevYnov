//--------------------------------------------------------------------------------------
// File: Tutorial04.fx
//
// Copyright (c) Microsoft Corporation. All rights reserved.
//--------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------
// Constant Buffer Variables
//--------------------------------------------------------------------------------------
cbuffer ConstantBuffer : register(b0)//indique dans quel point de départ va se trouver ce CB
{
	matrix World;
	matrix View;
	matrix Projection;
}

struct Light // quelle est le pramamètre qui définit map lumière ?
{
	float4 mPosition;

	float4 mDirection;

	float4 mColor;

	float mAngle;

	int mType;


};

cbuffer ConstantBufferLights : register(b1)
{
	Light lights[2];
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
VS_OUTPUT VS(float4 Pos : POSITION, float4 Color : COLOR, float3 Normal : NORMAL, float2 uv : TEXCOORD)
{
	VS_OUTPUT output = (VS_OUTPUT)0;

	output.WPos = mul(Pos, World);
	output.WNormal = mul(normalize(Normal), World);

	output.Pos = mul(output.WPos, View);
	output.Pos = mul(output.Pos, Projection);

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
	float attenuation = 1.0f / max(0.001f, Distance * Distance);
	return attenuation;
}

LightContribution Phong(float3 View, float3 InputNormalW, float3 LightDirW, float Distance, float SpecularPower)
{
	LightContribution res = (LightContribution)0;

	float attenuation = GetLightAttenuation(Distance);

	float NDotL = saturate(dot(LightDirW, InputNormalW));

	float3 R = reflect(normalize(-LightDirW), normalize(InputNormalW)); // normalize(LightDirW - 2 * NDotL * InputNormalW);

	res.Diffuse = attenuation * NDotL; //dépend de la normale de la surface et de sa distance à la source de lumière
	res.Specular = attenuation * pow(saturate(dot(View, R)), SpecularPower); // vecteur réflexion
	return res;
}

LightContribution PhongAngle(float3 View, float3 InputNormalW, float3 LightDirW, float SpotRadius, float3 SpotLightDir, float Distance, float SpecularPower)
{
	LightContribution res = (LightContribution)0;//la light contribution globale

	float attenuation = GetLightAttenuation(Distance);//je calcule la luminosité de mon pixel en fonction de sa distance à la source lumineuse
	attenuation *= dot(SpotLightDir, LightDirW);

	float NDotL = saturate(dot(LightDirW, InputNormalW));
	float3 R = normalize(LightDirW - 2 * NDotL * InputNormalW);

	res.Diffuse = attenuation * NDotL; //dépend de la normale de la surface et de sa distance à la source de lumière
	res.Specular = attenuation * pow(saturate(dot(View, R)), SpecularPower); // vecteur réflexion
	return res;
}

LightContribution PointLight_Phong(float3 View, float3 InputPosW, float3 InputNormalW, float3 LightPosW, float SpecularPower)
{
	LightContribution res = (LightContribution)0;

	float3 direction = LightPosW - InputPosW;
	float distance = length(direction);

	res = Phong(View, InputNormalW, direction / max(0.001, distance), distance, SpecularPower);

	return res;
}

LightContribution DirectionalLight_Phong(float3 View, float3 InputNormalW, float3 LightDirW, float SpecularPower)
{
	LightContribution res = (LightContribution)0;

	res = Phong(View, InputNormalW, normalize(LightDirW), 1.0f, SpecularPower);

	return res;
}

LightContribution SpotLight_Phong(float3 View, float3 InputPosW, float3 InputNormalW, float3 LightPosW, float3 SpotLightDir, float SpecularPower, float Radius) {

	LightContribution res = (LightContribution)0;

	float3 direction = LightPosW - InputPosW;//l'orientation de mon vertex du vertex shader vers la lumière
	float distance = length(direction);

	res = PhongAngle(View, InputNormalW, direction, Radius, SpotLightDir, distance, SpecularPower);

	return res;
}

float3 GetViewVector(float4x4 ViewMatrix)
{
	float3 v = mul(float4(0.0f, 0.0f, 1.0f, 0), transpose(ViewMatrix)).xyz;
	return -v;
}

float3 GetSunDirection()
{
	return normalize(float3(1.0f, -1.0f, 1.0f));
}

float3 GetPointLightPos()
{
	return float3(2.0f, 2.0f, -1.0f);
}

float3 GetSpotLightPos()
{
	return float3(-2.0f, 2.0f, 0.0f);//je place mon spot en haut à gauche de mon image
}

float3 GetSpotLightDir()
{
	return normalize(float3(-3.5f, -1.0f, -3.0f));
}

float4 GetAmbientColor()
{
	return float4(0.001f, 0.001f, 0.001f, 1.0f);
}

float4 AccumulateLightContrib(LightContribution contrib[2])
{
	float4 color = GetAmbientColor();
	for (int i = 0; i < 2; ++i)
	{
		color = color + contrib[i].Diffuse * lights[i].mColor + contrib[i].Specular * lights[1].mColor;
	}
	return color;
}

//--------------------------------------------------------------------------------------
// Pixel Shader
//--------------------------------------------------------------------------------------
float4 PS(VS_OUTPUT input) : SV_Target
{
	float3 WNormal = normalize(input.WNormal);

	float MaterialSpecPower = 10;//influence le calcul de la speculaire. plus il est élevé, plus le mat va parraitre lisse et brillant, à l'inverse = rugeux

	LightContribution allLights[2];

	for (int i = 0; i < 2; ++i)
	{
		if (lights[i].mType == 1) {//dir
			allLights[i] = DirectionalLight_Phong(GetViewVector(View), WNormal, lights[i].mDirection, MaterialSpecPower);
		}
		if (lights[i].mType == 2) {//spot
			allLights[i] = SpotLight_Phong(GetViewVector(View), input.WPos, WNormal, lights[i].mPosition, lights[i].mDirection, MaterialSpecPower, lights[i].mAngle);
		}
		if (lights[i].mType == 3) {//point
			allLights[i] = PointLight_Phong(GetViewVector(View), input.WPos, WNormal, lights[i].mPosition, MaterialSpecPower);
		}
	}

	//Compute Lighting
	

	//allLights[1] = PointLight_Phong(GetViewVector(View), input.WPos, WNormal, GetPointLightPos(), MaterialSpecPower);
	//allLights[2] = SpotLight_Phong(GetViewVector(View), input.WPos, WNormal, mPosition[2], mDirection[2], MaterialSpecPower,30);


	//passer get sun direction, point light pos en constante et les envoyer au shader



	// Accumulate and return lighting
	return AccumulateLightContrib(allLights) * input.Color;
}
