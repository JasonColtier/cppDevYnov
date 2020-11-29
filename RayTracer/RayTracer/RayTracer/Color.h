#pragma once
#include <iostream>
#include <ostream>
#include <memory>

#include "TPoint.h"


class Color
{

    friend std::ostream& operator<<(std::ostream& os, const Color& color);

public:

    Color() : Red(1), Green(1), Blue(1), Alpha(1)
    {
    }

    Color(const double& r, const double& g, const double& b, const double& a) : Red(r), Green(g), Blue(b), Alpha(a)
    {
    }

    Color(const Color& color) = default;
    Color(Color&& color) = default;

    ~Color() = default;


    double GetRed() const { return Red; }
    double GetGreen() const { return Green; }
    double GetBlue() const { return Blue; }
    double GetAlpha() const { return Alpha; }

    void SetRed(const double& red) { Red = red; }
    void SetGreen(const double& green) { Green = green; }
    void SetBlue(const double& blue) { Blue = blue; }
    void SetAlpha(const double& alpha) { Alpha = alpha; }

    /*
     * Operations de couleur   avec =
     */

    Color& operator=(const Color& color) = default;
    Color& operator=(Color&& color) = default;

    Color& operator+=(const Color& color)
    {
        Red += color.Red;
        Green += color.Green;
        Blue += color.Blue;
        Alpha += color.Alpha;
        return *this;
    };

    Color& operator-=(const Color& color)
    {
        Red -= color.Red;
        Green -= color.Green;
        Blue -= color.Blue;
        Alpha -= color.Alpha;
        return *this;
    };

    Color& operator*=(const Color& color)
    {
        Red *= color.Red;
        Green *= color.Green;
        Blue *= color.Blue;
        Alpha *= color.Alpha;
        return *this;
    };

    Color& operator*=(const double& scale)
    {
        Red *= scale;
        Green *= scale;
        Blue *= scale;
        Alpha *= scale;
        return *this;
    };

    Color& operator/=(const Color& color)
    {
        Red /= color.Red;
        Green /= color.Green;
        Blue /= color.Blue;
        Alpha /= color.Alpha;
        return *this;
    };

    Color& operator/=(const double& scale)
    {
        Red /= scale;
        Green /= scale;
        Blue /= scale;
        Alpha /= scale;
        return *this;
    };

    /*
     * operation directes
     */

    Color& operator+(const Color& color)
    {
        Color newColor;
        newColor.Red = Red + color.Red;
        newColor.Green = Green + color.Green;
        newColor.Blue = Blue + color.Blue;
        newColor.Alpha = Alpha + color.Alpha;
        return newColor;
    };

    Color& operator-(const Color& color)
    {
        Color newColor;
        newColor.Red = Red - color.Red;
        newColor.Green = Green - color.Green;
        newColor.Blue = Blue - color.Blue;
        newColor.Alpha = Alpha - color.Alpha;
        return newColor;
    };

    Color& operator*(const Color& color)
    {
        Color newColor;
        newColor.Red = Red * color.Red;
        newColor.Green = Green * color.Green;
        newColor.Blue = Blue * color.Blue;
        newColor.Alpha = Alpha * color.Alpha;
        return newColor;
    };

    Color& operator*(const double scale)
    {
        Color newColor;
        newColor.Red = Red * scale;
        newColor.Green = Green * scale;
        newColor.Blue = Blue * scale;
        newColor.Alpha = Alpha * scale;
        return newColor;
    };

    Color& operator/(const Color& color)
    {
        Color newColor;
        newColor.Red = Red / color.Red;
        newColor.Green = Green / color.Green;
        newColor.Blue = Blue / color.Blue;
        newColor.Alpha = Alpha / color.Alpha;
        return newColor;
    };

    Color& operator/(const double scale)
    {
        Color newColor;
        newColor.Red = Red / scale;
        newColor.Green = Green / scale;
        newColor.Blue = Blue / scale;
        newColor.Alpha = Alpha / scale;
        return newColor;
    };

    double Brightness()//la luminosité de ma couleur
    {
        return (Red + Green + Blue) / 3;
    };
    
    Color Average (const Color& color)//la moyenne de chaque channel entre 2 couleurs
    {
        Color newColor((color.Red + Red)/2,(color.Green + Green)/2,(color.Blue + Blue)/2,(color.Alpha + Alpha)/2);
        return newColor;
    };
    

protected:
    double Red;
    double Green;
    double Blue;
    double Alpha;
};

std::ostream& operator<<(std::ostream& os, const Color& color)
{
    return os << "(" << color.Red << ", " << color.Green << ", " << color.Blue <<  ", " << color.Alpha << ")";
};

