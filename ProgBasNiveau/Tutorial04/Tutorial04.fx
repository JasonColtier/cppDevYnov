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
	float ObjectSpecular;
	
	//les mats peuvent aller dans un constant buffer séparé
	//
}

struct Light // quelle est le pramamètre qui définit map lumière ?
{
	float4 mPosition;

	float4 mDirection;

	float4 mColor;

	float mAngle;

	int mType;


};

//b1 pour accéder au deuxième slot du constant buffer, il faut que ce soit raccord avec le VSSetConstantBuffer du cpp
cbuffer ConstantBufferLights : register(b1)
{
	Light lights[3];
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

	output.Color = Color;//vertex color

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

LightContribution PhongAngle(float3 View, float3 InputNormalW,float3 InputPosW, float3 LightDirW, float SpotRadius, float3 SpotLightDir, float Distance, float SpecularPower)
{
	LightContribution res = (LightContribution)0;
    
    float attenuation = GetLightAttenuation(Distance);

    //http://www.ozone3d.net/tutorials/glsl_lighting_phong_p3.php
    float3 L = normalize(LightDirW);//vecteur de mon point vers la lumière
	float3 D = normalize(SpotLightDir);//la direction de mon spot

    float radAngle = SpotRadius/2 * 3.14 / 180;//on travaille en Radians !

      //affiche un spot
    if( dot(-L, D) > cos(radAngle) )//si le
    {
    
        float3 N = normalize(InputNormalW);

        res.Diffuse = 1; //dépend de la normale de la surface et de sa distance à la source de lumière
                res.Specular = 1; // vecteur réflexion
        float NDotL = saturate(dot(LightDirW, InputNormalW));
            
        float3 R = reflect(normalize(-LightDirW), normalize(InputNormalW)); // normalize(LightDirW - 2 * NDotL * InputNormalW);
            
        res.Diffuse = attenuation * NDotL ; //dépend de la normale de la surface et de sa distance à la source de lumière
        res.Specular = attenuation * pow(saturate(dot(View, R)), SpecularPower); // vecteur réflexion
        
    }	
    
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

	res = PhongAngle(View, InputNormalW,InputPosW, direction, Radius, SpotLightDir, distance, SpecularPower);

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
//	return normalize(float3(-3.5f, -1.0f, -3.0f));
}

float4 GetAmbientColor()
{
	return float4(0.001f, 0.001f, 0.001f, 1.0f);
}

float4 AccumulateLightContrib(LightContribution contrib[3], float4 objectColor)//objectColor correspond à la couleur de mon objet (les vertex)
{
	float4 color = GetAmbientColor();
	
    //problème : la speculaire devient colorée
	
	for (int i = 0; i < 3; ++i)
	{
	    // comment faire en sorte que les couleurs des lights s'additionnent correctement avec celles des matériaux ?
		float4 coloredLightByObject = lights[i].mColor + objectColor;
		color = color + contrib[i].Diffuse * coloredLightByObject + contrib[i].Specular * lights[i].mColor;
	}
	return color;
}

//--------------------------------------------------------------------------------------
// Pixel Shader
//--------------------------------------------------------------------------------------
float4 PS(VS_OUTPUT input) : SV_Target
{
	float3 WNormal = normalize(input.WNormal);

//	float MaterialSpecPower = 1;//influence le calcul de la speculaire. plus il est élevé, plus le mat va parraitre lisse et brillant, à l'inverse = rugeux
	float MaterialSpecPower = ObjectSpecular;//influence le calcul de la speculaire. plus il est élevé, plus le mat va parraitre lisse et brillant, à l'inverse = rugeux

	LightContribution allLights[3];
	

	for (int i = 0; i < 3; ++i)
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


	// Accumulate and return lighting
//	return AccumulateLightContrib(allLights) * input.Color;
	return AccumulateLightContrib(allLights,input.Color);
}
