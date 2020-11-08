#pragma once
#include "TPoint.h"

template <typename T>
class TSphere
{

    static_assert(std::is_arithmetic<T>::value, "not a number !");

private:
	
    T rayon;
    TPoint<T> centerPoint;
    
public:
    TSphere() : rayon(1), centerPoint(TPoint<T>())
    {
        std::cout << "new default sphere created : " << rayon << " " << centerPoint << std::endl;
    }

    TSphere(const T& rayon,const TPoint<T>& center) : rayon(rayon), centerPoint(center)
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
    

    //utilisation de coordonnées sphériques
	TPoint<T> GetPointOnSphere(float angleAroundZ, float heightAngle)
    {
    	
        TPoint<T> point(
            rayon * cos(angleAroundZ) * sin(heightAngle),
            rayon * sin(angleAroundZ) * cos(heightAngle),
            rayon * cos(heightAngle)
            );
        return point;
    }

	//retourne un vecteur normalisé basé sur le centre et un point
    TVector3D<float> GetNormalOnSphere(TPoint<T> point)
    {
        TVector3D<float> normal(centerPoint, point);
        normal.Normalize();
        return normal;
    }
    
};
