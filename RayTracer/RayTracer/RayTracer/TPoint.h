#pragma once
#include <iostream>
#include <ostream>

template <typename T>
class TPoint
{
	static_assert(std::is_pod<T>::value, "not a number !");

private:
	//mes coordonnées de type T
	T coord_x;
	T coord_y;
	T coord_z;

public:
	// ici const veut dire que la valeur ne sera pas modifiée dans la fonction
	TPoint(const T& x,const T& y, const T& z) : coord_x(x),coord_y(y),coord_z(z)
	{
		std::cout << "new point created : "<<coord_x<<" "<<coord_y<<" "<<coord_z<<std::endl;
	}
	TPoint(const T& x) : coord_x(x), coord_y(x), coord_z(x)
	{
		std::cout << "new point created : " << coord_x << " " << coord_y << " " << coord_z << std::endl;
	}

	//constructeur par recopie
	TPoint(const TPoint &refPoint) : coord_x(refPoint.coord_x), coord_y(refPoint.coord_y), coord_z(refPoint.coord_z)
	{
		std::cout << "new point created by copy : " << coord_x << " " << coord_y << " " << coord_z << std::endl;
	}

	//void Print(){std::cout << "point coordinates : " << coord_x << " " << coord_y << " " << coord_z << std::endl;}

	

	T GetX(){return coord_x;}
	T GetY(){return coord_y;}
	T GetZ(){return coord_z;}
};

//override de l'operateur << pour pouvoir faire un cout de mon point
//important de le mettre en dehors de la classe
// la référence à l'ostream permet de continuer le cout
template <typename T>
std::ostream& operator<<(std::ostream& os, TPoint<T>& point) {
	return os << point.GetX() << " " << point.GetY() << " " << point.GetZ();
};

