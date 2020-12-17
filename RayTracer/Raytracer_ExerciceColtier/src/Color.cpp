#include "Color.h"
#include <ostream>
#include <algorithm>

Color::Color(const double& _red, const double& _green, const double& _blue, const double& _alpha)
	: m_red(_red)
    , m_green(_green)
    , m_blue(_blue)
	, m_alpha(_alpha)
{
}

Color::Color()
	: Color(0.5, 0.5, 0.5, 0.0)
{
}

Color& Color::operator+=(const Color& _color)
{
	m_red += _color.m_red;
	m_green += _color.m_green;
	m_blue += _color.m_blue;
	return *this;
}

Color& Color::operator*=(const Color& _color)
{
	m_red *= _color.m_red;
	m_green *= _color.m_green;
	m_blue *= _color.m_blue;
	return *this;
}

Color& Color::operator*=(const double& _scale)
{
	m_red *= _scale;
	m_green *= _scale;
	m_blue *= _scale;
	return *this;
}

Color& Color::operator/=(const double& _scale)
{
	m_red /= _scale;
	m_green /= _scale;
	m_blue /= _scale;
	return *this;
}

Color& Color::operator-=(const Color& _color)
{
    m_red -= _color.m_red;
    m_green -= _color.m_green;
    m_blue -= _color.m_blue;
    return *this;
}

double Color::Red() const
{
	return m_red;
}

double Color::Green() const
{
	return m_green;
}

double Color::Blue() const
{
	return m_blue;
}

double Color::Alpha() const
{
	return m_alpha;
}

void Color::SetRed(const double& _red)
{
	m_red = _red;
}

void Color::SetGreen(const double& _green)
{
	m_green = _green;
}

void Color::SetBlue(const double& _blue)
{
	m_blue = _blue;
}

void Color::SetAlpha(const double& _alpha)
{
	m_alpha = _alpha;
}

double Color::Brightness() const
{
	return (m_red + m_green + m_blue) / 3.0;
}

Color Color::Average(const Color& _color) const
{
    return { (m_red + _color.Red()) / 2.0, (m_green + _color.Green()) / 2.0, (m_blue + _color.Blue()) / 2.0, m_alpha };
}

Color Color::Clip()
{
	const auto  sumColor = m_red + m_green + m_blue;
	const auto colorOverflow = sumColor - 3.0;
	if (colorOverflow > 0) {
		m_red *= 1.0 + colorOverflow / sumColor;
		m_green *= 1.0 + colorOverflow / sumColor;
		m_blue *= 1.0 + colorOverflow / sumColor;
	}

	m_red = std::clamp(m_red, 0.0, 1.0);
	m_green = std::clamp(m_green, 0.0, 1.0);
	m_blue = std::clamp(m_blue, 0.0, 1.0);

	return { m_red, m_green, m_blue, m_alpha };
}

Color operator+(const Color& _lhs, const Color& _rhs)
{
	auto outColor = _lhs;
	return outColor += _rhs;
}

Color operator-(const Color& _lhs, const Color& _rhs)
{
    auto outColor = _lhs;
    return outColor -= _rhs;
}

Color operator*(const Color& _lhs, const Color& _rhs)
{
	auto outColor = _lhs;
	return outColor *= _rhs;
}

Color operator*(const Color& _lhs, const double& _rhs)
{
	auto outColor = _lhs;
	return outColor *= _rhs;
}

Color operator*(const double& _lhs, const Color& _rhs)
{
    auto outColor = _rhs;
    return outColor *= _lhs;
}

Color operator/(const Color& _lhs, const double& _rhs)
{
	auto outColor = _lhs;
	return outColor /= _rhs;
}

std::ostream& operator<<(std::ostream& _os, const Color& _rhs)
{
    _os << "RGBA(" << _rhs.m_red << ", " << _rhs.m_green << ", " << _rhs.m_blue << ", " << _rhs.Alpha() << ")";
    return _os;
}

