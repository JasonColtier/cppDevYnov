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

	TPoint<T>* operator[](int point)
	{
		return p_PointsVector.at(point);
	}

	
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
int IsPointInPolygon(int nvert, TPolygon<T>& poly, TPoint<T>& point)
{
	std::vector<TPoint<T>*> polyPoints = poly.GetPointList();

	
	int i, j, c = 0;
	for (i = 0, j = nvert - 1; i < nvert; j = i++) {
		TPoint<T>* currentPointI = polyPoints[i];
		TPoint<T>* currentPointJ = polyPoints[j];
		if (((currentPointI->GetY() > point.GetY()) != (currentPointJ->GetY() > point.GetY())) &&
			(point.GetX() < (currentPointJ->GetX() - currentPointI->GetX()) * (point.GetY() - currentPointI->GetY()) / (currentPointJ->GetY() - currentPointI->GetY()) + currentPointI->GetX()))
			c = !c;
		//waw la magie
	}
	return c;
}

template <typename T>
int orientation(TPoint<T>& p, TPoint<T>& q, TPoint<T>& r)
{
	int val = (q.GetX() - p.GetY()) * (r.GetX() - q.GetX()) -
		(q.GetX() - p.GetX()) * (r.GetY() - q.GetY());

	if (val == 0) return 0;  // colinear 
	return (val > 0) ? 1 : 2; // clock or counterclock wise 
}

template <typename T>
TPolygon<T> ConvexFromPolygon(TPolygon<T>& poly)
{
	TPolygon<T> convex;
	int n = poly.GetPointList().size();
	// Find the leftmost point 
	int l = 0;
	for (int i = 1; i < n; i++)
	{
		if (poly[i]->GetX() < poly[l]->GetX())
			l = i;
	}
	std::cout << "left point is "<< *poly[l]<<std::endl;


	// Start from leftmost point, keep moving counterclockwise 
	// until reach the start point again.  This loop runs O(h) 
	// times where h is number of points in result or output. 
	int p = l, q;
	do
	{
		// Add current point to result
		convex.AddPoint(poly[p]);
		std::cout << convex.GetPointList().size();
		// Search for a point 'q' such that orientation(p, x, 
		// q) is counterclockwise for all points 'x'. The idea 
		// is to keep track of last visited most counterclock- 
		// wise point in q. If any point 'i' is more counterclock- 
		// wise than q, then update q. 
		q = (p + 1) % n;
		for (int i = 0; i < n; i++)
		{
			// If i is more counterclockwise than current q, then 
			// update q 
			if (orientation(*poly[p], *poly[i], *poly[q]) == 2)
				q = i;
		}

		// Now q is the most counterclockwise with respect to p 
		// Set p as q for next iteration, so that q is added to 
		// result 'hull' 
		p = q;

	} while (p != l);  // While we don't come to first point 

	
	return convex;
	
}