#include "Box.h"
#include <ostream>
#include <iostream>

// Forward declaration
HRESULT CompileShaderFromFile(const WCHAR* szFileName, LPCSTR szEntryPoint, LPCSTR szShaderModel, ID3DBlob** ppBlobOut);

using namespace DirectX;

//--------------------------------------------------------------------------------------
// Structures
//--------------------------------------------------------------------------------------
struct SimpleVertex
{
    XMFLOAT3 Pos;
    XMFLOAT4 Color;
    XMFLOAT3 Normal;
    XMFLOAT2 UV;
};

// Box3D Ctor
Box3D::Box3D()
{
    Transform = XMMatrixIdentity();
	std::cout << "new box !" << std::endl;

}

// Box3D Dtor
Box3D::~Box3D()
{
    Release();
}


HRESULT Box3D::Init(ID3D11Device* pd3dDevice)
{
    // Compile the vertex shader
    ID3DBlob* pVSBlob = nullptr;
    HRESULT hr = CompileShaderFromFile(L"Tutorial04.fx", "VS", "vs_4_0", &pVSBlob);
    if (FAILED(hr))
    {
        MessageBox(nullptr,
            L"The FX file cannot be compiled.  Please run this executable from the directory that contains the FX file.", L"Error", MB_OK);
        return hr;
    }

    // Create the vertex shader
    hr = pd3dDevice->CreateVertexShader(pVSBlob->GetBufferPointer(), pVSBlob->GetBufferSize(), nullptr, &m_pVertexShader);
    if (FAILED(hr))
    {
        pVSBlob->Release();
        return hr;
    }

    // Define the input layout
    D3D11_INPUT_ELEMENT_DESC layout[] =
    {
        { "POSITION", 0,    DXGI_FORMAT_R32G32B32_FLOAT,    0, 0,   D3D11_INPUT_PER_VERTEX_DATA, 0 },
        { "COLOR", 0,       DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12,  D3D11_INPUT_PER_VERTEX_DATA, 0 },
        { "NORMAL", 0,      DXGI_FORMAT_R32G32B32_FLOAT,    0, 28,  D3D11_INPUT_PER_VERTEX_DATA, 0 },
        { "TEXCOORD", 0,    DXGI_FORMAT_R32G32_FLOAT,       0, 40,  D3D11_INPUT_PER_VERTEX_DATA, 0 }
    };
    UINT numElements = ARRAYSIZE(layout);

    // Create the input layout
    hr = pd3dDevice->CreateInputLayout(layout, numElements, pVSBlob->GetBufferPointer(), pVSBlob->GetBufferSize(), &m_pVertexLayout);
    pVSBlob->Release();
    if (FAILED(hr))
        return hr;


    // Compile the pixel shader
    ID3DBlob* pPSBlob = nullptr;
    hr = CompileShaderFromFile(L"Tutorial04.fx", "PS", "ps_4_0", &pPSBlob);
    if (FAILED(hr))
    {
        MessageBox(nullptr, L"The FX file cannot be compiled.  Please run this executable from the directory that contains the FX file.", L"Error", MB_OK);
        return hr;
    }

    // Create the pixel shader
    hr = pd3dDevice->CreatePixelShader(pPSBlob->GetBufferPointer(), pPSBlob->GetBufferSize(), nullptr, &m_pPixelShader);
    pPSBlob->Release();
    if (FAILED(hr))
        return hr;

    XMFLOAT4 WhiteColor = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);

    XMFLOAT2 UVs[] =
    {
        XMFLOAT2(0,0),
        XMFLOAT2(1,0),
        XMFLOAT2(1,1),
        XMFLOAT2(0,1)
    };

    XMFLOAT3 Points[] =
    {
         XMFLOAT3(-1.0f, 1.0f, -1.0f),
         XMFLOAT3(1.0f, 1.0f, -1.0f),
         XMFLOAT3(1.0f, 1.0f, 1.0f),
         XMFLOAT3(-1.0f, 1.0f, 1.0f),
         XMFLOAT3(-1.0f, -1.0f, -1.0f),
         XMFLOAT3(1.0f, -1.0f, -1.0f),
         XMFLOAT3(1.0f, -1.0f, 1.0f),
         XMFLOAT3(-1.0f, -1.0f, 1.0f),
    };

    XMFLOAT3 Normals[] =
    {
         XMFLOAT3(0.0f, 1.0f, 0.0f),    // Face 0
         XMFLOAT3(1.0f, 0.0f, 0.0f),    // Face 1
         XMFLOAT3(0.0f, 0.0f, -1.0f),   // Face 2
         XMFLOAT3(0.0f, -1.0f, 0.0f),   // Face 3
         XMFLOAT3(0.0f, 0.0f, 1.0f),    // Face 4
         XMFLOAT3(-1.0f, 0.0f, 0.0f),   // Face 5
    };

    WORD indicesVertexQuad[] =
    {
        0, 1, 2, 3,    // Face 0
        1, 5, 6, 2,    // Face 1
        0, 4, 5, 1,    // Face 2
        4, 7, 6, 5,    // Face 3
        2, 6, 7, 3,    // Face 4
        3, 7, 4, 0,    // Face 5
    };

    // Create vertex buffer
    SimpleVertex vertices[24];

    for (int f = 0; f < 6; ++f)
    {
        for (int i = 0; i < 4; ++i)
        {
            int indexV = (f * 4 + i);
            vertices[f * 4 + i] = { Points[indicesVertexQuad[indexV]],   WhiteColor, Normals[f], UVs[i] };
        }
    }

    D3D11_BUFFER_DESC bd = {};
    bd.Usage = D3D11_USAGE_DEFAULT;
    bd.ByteWidth = sizeof(vertices);
    bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
    bd.CPUAccessFlags = 0;

    D3D11_SUBRESOURCE_DATA InitData = {};
    InitData.pSysMem = vertices;
    hr = pd3dDevice->CreateBuffer(&bd, &InitData, &m_pVertexBuffer);
    if (FAILED(hr))
        return hr;

    // Create index buffer
    WORD faceindices[] =
    {
        3,1,0,
        2,1,3,
    };

    WORD indices[36];
    for (WORD f = 0; f < 6; ++f)
    {
        for (WORD i = 0; i < 6; ++i)
        {
            indices[f * 6 + i] = faceindices[i] + 4 * f;
        }
    }

    bd.Usage = D3D11_USAGE_DEFAULT;
    bd.ByteWidth = sizeof(WORD) * 36;        // 36 vertices needed for 12 triangles in a triangle list
    bd.BindFlags = D3D11_BIND_INDEX_BUFFER;
    bd.CPUAccessFlags = 0;
    InitData.pSysMem = indices;
    hr = pd3dDevice->CreateBuffer(&bd, &InitData, &m_pIndexBuffer);
    if (FAILED(hr))
        return hr;

    return S_OK;
}

