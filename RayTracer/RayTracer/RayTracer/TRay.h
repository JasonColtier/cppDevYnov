#pragma once
#include "TPoint.h"

template <typename T>
class TRay
{
	//static assert

	TPoint<T> originPoint;
	TVector3D<T> directionVector;

private:
	std::pair<TPoint<T>, TVector3D<T>> m_rays;
};

