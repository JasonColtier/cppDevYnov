#include "Scene3D.h"
#include "Buffers.h"
#include "Object.h"

void Scene3D::AddObject(Object* object)
{
	objects.push_back(object);
}

void Scene3D::Draw(ID3D11DeviceContext* pContext, DirectX::XMMATRIX g_view, DirectX::XMMATRIX g_Projection,
	ID3D11Buffer* g_pConstantBuffer)
{
	ConstantBuffer cb;

	for (Object* object : objects)
	{
		cb.mView = DirectX::XMMatrixTranspose(g_view);
		cb.mProjection = DirectX::XMMatrixTranspose(g_Projection);
		cb.mWorld = DirectX::XMMatrixTranspose(object->GetTransform());
		pContext->UpdateSubresource(g_pConstantBuffer, 0, nullptr, &cb, 0, 0);
		object->Draw(pContext);
	}
}
