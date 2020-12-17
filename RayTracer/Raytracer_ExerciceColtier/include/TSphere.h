#ifndef	TSPHERE_H
#define	TSPHERE_H

#include "TPoint3D.h"
#include "TVec3D.h"
#include "Color.h"
#include "IObject.h"
#include <type_traits>

template<typename T>
class TSphere :	public IObject<T>
{
	static_assert(std::is_pod<T>::value, "T	must be	a pod !");
public:

	TSphere()
		: m_center()
		, m_radius(1.0)
		, m_color(0.5, 0.5,	0.5, 0.0)
	{
		
	}
	
	TSphere(const TPoint3D<T>& _center,	const T& _radius, const	Color& _color)
		: m_center(_center)
		, m_radius(_radius)
		, m_color(_color)
	{
		
	}

	~TSphere() = default;

	auto GetCenter() const { return	m_center; }
	auto GetRadius() const { return	m_radius; }
	Color GetColorAt(const TPoint3D<T>& /*_position*/) const override	{ return m_color; }

	TVec3D<T> GetNormalAt(const	TPoint3D<T>& _point) override
	{
		return TVec3D<T>(m_center, _point).Normalized();
	}

	double FindIntersection(const TRay<T>& _ray) override
	{
		// TODO 1) First thing to do !
		// Write Sphere intersection algorithm.
		// Do not forget that if there is no intersection you have to return -1

		//https://en.wikipedia.org/wiki/Line%E2%80%93sphere_intersection
		//on applique la formule donnée pour le calcul
		
		//on crée un vecteur qui va du centre du raycast vers le centre de la sphère
		TVec3D<double> originToCenter( m_center,_ray.GetOrigin());

		//on calcule la norme au carré de notre vecteur direction
		double a = _ray.GetDirection().DotProduct(_ray.GetDirection());

		//première partie de l'équation
		double b = 2.0 * (_ray.GetDirection().DotProduct(originToCenter));

		double c = originToCenter.DotProduct(originToCenter) - m_radius*m_radius;
		double d = b*b - 4*a*c;
		if(d < 0){
			return -1.0;//si notre sphère n'a rien touché
		}
		else{
			return (-b - sqrt(d)) / (2.0*a);//on retourne la distance depuis l'origine du ray
		}
	}
	
private:
	TPoint3D<T>	m_center;
	T m_radius;
	Color m_color;
};


#endif // TSPHERE_H
