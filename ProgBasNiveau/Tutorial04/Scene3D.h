#pragma once
#include <d3d11.h>
#include <directxmath.h>
#include <vector>


class Object;
class DirectX::XMMATRIX;

class Scene3D
{
	std::vector<Object*> objects;

public:

	//ajouter constructeur et destructeur


	void AddObject(Object* object);

	void Draw(ID3D11DeviceContext* pContext, DirectX::XMMATRIX g_view, DirectX::XMMATRIX g_Projection, ID3D11Buffer* g_pConstantBuffer);
};

