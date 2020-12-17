#ifndef COLOR_H
#define COLOR_H
#include <iosfwd>

class Color
{
	friend Color operator+(const Color& _lhs, const Color& _rhs);
    friend Color operator-(const Color& _lhs, const Color& _rhs);
	friend Color operator*(const Color& _lhs, const Color& _rhs);
	friend Color operator*(const Color& _lhs, const double& _rhs);
    friend Color operator*(const double& _lhs, const Color& _rhs);
	friend Color operator/(const Color& _lhs, const double& _rhs);
    friend std::ostream& operator<<(std::ostream& _os, const Color& _rhs);
	
public:
	Color();

	Color(const double& _red, const double& _green, const double& _blue, const double& _alpha);

	Color(const Color& _color) = default;
	Color(Color&& _color) = default;
	~Color() = default;

	Color& operator=(const Color& _color) = default;
	Color& operator=(Color&& _color) = default;
	Color& operator+=(const Color& _color);
	Color& operator*=(const Color& _color);
	Color& operator*=(const double& _scale);
	Color& operator/=(const double& _scale);
    Color& operator-=(const Color& _color);

	double Red() const;
	double Green() const;
	double Blue() const;
	double Alpha() const;

	void SetRed(const double& _red);
	void SetGreen(const double& _green);
	void SetBlue(const double& _blue);
	void SetAlpha(const double& _alpha);

	double Brightness() const;
	Color Average(const Color& _color) const;
	Color Clip();

private:
	double m_red;
	double m_green;
	double m_blue;
	double m_alpha;
};

#endif // COLOR_H
