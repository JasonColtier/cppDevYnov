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
	~TPolygon() = default;//à finir?


	TPoint<T>* operator[](int point)
	{
		return p_PointsVector.at(point);
	}

	//pourrait être remplacé par std initialize list plus facile à manipuler
	template <typename U, typename... Ts>
	TPolygon(U* point, Ts*... points) : TPolygon(points...)
	{
		p_PointsVector.insert(p_PointsVector.begin(),point);
		TPolygon(points...);
		std::cout << "adding point "<<*point<<" to poly "<<std::endl;
	}

	std::vector<TPoint<T>*> GetPointList()
	{
		return p_PointsVector;
	}

	void AddPoint(TPoint<T>* point)
	{
		p_PointsVector.push_back(point);
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

template <typename T>
int IsPointInPolygon(int nvert, TPolygon<T>& poly, TPoint<T>& point)//fonction permettant de déterminer si un point est dans un polygone ou pas
{
	std::vector<TPoint<T>*> polyPoints = poly.GetPointList();
	//I run a semi - infinite ray horizontally(increasing x, fixed y) out from the test point, and count how many edges it crosses.
	//At each crossing, the ray switches between insideand outside.This is called the Jordan curve theorem.
	
	int i, j, c = 0;
	for (i = 0, j = nvert - 1; i < nvert; j = i++) {
		TPoint<T>* currentPointI = polyPoints[i];
		TPoint<T>* currentPointJ = polyPoints[j];
		if (((currentPointI->GetY() > point.GetY()) != (currentPointJ->GetY() > point.GetY())) &&
			(point.GetX() < (currentPointJ->GetX() - currentPointI->GetX()) * (point.GetY() - currentPointI->GetY()) / (currentPointJ->GetY() - currentPointI->GetY()) + currentPointI->GetX()))
			c = !c;
	}
	return c;
}
