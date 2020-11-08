#pragma once
#include <iostream>
#include <ostream>
#include "TPoint.h"
#include <math.h>

template <typename T>
class TVector3D
{
    static_assert(std::is_arithmetic<T>::value, "not a number !");

    friend std::ostream& operator<<(std::ostream& os, const TVector3D<int>& vector);
    friend std::ostream& operator<<(std::ostream& os, const TVector3D<float>& vector);
	
private:
    //coordonn�es de mon vecteur
    T delta_x;
    T delta_y;
    T delta_z;

public:
    TVector3D() : delta_x(0), delta_y(0), delta_z(0)
    {
        std::cout << "new vector created : " << delta_x << " " << delta_y << " " << delta_z << std::endl;
    }

    TVector3D(const T& x, const T& y, const T& z) : delta_x(x), delta_y(y), delta_z(z)
    {
        std::cout << "new vector created : " << delta_x << " " << delta_y << " " << delta_z << std::endl;
    }

    //ATTENTION !!! si on ne met pas le & de reference ça crée une nouvelle variable via constructeur par copie !!
    TVector3D(TPoint<T>& point1, TPoint<T>& point2)
    {
        delta_x = point2.GetX() - point1.GetX();
        delta_y = point2.GetY() - point1.GetY();
        delta_z = point2.GetZ() - point1.GetZ();
        std::cout << "new vector created by points : " << delta_x << " " << delta_y << " " << delta_z << std::endl;
    }

    TVector3D(TVector3D& ref_vector) : delta_x(ref_vector.delta_x), delta_y(ref_vector.delta_y),
                                       delta_z(ref_vector.delta_z)
    {
        std::cout << "new vector created by copy : " << delta_x << " " << delta_y << " " << delta_z << std::endl;
    }

    ~TVector3D()
    {
        //std::cout << " ~ ";
        // std::cout<<delta_x<<" " <<delta_y<<" " <<delta_z<<" ";
    }

    /*
     * GETTERS ET SETTERS
     */
    T GetX() { return delta_x; }
    T GetY() { return delta_y; }
    T GetZ() { return delta_z; }
    void set_delta_x(const T& delta_x) { this->delta_x = delta_x; }
    void set_delta_y(const T& delta_y) { this->delta_y = delta_y; }
    void set_delta_z(const T& delta_z) { this->delta_z = delta_z; }

    /*
     * OPERATIONS AVEC =
     */
    void operator+=(T add)
    {
        delta_x += add;
        delta_y += add;
        delta_z += add;
    }

    void operator-=(T sub)
    {
        delta_x -= sub;
        delta_y -= sub;
        delta_z -= sub;
    }

    void operator*=(T mul)
    {
        delta_x *= mul;
        delta_y *= mul;
        delta_z *= mul;
    }

    void operator/=(T div)
    {
        delta_x /= div;
        delta_y /= div;
        delta_z /= div;
    }



    /*
     * OPERTATIONS SIMPLES
     */
    TVector3D operator+(T add)
    {
        TVector3D<T> result;
        result.set_delta_x(this->delta_x + add);
        result.set_delta_y(this->delta_y + add);
        result.set_delta_z(this->delta_z + add);
        return result;
    }

    TVector3D operator-(T sub)
    {
        TVector3D<T> result;
        result.set_delta_x(this->delta_x - sub);
        result.set_delta_y(this->delta_y - sub);
        result.set_delta_z(this->delta_z - sub);
        return result;
    }

    TVector3D operator*(T mul)
    {
        TVector3D<T> result;
        result.set_delta_x(this->delta_x * mul);
        result.set_delta_y(this->delta_y * mul);
        result.set_delta_z(this->delta_z * mul);
        return result;
    }

    TVector3D operator/(T div)
    {
        TVector3D<T> result;
        result.set_delta_x(this->delta_x / div);
        result.set_delta_y(this->delta_y / div);
        result.set_delta_z(this->delta_z / div);
        return result;
    }

    /*
     * OPERATIONS COMPEXES
     */

    void operator*=(TVector3D& vector) //cross product, produit vectoriel
    {
        T tmpX = delta_x;
        T tmpY = delta_y;
        T tmpZ = delta_z;

        delta_x = tmpY * vector.GetZ() - tmpZ * vector.GetY();
        delta_y = tmpZ * vector.GetX() - tmpX * vector.GetZ();
        delta_z = tmpX * vector.GetY() - tmpY * vector.GetX();
    }

    TVector3D operator*(TVector3D& vector) //cross product, produit vectoriel
    {
        TVector3D<T> result;

        result.set_delta_x(this->delta_y * vector.GetZ() - this->delta_z * vector.GetY());
        result.set_delta_y(this->delta_z * vector.GetX() - this->delta_x * vector.GetZ());
        result.set_delta_z(this->delta_x * vector.GetY() - this->delta_y * vector.GetX());
        return result;
    }

    double Magnitude() // ||a|| ou length
    {
        return sqrt(pow(delta_x, 2) + pow(delta_y, 2) + pow(delta_z, 2));
    }

    TVector3D<float> Normalize()
    {
        TVector3D<T> result = *this;
        double mag = result.Magnitude();
        result /= mag;
        return result;
    }

	//renvoit un nouveau vecteur normalisé

    TVector3D Invert()
    {
        TVector3D<T> result = *this;
        result *= -1;
        return result;
    }
};

template <typename T>
T Dot(TVector3D<T>& v1, TVector3D<T>& v2)
{
    return v1.GetX() * v2.GetX() + v1.GetY() * v2.GetY() + v1.GetZ() * v2.GetZ();
}

std::ostream& operator<<(std::ostream& os, const TVector3D<int>& vector)
{
    return os << "(" << vector.delta_x << ", " << vector.delta_y << ", " << vector.delta_z << ")";
};


std::ostream& operator<<(std::ostream& os, const TVector3D<float>& vector)
{
    return os << "(" << vector.delta_x << ", " << vector.delta_y << ", " << vector.delta_z << ")";
};
