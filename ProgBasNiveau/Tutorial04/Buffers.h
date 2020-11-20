#pragma once
#include <directxmath.h>

using namespace DirectX;

//un constant buffer = 1 appel = 1 draw
//c'est une d�finition de taille de zone m�moire

struct ConstantBuffer
{
	//Place l'objet
	XMMATRIX mWorld;
	//Tourne l'objet
	XMMATRIX mView;
	//Transforme vertice : perspective
	XMMATRIX mProjection;
};

enum LightTypes { Directional = 1, Spot = 2, Point = 3 };

struct Light // quelle est le pramam�tre qui d�finit map lumi�re ?
{
	XMFLOAT4 mPosition;

	XMFLOAT4 mDirection;

	XMFLOAT4 mColor;

	float mAngle;

	LightTypes mType;

	XMFLOAT2 dummy;
	
};

struct ConstantBufferLights
{
	Light lights[2];
};
