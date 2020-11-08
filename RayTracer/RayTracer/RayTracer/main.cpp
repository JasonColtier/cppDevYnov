#include <complex.h>
#include <iostream>
#include <iso646.h>
#include <ostream>
#include <memory>

#include "TList.h"
#include "TPlan.h"
#include "TVector3D.h"
#include "TPoint.h"
#include "TPolygon.h"
#include "TRay.h"
#include "TSphere.h"
#include "TVector.h"


int main()
{


	std::cout << "---- CUSTOM VECTOR CONTENER -----" << std::endl;

	TVector<int> customVector1;//constructeur
	TVector<int> customVector2(8);//constructeur avec taille
	TVector<int> customVector3({ 1,5,3,4 });//constructeur avec list
	std::cout << std::endl;
	std::cout << "size of last vector : " << customVector3.Size() << std::endl;//fonction size
	std::cout << customVector3 << std::endl;
	customVector3.Push_back(6);//fonction pushback
	std::cout << customVector3 << std::endl;
	customVector3.Push_back({ 5,8,3 });//fonction pushback de list
	std::cout << customVector3 << std::endl;
	customVector3.Insert(100, 3);//fonction insert
	std::cout << customVector3 << std::endl;
	customVector3.Sort();//fonction sort
	std::cout << customVector3 << std::endl;
	TVector<int> customVector4;
	customVector4 = customVector3;//operateur =
	std::cout << customVector4[3] << std::endl;// operator []
	std::cout << customVector4.At(1) << std::endl;// pareil que At
	customVector4.Erase(customVector4.Begin() + 7);//Erase
	std::cout << customVector4 << std::endl;
	customVector4.Applyfunction([](int& a)//application d'une fonction à tous les élements de mon tableau
		{
			a += 2;
		});
	std::cout << customVector4 << std::endl;

	
	std::cout << "\n\n\n---- CUSTOM LIST CONTENER -----" << std::endl;
	TList<int> customList1;
	customList1.Push_back(2);
	customList1.Push_back(8);
	customList1.Push_back(15);
	std::cout << customList1 << std::endl;
	customList1.Insert(99,1);
	std::cout << customList1 << std::endl;





	std::cout << "\n\n\n---- 3D POINT AND 3D VECTOR -----" << std::endl;
	std::cout << "Creating a new point" <<std::endl;
	TPoint<int> point1(1, 3, 6);
	std::cout << point1;
	TPoint<int>* p_Point1 = &point1;
	TPoint<int> point2(0);
	TPoint<int> point3(point1);
	TPoint<int> point4(2,5,3);
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
	std::cout << "using pointers" << std::endl;
	point1 += vector1;
	std::cout << point1 << std::endl;
	std::cout << *p_Point1 << std::endl;
	
	std::cout << std::endl; 
	std::cout << std::endl; 
	std::cout << "starting operations : vector1 += 2" << std::endl;
	vector1 += 2;
	std::cout << vector1  <<std::endl;
	std::cout << "vector2 =  vector1 + 2" << std::endl;
	vector2 = vector1 + 2;
	TVector3D<int> v = vector1 + 2;
	std::cout << vector2  <<std::endl;
	std::cout << v  <<std::endl;
	
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

	std::cout << "\n\n\n---- 3D Sphere -----" << std::endl;
	std::cout << std::endl; 
	std::cout << std::endl;
	std::cout << "Creating a sphere";
	TSphere<int> sphere1;
	TSphere<int> sphere2(600,point1);
	TSphere<float> sphere3;

	TPoint<int> pointOnSphere = sphere2.GetPointOnSphere(30.0f, 80.0f);
	std::cout << "point on sphere : "<<pointOnSphere;

	TVector3D<float> normalOnSphere; 
	normalOnSphere = sphere3.GetNormalOnSphere(TPoint<float>(10,50,2));
	std::cout << "normal on sphere : " << normalOnSphere;
	std::cout << std::endl;
	std::cout << std::endl;


	std::cout << "\n\n\n---- 2D Polygon -----" << std::endl;
	TPoint<float> polyPoint1(1, 1, 0);
	TPoint<float> polyPoint2(-1, 1, 0);
	TPoint<float> polyPoint3(-1, -1, 0);
	TPoint<float> polyPoint4(1, -1, 1);

	//je crée mon polygone en donnant des références à des points car si les points changent, je veux que le polygone change aussi
	TPolygon<float> poly(&polyPoint1,&polyPoint2, &polyPoint3, &polyPoint4);
	std::cout << "poly : " << poly<<std::endl;


	//modification d'un point du polygone pour vérifier que ce polygone est bien mis à jour aussi
	polyPoint1 += vector6;
	std::cout << "polypoint1 : " << polyPoint1 << std::endl;
	std::cout << "poly : " << poly << std::endl;

	TPoint<float> center(0.5f, 0, 0);
	int inside = IsPointInPolygon(poly.GetPointList().size(), poly, center);
	std::cout << "inside : " << inside << std::endl;

	std::cout << "\n\n\n---- Ray -----" << std::endl;
	TRay<int> ray(point1,vector1);
	std::cout << "origin : " << ray.GetOrigin() << " direction : " << ray.GetDirection();

	std::cout << "\n\n\n---- Plan -----" << std::endl;
	TPlan<int> plan(vector1,10);
	std::cout << "origin : " << plan.GetDistance() << " normal : " << plan.GetNormal();
	
}

