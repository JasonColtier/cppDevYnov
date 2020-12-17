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
    XMFLOAT4 ObjectColor = XMFLOAT4(1,1,1,1); // world transform
    float ObjectSpecular = 1; // world transform

public:
    
    float GetObjectSpecular() const
    {
        return ObjectSpecular;
    }

    void SetObjectSpecular(float object_specular)
    {
        ObjectSpecular = object_specular;
    }

    void SetObjectColor(const XMFLOAT4& objectColor)
    {
        ObjectColor = objectColor;
    }

    // Return World Transform
    virtual const XMMATRIX& GetTransform() = 0;
    virtual const XMFLOAT4& GetObjectColor()
    {
        return ObjectColor;
    };

    
    virtual HRESULT Draw(ID3D11DeviceContext*) = 0;
    
};


