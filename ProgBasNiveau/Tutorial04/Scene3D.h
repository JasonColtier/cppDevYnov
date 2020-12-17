#pragma once
#include <d3d11.h>
#include <directxmath.h>
#include <vector>

#include "Buffers.h"


struct ConstantBufferLights;
class Object;

class Scene3D
{
	std::vector<Object*> objects;//les objets qui seront rendus dans ma scène. Ajoutés dans le InitScene de tutorial.cpp
	ConstantBufferLights lightsBuffer;//contiendra les infos de mes lights (pour l'instant 2)
	int indexLight = 0;//index pour ajouter mes lights au lightBuffer

public:

	Scene3D() = default;
	~Scene3D() = default;

	//ajout d'objets comme les cubes à la scène
	void AddObject(Object* object);

	//ajout des lumières à la scène
	void AddLight(LightStruct* light);

	//update et affichage des lumières puis des objets
	void Draw(ID3D11DeviceContext* pContext, DirectX::XMMATRIX g_view, DirectX::XMMATRIX g_Projection, ID3D11Buffer* g_pConstantBuffer, ID3D11Buffer
	          * pContextLights);
};

