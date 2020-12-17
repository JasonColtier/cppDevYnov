#ifndef TLIGHT_H
#define TLIGHT_H

#include "TPoint3D.h"
#include "Color.h"
#include "ISource.h"
#include <type_traits>

template<typename T>
class TLight : public ISource<T>
{
	static_assert(std::is_pod<T>::value, "T must be a pod !");

public:
	TLight()
		: m_position()
		, m_color()
	{
		
	}
	
	TLight(const TPoint3D<T>& _position, const Color& _color)
		: m_position(_position)
		, m_color(_color)
	{
		
	}

	~TLight() = default;

    TPoint3D<T> GetLightPosition() const override { return m_position; }
    Color GetLightColor() const override { return m_color; }

protected:
    TPoint3D<T> m_position;
    Color m_color;
};

#endif // TLIGHT_H
