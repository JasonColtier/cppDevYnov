#include "Scene3D.h"
#include "Buffers.h"
#include "Object.h"

void Scene3D::AddObject(Object* object)
{
	objects.push_back(object);
}

void Scene3D::AddLight(LightStruct* light)
{
	lightsBuffer.lights[indexLight] = *light;
	indexLight++;
}

void Scene3D::Draw(ID3D11DeviceContext* pContext, DirectX::XMMATRIX g_view, DirectX::XMMATRIX g_Projection,
                   ID3D11Buffer* g_pConstantBuffer, ID3D11Buffer* pContextLights)
{
	ConstantBuffer cb;

	//ajout des lights contenues dans le LightBuffer
	pContext->UpdateSubresource(pContextLights, 0, nullptr, &lightsBuffer, 0, 0);


	//ajout et affichage des objets
	for (Object* object : objects)
	{
		cb.mView = DirectX::XMMatrixTranspose(g_view);
		cb.mProjection = DirectX::XMMatrixTranspose(g_Projection);
		cb.mWorld = DirectX::XMMatrixTranspose(object->GetTransform());
		cb.mSpecular = object->GetObjectSpecular();
		pContext->UpdateSubresource(g_pConstantBuffer, 0, nullptr, &cb, 0, 0);
		object->Draw(pContext);
	}

	

	
}
