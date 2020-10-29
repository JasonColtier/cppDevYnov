#pragma once
#include <directxmath.h>

class Object
{
protected:
    DirectX::XMMATRIX Transform; // world transform

public:
    // Return World Transform
    const DirectX::XMMATRIX& GetTransform() const { return Transform; };
    
};
