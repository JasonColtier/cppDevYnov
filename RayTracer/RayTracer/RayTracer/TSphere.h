#pragma once
#include "TPoint.h"

template <typename T>
class TSphere
{

private:
	
    T rayon;
    TPoint<T> centerPoint;
    
public:
    TSphere() : rayon(1), centerPoint(TPoint<T>())
    {
        std::cout << "new default sphere created : " << rayon << " " << centerPoint << std::endl;
    }

    TSphere(T rayon, TPoint<T>& center) : rayon(rayon), centerPoint(center)
    {
        std::cout << "new sphere created rayon : " << rayon << " center point : " << centerPoint << std::endl;
    }
	
    ~TSphere() = default;
  
    T GetRayon() const
    {
        return rayon;
    }

    void SetRayon(const T& rayon)
    {
        this->rayon = rayon;
    }

    TPoint<T> GetCenterPoint() const
    {
        return centerPoint;
    }

    void SetCenterPoint(const TPoint<T>& center_point)
    {
        centerPoint = center_point;
    }
    
    //fonction pour retourner la normale d'un point sur la sphère
    //point définit par angle X
    // TVector3D<T> GetNormalAtPoint()

	TPoint<T> GetPointOnSphere(float angleAroundZ, float heightAngle)
    {
    	
        TPoint<T> point(
            rayon * cos(angleAroundZ) * sin(heightAngle),
            rayon * sin(angleAroundZ) * cos(heightAngle),
            rayon * cos(heightAngle)
            );
        return point;
    }

	TVector3D<float> GetNormalOnSphere(float angleAroundZ, float heightAngle)
    {

        TPoint<float> surfacePoint = GetPointOnSphere(angleAroundZ, heightAngle);
        TVector3D<float> normal(centerPoint, surfacePoint);
        normal.Normalize();
        return normal;

        //return TVector3D<T>(centerPoint, point).Normalize();
    	//il me faut juste un point en coo
    }

    TVector3D<float> GetNormalOnSphere(TPoint<T> surfacePoint)
    {
        TVector3D<float> normal(centerPoint, surfacePoint);
        normal.Normalize();
        return normal;
    }
    
};
