#pragma once
#include <directxmath.h>
#include <windows.h>
#include <d3d11_1.h>
#include <d3dcompiler.h>
#include <directxmath.h>
#include <directxcolors.h>
#include <windowsx.h>


using namespace DirectX;

class Object
{
protected:
    XMMATRIX Transform; // world transform

public:
    // Return World Transform
    virtual const XMMATRIX& GetTransform() = 0;
    virtual HRESULT Draw(ID3D11DeviceContext*) = 0;
    
};


