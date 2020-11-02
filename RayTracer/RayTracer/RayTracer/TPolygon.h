#pragma once
#include <vector>
#include "TPoint.h"

template <class T>
class TPolygon
{

	//définit par une suite de points rejoints dans un ordre donné
	std::vector<TPoint<T>> pointList;

public:

	TPolygon() = default;
	
	template <class U, class... Ts>
	TPolygon(U& point, Ts&... points) : TPolygon(points...)
	{
		pointList.insert(pointList.begin(),point);
		TPolygon(points...);
		std::cout << "adding point "<<point<<" to poly "<<std::endl;
	}

	std::vector<TPoint<T>> GetPointList()
	{
		return pointList;
	}
	
private:
	

};

template <typename T>
std::ostream& operator<<(std::ostream& os, TPolygon<T>& poly)
{
	std::string out;
	for (auto& point : poly.GetPointList()) // access by reference to avoid copying
	{
		std::cout << point;
	}
	return os;
};
