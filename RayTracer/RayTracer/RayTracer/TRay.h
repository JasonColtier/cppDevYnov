#pragma once
#include "TPoint.h"
#include <algorithm>

template <typename T>
class TRay
{
	static_assert(std::is_arithmetic<T>::value, "not a number !");

	std::pair<TPoint<T>, TVector3D<T>> ray;

public:
	TRay() : TRay(TVector3D<T>(), TVector3D<T>(1, 0, 0))
	{
		std::cout << "new  defalut Ray created : " << std::endl;

	}
	TRay(const TPoint<T>& origin, const TVector3D<T>& direction) : ray(origin,direction)
	{
		std::cout << "new Ray created, origin : " << origin << ", direction :  " << direction << std::endl;

	}
	~TRay() = default;


	TPoint<T> GetOrigin() const { return ray.first; }
	TVector3D<T> GetDirection() const { return ray.second; }
	
};

