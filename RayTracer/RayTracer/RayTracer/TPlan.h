#pragma once
#include <algorithm>
#include "TVector3D.h";

template <typename T>
class TPlan
{
	static_assert(std::is_arithmetic<T>::value, "not a number !");

	TVector3D<T> normal;
	float distance;

public:
	TPlan() : normal(TVector3D<T>(1,0,0)), distance(0)
	{
	}

	TPlan(const TVector3D<T>& normal,const T& distance) : normal(normal), distance(distance)
	{
	}


	TVector3D<T> GetNormal() { return normal; }
	TVector3D<T> GetDistance() { return distance; }

	TVector3D<T> GetNormalAt(const TPoint<T>& point) { return normal; }

	//la transformé de huggs
	//distance à une droite depuis l'origine

};

