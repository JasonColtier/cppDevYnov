#pragma once

#include "Object.h"

#include <windows.h>
#include <d3d11_1.h>
#include <d3dcompiler.h>
#include <directxmath.h>
#include <directxcolors.h>
#include <windowsx.h>

#include "resource.h"

class Box3D : public Object
{

public:
    Box3D();
    Box3D(const Box3D&) = delete;//je crée un constructeur par copie qui va faire on purpose une erreur de compilation
    ~Box3D();

    // Initialize API Resources (VBuffer, IBuffer and Shader)
    HRESULT Init(ID3D11Device*);

    // Release API Resources
    void Release();

    // Apply shader and vbuffer setting to the supplied API rendering context and render the box 
    HRESULT Draw(ID3D11DeviceContext*);

    // Return World Transform
    //const  DirectX::XMMATRIX& GetTransform() const { return Transform; }
    const DirectX::XMMATRIX& GetTransform() override { return Transform; }

    // Translate the Box
    void Translate(const DirectX::XMFLOAT3& Translation);

    // Rotate the box with using Euler angle RX,RY,RZ and 
    void Rotate(const DirectX::XMFLOAT3& Euler);

    // Scale the box
    void Scale(const DirectX::XMFLOAT3& Scale);

private:
     //DirectX::XMMATRIX Transform; // world transform

    // Store API resource
    ID3D11VertexShader* m_pVertexShader = nullptr;
    ID3D11PixelShader* m_pPixelShader = nullptr;
    ID3D11InputLayout* m_pVertexLayout = nullptr;
    ID3D11Buffer* m_pVertexBuffer = nullptr;
    ID3D11Buffer* m_pIndexBuffer = nullptr;
};