void Box3D::Release()
{
    if (m_pVertexBuffer) m_pVertexBuffer->Release();
    if (m_pIndexBuffer) m_pIndexBuffer->Release();
    if (m_pVertexLayout) m_pVertexLayout->Release();
    if (m_pVertexShader) m_pVertexShader->Release();
    if (m_pPixelShader) m_pPixelShader->Release();

    m_pVertexBuffer = nullptr;
    m_pIndexBuffer = nullptr;
    m_pVertexLayout = nullptr;
    m_pVertexShader = nullptr;
    m_pPixelShader = nullptr;
}

// Translate the Box
void  Box3D::Translate(const XMFLOAT3& Translation)
{
    Transform = XMMatrixTranslation(Translation.x, Translation.y, Translation.z);
}

// Rotate the box with using Euler angle RX,RY,RZ and 
void  Box3D::Rotate(const XMFLOAT3& Euler)
{
    Transform = XMMatrixRotationRollPitchYaw(Euler.x, Euler.y, Euler.z);
}

// Scale the box
void  Box3D::Scale(const XMFLOAT3& Scale)
{
    Transform = XMMatrixScaling(Scale.x,Scale.y,Scale.z);
}


HRESULT Box3D::Draw(ID3D11DeviceContext* pContext)
{
    // Set the input layout
    pContext->IASetInputLayout(m_pVertexLayout);

    // Set vertex buffer
    UINT stride = sizeof(SimpleVertex);
    UINT offset = 0;
    pContext->IASetVertexBuffers(0, 1, &m_pVertexBuffer, &stride, &offset);

    // Set index buffer
    pContext->IASetIndexBuffer(m_pIndexBuffer, DXGI_FORMAT_R16_UINT, 0);

    // Set primitive topology
    pContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

    // Set the shaders
    pContext->VSSetShader(m_pVertexShader, nullptr, 0);
    pContext->PSSetShader(m_pPixelShader, nullptr, 0);


    // Draw
    pContext->DrawIndexed(36, 0, 0);        // 36 vertices needed for 12 triangles in a triangle list

    return S_OK;
}
