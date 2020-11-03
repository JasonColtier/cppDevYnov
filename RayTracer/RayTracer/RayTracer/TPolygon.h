#pragma once
#include <vector>
#include <memory>
#include "TPoint.h"

template <typename T>
class TPolygon
{

	//définit par une suite de points rejoints dans un ordre donné
	//un vecteur de pointeurs vers mes points
	std::vector<TPoint<T>*> p_PointsVector;

public:


	
	TPolygon() = default;
	~TPolygon()
	{
		for (auto point = p_PointsVector.begin(); point != p_PointsVector.end(); ++point)
		{
			//détruire les pointeurs ?
		}
	}

	
	template <typename U, typename... Ts>
	TPolygon(U* point, Ts*... points) : TPolygon(points...)
	{
		p_PointsVector.insert(p_PointsVector.begin(),point);
		TPolygon(points...);
		std::cout << "adding point "<<point<<" to poly "<<std::endl;
	}

	std::vector<TPoint<T>*> GetPointList()
	{
		return p_PointsVector;
	}
	
private:
	

};

template <typename T>
std::ostream& operator<<(std::ostream& os, TPolygon<T>& poly)
{
	std::string out;
	for (auto& point : poly.GetPointList()) // access by reference to avoid copying
	{
		std::cout << *point;
	}
	return os;
};
