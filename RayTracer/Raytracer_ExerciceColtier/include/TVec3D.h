#ifndef	TVEC3D_H
#define	TVEC3D_H

#include "TPoint3D.h"
#include <type_traits>
#include <ostream>

template <typename T>
class TVec3D
{
	static_assert(std::is_pod<T>::value, "T	must be	POD");

	template <typename>
	friend auto	operator+(const	TVec3D&	_lhs, const	TVec3D&	_rhs);

	template <typename>
	friend auto	operator-(const	TVec3D&	_lhs, const	TVec3D&	_rhs);

	template <typename>
	friend auto	operator*(const	TVec3D&	_lhs, const	TVec3D&	_rhs);

	template <typename>
	friend auto	operator*(const	T& _lhs, const TVec3D& _rhs);

	template <typename>
	friend auto	operator*(const	TVec3D&	_lhs, const	T& _rhs);

	template <typename>
	friend auto	operator/(const	TVec3D&	_lhs, const	T& _rhs);

	template<typename>
	friend TPoint3D<T> operator+(const TPoint3D<T>&	_lhs, const	TVec3D&	_rhs);

	template<typename>
	friend TPoint3D<T> operator-(const TPoint3D<T>&	_lhs, const	TVec3D&	_rhs);

	friend std::ostream& operator<<(std::ostream& _os, const TVec3D<int>& _vec);
	friend std::ostream& operator<<(std::ostream& _os, const TVec3D<double>& _vec);

public:

	TVec3D()
		: TVec3D(0,	0, 0)
	{
	}

	TVec3D(const T&	_x,	const T& _y, const T& _z)
		: m_x(_x)
		, m_y(_y)
		, m_z(_z)
	{
	}

	TVec3D(const TPoint3D<T>& _begin, const	TPoint3D<T>& _end)
		: m_x(_end.X() - _begin.X())
		, m_y(_end.Y() - _begin.Y())
		, m_z(_end.Z() - _begin.Z())
	{
	}

	~TVec3D() =	default;

	TVec3D(const TVec3D& _vec) = default;

	TVec3D(TVec3D&&	_vec) =	default;

	TVec3D&	operator=(const	TVec3D&	_vec) =	default;
	TVec3D&	operator=(TVec3D&& _vec) = default;

	auto& operator+=(const TVec3D& _vec)
	{
		m_x	+= _vec.m_x;
		m_y	+= _vec.m_y;
		m_z	+= _vec.m_z;
		return *this;
	}

	auto& operator-=(const TVec3D& _vec)
	{
		m_x	-= _vec.m_x;
		m_y	-= _vec.m_y;
		m_z	-= _vec.m_z;
		return *this;
	}

	T X() const	{ return m_x; }
	T Y() const	{ return m_y; }
	T Z() const	{ return m_z; }

	double Magnitude() const
	{
		return std::sqrt(std::pow(m_x, 2) +	std::pow(m_y, 2) + std::pow(m_z, 2));
	}

	TVec3D<double> Normalized()	const
	{
		const auto norm	= Magnitude();
		return { m_x / norm, m_y / norm, m_z / norm	};
	}

	TVec3D Opposite() const
	{
		return { -m_x, -m_y, -m_z };
	}

	double DotProduct(const	TVec3D&	_vec) const
	{
		return m_x * _vec.m_x +	m_y	* _vec.m_y + m_z * _vec.m_z;
	}

	TVec3D&	operator*=(const TVec3D& _vec)
	{
		TVec3D temp(m_x, m_y, m_z);
		m_x	= temp.m_y * _vec.m_z -	temp.m_z * _vec.m_y;
		m_y	= temp.m_z * _vec.m_x -	temp.m_x * _vec.m_z;
		m_z	= temp.m_x * _vec.m_y -	temp.m_y * _vec.m_x;
		return *this;
	}

	TVec3D&	operator*=(const T&	_k)
	{
		m_x	*= _k;
		m_y	*= _k;
		m_z	*= _k;
		return *this;
	}

	TVec3D&	operator/=(const T&	_k)
	{
		m_x	/= _k;
		m_y	/= _k;
		m_z	/= _k;
		return *this;
	}

private:
	T m_x;
	T m_y;
	T m_z;
};

template <typename T>
auto operator+(const TVec3D<T>&	_lhs, const	TVec3D<T>& _rhs)
{
	auto outputVector =	_lhs;
	return outputVector	+= _rhs;
}

template <typename T>
auto operator-(const TVec3D<T>&	_lhs, const	TVec3D<T>& _rhs)
{
	auto outputVector =	_lhs;
	return outputVector	-= _rhs;
}

template <typename T>
auto operator*(const TVec3D<T>&	_lhs, const	TVec3D<T>& _rhs)
{
	auto outputVector =	_lhs;
	return outputVector	*= _rhs;
}

template <typename T>
TVec3D<T> operator*(const T& _lhs, const TVec3D<T>&	_rhs)
{
	auto outputVector =	_rhs;
	return outputVector	*= _lhs;
}

template <typename T>
TVec3D<T> operator*(const TVec3D<T>& _lhs, const T&	_rhs)
{
	auto outputVector =	_lhs;
	return outputVector	*= _rhs;
}

template <typename T>
TVec3D<T> operator/(const TVec3D<T>& _lhs, const T&	_rhs)
{
	auto outputVector =	_lhs;
	return outputVector	/= _rhs;
}

template <typename T>
TPoint3D<T>	operator+(const	TPoint3D<T>& _lhs, const TVec3D<T>&	_rhs)
{
	return TPoint3D<T>(_lhs.X()	+ _rhs.X(),	_lhs.Y() + _rhs.Y(), _lhs.Z() +	_rhs.Z());
}

template <typename T>
TPoint3D<T>	operator-(const	TPoint3D<T>& _lhs, const TVec3D<T>&	_rhs)
{
	return TPoint3D<T>(_lhs.X()	- _rhs.X(),	_lhs.Y() - _rhs.Y(), _lhs.Z() -	_rhs.Z());
}

std::ostream& operator<<(std::ostream& _os,	const TVec3D<int>& _lhs)
{
	_os	<< "[ "	<< _lhs.m_x	<< ", "	<< _lhs.m_y	<< ", "	<< _lhs.m_z	<< " ]";
	return _os;
}

std::ostream& operator<<(std::ostream& _os,	const TVec3D<double>& _lhs)
{
	_os	<< "[ "	<< _lhs.m_x	<< ", "	<< _lhs.m_y	<< ", "	<< _lhs.m_z	<< " ]";
	return _os;
}

#endif // TVEC3D_H
