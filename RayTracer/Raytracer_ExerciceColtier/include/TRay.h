#ifndef TRAY_H
#define TRAY_H

#include "TVec3D.h"
#include "TPoint3D.h"

#include <type_traits>
#include <utility>

template<typename T>
class TRay
{
	static_assert(std::is_pod<T>::value, "T must be POD");

public:
	TRay()
		: TRay(TPoint3D<T>(), TVec3D<T>(1, 0, 0))
	{
	}
	
	TRay(const TPoint3D<T>& _origin, const TVec3D<T>& _direction)
		: m_rays{_origin, _direction}
	{
		
	}

	auto GetOrigin() const { return m_rays.first; }
	auto GetDirection() const { return m_rays.second; }
	
private:
	std::pair<TPoint3D<T>, TVec3D<T>> m_rays;
	
};

#endif // TRAY_H
