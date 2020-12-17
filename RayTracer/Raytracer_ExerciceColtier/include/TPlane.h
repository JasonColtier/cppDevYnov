#ifndef TPLANE_H
#define TPLANE_H

#include "IObject.h"
#include "TVec3D.h"
#include "Color.h"
#include <type_traits>

template<typename T>
class TPlane : public IObject<T>
{
	static_assert(std::is_pod<T>::value, "T must be a pod !");
public:
	TPlane()
		: m_normal(TVec3D<T>(1, 0, 0))
		, m_distance(0)
		, Color(0.5, 0.5, 0.5, 0)
	{
		
	}
	
	TPlane(const TVec3D<T>& _normal, const T& _distance, const Color& _color)
		: m_normal(_normal)
		, m_distance(_distance)
		, m_color(_color)
	{
		
	}

	auto GetNormal() const { return m_normal; }
	auto GetDistanceFromOrigin() const { return m_distance; }

	Color GetColorAt(const TPoint3D<T>& _position) const override
	{
        if (m_color.Alpha() == 2.0)
        {
            const auto square = static_cast<int>(std::floor(_position.X())) + static_cast<int>(std::floor(_position.Z()));
            if ((square % 2) == 0)
                return Color(0.0, 0.0, 0.0, m_color.Alpha());

            return Color(1.0, 1.0, 1.0, m_color.Alpha());
        }

        return m_color;
	}

	TVec3D<T> GetNormalAt(const TPoint3D<T>& _point) override { return m_normal; }
	
	double FindIntersection(const TRay<T>& _ray) override
	{
		const auto direction = _ray.GetDirection();
		const auto a = direction.DotProduct(m_normal);
		if (a == 0)
		{
			// ray direction and normal of the plan are //
			return -1.0;
		}
		else
		{
            const TVec3D<T> originVec(_ray.GetOrigin().X(), _ray.GetOrigin().Y(), _ray.GetOrigin().Z());
			const double b = m_normal.DotProduct(originVec + (m_normal * m_distance).Opposite());
			return -1.0 * b / static_cast<double>(a);
		}
	}
	
private:
	TVec3D<T> m_normal;
	T m_distance;
	Color m_color;
	
};

#endif // TPLANE_H
