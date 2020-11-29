#pragma once
#include "TPoint.h"
#include "Color.h"

template <typename T>
class ISource
{

    static_assert(std::is_arithmetic<T>::value, "not a number !");

public:

    virtual ~ISource() = default;
    
    virtual Color GetLightColor() = 0;
    virtual TPoint<T> GetLightPointSource() = 0;
    
};
