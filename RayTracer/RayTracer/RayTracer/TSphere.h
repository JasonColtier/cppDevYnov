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
    };

    TSphere(T rayon, TPoint<T>& center) : rayon(rayon), centerPoint(center)
    {
        std::cout << "new sphere created rayon : " << rayon << " center point : " << centerPoint << std::endl;
    };
    ~TSphere() = default;
  
    T GetRayon() const
    {
        return rayon;
    }

    void set_rayon(const T& rayon)
    {
        this->rayon = rayon;
    }

    TPoint<T> GetCenterPoint() const
    {
        return centerPoint;
    }

    void set_center_point(const TPoint<T>& center_point)
    {
        centerPoint = center_point;
    }
    
    //fonction pour retourner la normale d'un point sur la sphère
    //point définit par angle X
    // TVector3D<T> GetNormalAtPoint()


    
};
