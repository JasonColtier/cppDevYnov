#pragma once
#include "TPoint.h"
#include "TRay.h"
#include "Color.h"

template <typename T>
class IObject
{

    static_assert(std::is_arithmetic<T>::value, "not a number !");

public:

    virtual ~IObject() = default;   
    
    virtual TPoint<T> GetRayIntersection(const TRay<T>& ray) = 0;
    virtual Color GetColorAt(const TPoint<T>& point) const = 0;
    virtual TVector3D<T> GetNormalAtIntersection(const TPoint<T>& point) = 0;
    
};
