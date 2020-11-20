#pragma once

#include <d3d11_1.h>
#include <d3dcompiler.h>
#include <directxmath.h>
#include <directxcolors.h>
#include <windowsx.h>
#include "resource.h"

/** Class fo holding Camera data
*/
using namespace DirectX;

class Camera
{
public:
    Camera();

    void SetPosition(const XMVECTOR& p)
    {
        Eye = p;
    };
    void SetLookAt(const XMVECTOR& p)
    {
        LookAt = p;
    };
    void SetUp(const XMVECTOR& p)
    {
        Up = p;
    };
    void SetFocale(float f)
    {
        Focale = f;
    };

    // return unormalized direction
    XMVECTOR GetDirection() const
    {
        return LookAt - Eye;
    }
    XMVECTOR GetPosition() const
    {
        return Eye;
    }
    XMVECTOR GetLookAt() const
    {
        return LookAt;
    }

    void Translate(const XMVECTOR& t)
    {
        Eye += t;
        LookAt += t;
    }

    void GetView(XMMATRIX& v) const;
    void GetProjection(XMMATRIX& p) const;
protected:
    XMVECTOR Eye;
    XMVECTOR LookAt;
    XMVECTOR Up;

    float Focale;
};