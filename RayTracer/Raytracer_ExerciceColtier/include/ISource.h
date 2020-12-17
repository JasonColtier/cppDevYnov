#ifndef TSOURCE_H
#define TSOURCE_H

#include "TPoint3D.h"
#include "Color.h"
#include <type_traits>

template<typename T>
class ISource
{
    static_assert(std::is_pod<T>::value && "T must be a pod !");
public:
    virtual ~ISource() = default;

    virtual TPoint3D<T> GetLightPosition() const = 0;
    virtual Color GetLightColor() const = 0;
};

#endif // TSOURCE_H
