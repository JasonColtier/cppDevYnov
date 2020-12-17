#ifndef IOBJECT_H
#define IOBJECT_H

#include "Color.h"
#include "TRay.h"
#include "TVec3D.h"
#include "TPoint3D.h"
#include <type_traits>

template<typename T>
class IObject
{
	static_assert(std::is_pod<T>::value, "T must be a pod !");
public:
	virtual ~IObject() = default;

	virtual Color GetColorAt(const TPoint3D<T>& _position) const = 0;
	
	virtual double FindIntersection(const TRay<T>& _ray) = 0;
	virtual TVec3D<T> GetNormalAt(const TPoint3D<T>& _point) = 0;
};

#endif // IOBJECT_H
