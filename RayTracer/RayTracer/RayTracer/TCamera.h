#pragma once
#include <iostream>
#include <ostream>
#include <memory>

#include "TPoint.h"


template <typename T>
class TCamera
{
    static_assert(std::is_arithmetic<T>::value, "not a number !");

public:

    TCamera() : OriginPoint(TPoint<T>(0, 0, 0)),
                Direction(TVector3D<T>(0, 1, 0), RightVector(TVector3D<T>(1, 0, 0)), DownVector(TVector3D<T>(0, -1, 0)))
    {
    }

    TCamera(const TPoint<T>& origin, const TVector3D<T>& dir, const TVector3D<T>& right, const TVector3D<T>& down) :
        OriginPoint(origin), Direction(dir), RightVector(right), DownVector(down)
    {
    }

    TPoint<T> OriginPoint;
    TVector3D<T> Direction;
    TVector3D<T> RightVector;
    TVector3D<T> DownVector;
};
