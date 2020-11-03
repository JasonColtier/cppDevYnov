#pragma once
#include <iostream>
#include <ostream>
#include <memory>

// #include "TVector3D.h"

template <typename T>
class TVector3D; 

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
    TPoint() : coord_x(0), coord_y(0), coord_z(0)
    {
        //std::cout << "new point created : " << coord_x << " " << coord_y << " " << coord_z << std::endl;
    }
    
    TPoint(const T& x, const T& y, const T& z) : coord_x(x), coord_y(y), coord_z(z)
    {
        //std::cout << "new point created : " << coord_x << " " << coord_y << " " << coord_z << std::endl;
    }

    TPoint(const T& x) : coord_x(x), coord_y(x), coord_z(x)
    {
        //std::cout << "new point created : " << coord_x << " " << coord_y << " " << coord_z << std::endl;
    }

    //constructeur par recopie
    TPoint(const TPoint& refPoint) : coord_x(refPoint.coord_x), coord_y(refPoint.coord_y), coord_z(refPoint.coord_z)
    {
        //std::cout << "new point created by copy : " << coord_x << " " << coord_y << " " << coord_z << std::endl;
    }

    T GetX() { return coord_x; }
    T GetY() { return coord_y; }
    T GetZ() { return coord_z; }

    void set_coord_x(const T& coord_x)
    {
        this->coord_x = coord_x;
    }

    void set_coord_y(const T& coord_y)
    {
        this->coord_y = coord_y;
    }

    void set_coord_z(const T& coord_z)
    {
        this->coord_z = coord_z;
    }


    /*
    *    OPERATIONS DE TRANSLATION AVEC VECTEURS
    */
    TPoint<T> operator+(TVector3D<T>& vector)
    {
        TPoint<T> newPoint;
        newPoint.set_coord_x(vector.GetX() + this->GetX());
        newPoint.set_coord_y(vector.GetY() + this->GetY());
        newPoint.set_coord_z(vector.GetZ() + this->GetZ());
        return newPoint;
    }
    
    void operator+=(TVector3D<T>& vector) 
    {
        this->coord_x += vector.GetX();
        this->coord_y += vector.GetY();
        this->coord_z += vector.GetZ();
    }

    TPoint<T> operator-(TVector3D<T>& vector)
    {
        TPoint<T> newPoint;
        newPoint.set_coord_x(vector.GetX() - this->GetX());
        newPoint.set_coord_y(vector.GetY() - this->GetY());
        newPoint.set_coord_z(vector.GetZ() - this->GetZ());
        return newPoint;
    }
    
    void operator-=(TVector3D<T>& vector) 
    {
        this->coord_x -= vector.GetX();
        this->coord_y -= vector.GetY();
        this->coord_z -= vector.GetZ();
    }
};

//override de l'operateur << pour pouvoir faire un cout de mon point
//important de le mettre en dehors de la classe
// la référence à l'ostream permet de continuer le cout
template <typename T>
std::ostream& operator<<(std::ostream& os, TPoint<T>& point)
{
    return os <<"("<< point.GetX() << ", " << point.GetY() << ", " << point.GetZ()<<")";
};
