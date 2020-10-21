#pragma once
#include <iostream>
#include <ostream>
#include "TPoint.h";

template <typename T>
class TVector3D
{
	static_assert(std::is_pod<T>::value, "not a number !");

private:
	//coordonnées de mon vecteur
	T delta_x;
	T delta_y;
	T delta_z;

public:
	TVector3D(const T& x,const T& y,const T& z) : delta_x(x),delta_y(y),delta_z(z)
	{
		std::cout << "new vector created : " << delta_x << " " << delta_y << " " << delta_z << std::endl;
	}
	TVector3D(TPoint<T>& point1,TPoint<T>& point2)
	{
		delta_x = point2.GetX() - point1.GetX();
		delta_y = point2.GetY() - point1.GetY();
		delta_z = point2.GetZ() - point1.GetZ();
		std::cout << "new vector created by points : " << delta_x << " " << delta_y << " " << delta_z << std::endl;
	}
	TVector3D(TVector3D& ref_vector) : delta_x(ref_vector.delta_x), delta_y(ref_vector.delta_y), delta_z(ref_vector.delta_z)
	{
		std::cout << "new vector created by copy : " << delta_x << " " << delta_y << " " << delta_z << std::endl;
	}

	T GetX() { return delta_x; }
	T GetY() { return delta_y; }
	T GetZ() { return delta_z; }


	void operator+(int add) { delta_x += add; delta_y += add; delta_z += add; };
	void operator-(int sub) { delta_x -= sub; delta_y -= sub; delta_z -= sub; };

};

template <typename T>
std::ostream& operator<<(std::ostream& os, TVector3D<T>& vector) {
	return os << vector.GetX() << " " << vector.GetY() << " " << vector.GetZ();
};

