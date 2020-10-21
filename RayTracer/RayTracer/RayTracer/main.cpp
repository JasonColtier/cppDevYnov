#include <iostream>
#include <ostream>
#include "TPoint.h"
#include "TVector3D.h"

int main()
{
	std::cout << "Creating a new point" <<std::endl;
	TPoint<int> point1(1, 3, 6);
	TPoint<int> point2(0);
	TPoint<int> point3(point1);
	TPoint<int> point4(2,5,3);
	std::cout << point1;   

	std::cout << std::endl; 
	std::cout << "Creating a new vector" << std::endl;
	TVector3D<int> vector1(2, 5, 3);
	TVector3D<int> vector2(point1,point4);           
	TVector3D<int> vector3(vector1);           

	std::cout << std::endl; 
	std::cout << "starting operations : + 2" << std::endl;
	vector1 + 2;
	std::cout << vector1  <<std::endl;
	vector1 - 1;
	std::cout << vector1 << std::endl;
	
}