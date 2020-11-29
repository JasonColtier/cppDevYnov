#pragma once
#include <iostream>
#include <ostream>
#include <memory>

#include "TPoint.h"
#include "Color.h"


template <typename T>
class TLight
{
    static_assert(std::is_arithmetic<T>::value, "not a number !");

public:

    TLight(TPoint<T> origin, Color color) : OriginPoint(origin), LightColor(color)
    {
    };

    TPoint<T> OriginPoint;
    Color LightColor;
};
