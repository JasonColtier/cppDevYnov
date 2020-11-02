#include <complex.h>
#include <iostream>
#include <iso646.h>
#include <ostream>
#include "TVector3D.h"
#include "TPoint.h"
#include "TPolygon.h"
#include "TSphere.h"


int main()
{
	std::cout << "Creating a new point" <<std::endl;
	TPoint<int> point1(1, 3, 6);
	TPoint<int> point2(0);
	TPoint<int> point3(point1);
	TPoint<int> point4(2,5,3);
	std::cout << point1;   

	std::cout << std::endl; 
	std::cout << std::endl; 
	std::cout << "Creating a new vector" << std::endl;
	TVector3D<int> vector1(2, 5, 3);
	TVector3D<int> vector2(point1,point4);           
	TVector3D<int> vector3(vector1);           
	TVector3D<int> vector4(3,-5,4);           
	TVector3D<int> vector5(2,6,5);           
	TVector3D<float> vector6(5,5,5);            

	std::cout << std::endl; 
	std::cout << std::endl; 
	std::cout << "starting operations : vector1 + 2" << std::endl;
	vector1 += 2;
	std::cout << vector1  <<std::endl;
	std::cout << "vector2 =  vector1 + 2" << std::endl;
	vector2 = vector1 + 2;
	std::cout << vector2  <<std::endl;
	
	std::cout << "- 1" << std::endl;
	vector1 -= 1;
	std::cout << vector1 << std::endl;
	std::cout << "* 3" << std::endl;
	vector1 *= 3;
	std::cout << vector1 << std::endl;
	std::cout << "/ 2" << std::endl;
	vector1 /= 2;
	std::cout << "vector 1 : " << vector1 << std::endl;
	std::cout << "vector4 * vector5" << std::endl;
	vector3 = vector4 * vector5;
	std::cout << vector3 << std::endl;

	std::cout << std::endl; 
	std::cout << std::endl; 
	std::cout << "magnitude de v1 : " << std::endl;
	auto mag =  vector1.Magnitude();
	std::cout << mag << std::endl;

	std::cout << std::endl; 
	std::cout << std::endl; 
	std::cout << "normalisation de v6 : " << std::endl;
	TVector3D<float> norm;
	norm = vector6.Normalize();
	std::cout <<"normalisation : "<< norm << std::endl;

	std::cout << std::endl; 
	std::cout << std::endl; 
	std::cout << "dot de v1 et v2: " << std::endl;
	std::cout << "v1: " <<vector1<< std::endl;
	std::cout << "v2: " <<vector2<< std::endl;
	auto dot =  Dot(vector1,vector2);	
	std::cout << dot << std::endl;

	std::cout << std::endl; 
	std::cout << std::endl; 
	std::cout << "invert de v6 : " << vector6<< std::endl;
	TVector3D<float> invert;
	invert = vector6.Invert();
	std::cout << invert << std::endl; 

	std::cout << std::endl; 
	std::cout << std::endl; 
	std::cout << "operation entre point 1 "<< point1 <<" et vector 1 " << vector1 << std::endl;
	point1 += vector1;
	point2 = point1 + vector1;
	std::cout << point1 << std::endl;
	std::cout << point2 << std::endl;

	std::cout << std::endl; 
	std::cout << std::endl;
	std::cout << "Creating a sphere";
	TSphere<int> sphere1;
	TSphere<int> sphere2(600,point1);
	TSphere<float> sphere3;

	TPoint<int> pointOnSphere = sphere2.GetPointOnSphere(30.0f, 80.0f);
	std::cout << "point on sphere : "<<pointOnSphere;

	TVector3D<float> normalOnSphere; 
	normalOnSphere = sphere3.GetNormalOnSphere(30.0f,40.0f);
	std::cout << "normal on sphere : " << normalOnSphere;
	std::cout << std::endl;
	std::cout << std::endl;

	TPoint<float> polyPoint1(0, 0, 0);
	TPoint<float> polyPoint2(1, 0, 0);
	TPoint<float> polyPoint3(0, 1, 0);
	TPoint<float> polyPoint4(0, 1, 1);
	
	TPolygon<float> poly(polyPoint1, polyPoint2, polyPoint3, polyPoint4);
	std::cout << "poly : " << poly<<std::endl;


}
