#ifndef TPOINT3D_H
#define TPOINT3D_H

#include <type_traits>

template<typename T>
struct TPoint3D
{
	static_assert(std::is_pod<T>::value, "T must be POD");

public:
	TPoint3D()
		: TPoint3D(0, 0, 0)
	{}
	
	TPoint3D(const T& _x, const T& _y, const T& _z)
		: m_x(_x)
		, m_y(_y)
		, m_z(_z)
	{
	}

	T X() const { return m_x; }
	T Y() const { return m_y; }
	T Z() const { return m_z; }

private:
	T m_x;
	T m_y;
	T m_z;
};
#endif // TPOINT3D_H
