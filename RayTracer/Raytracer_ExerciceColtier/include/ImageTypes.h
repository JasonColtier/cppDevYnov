#ifndef IMAGETYPES_H
#define IMAGETYPES_H
#include <type_traits>

template <typename T>
struct TRgb
{
	static_assert(std::is_pod<T>::value, "T must be POD");

	explicit TRgb(T _r = 0, T _g = 0, T _b = 0)
		: r(_r)
		, g(_g)
		, b(_b)
	{
		
	}

	~TRgb() = default;
	
	T r;
	T g;
	T b;
};


#endif // IMAGETYPES_H
