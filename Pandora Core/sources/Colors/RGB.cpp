#include "Colors.hpp"
using namespace Colors;
#pragma region RGB
RGB::RGB()
{
    RGB::red = 0;
    RGB::green = 0;
    RGB::blue = 0;
}
RGB::RGB(byte red, byte green, byte blue)
{
    RGB::red = red;
    RGB::green = green;
    RGB::blue = blue;
}

RGB RGB::GetRGB()
{
    return *this;
}

RGBA RGB::GetRGBA()
{
    RGBA rgba = RGBA(RGB::red,RGB::green,RGB::blue,1.0);
    return rgba;
}
#pragma endregion RGB

#pragma region RGBA
class Colors::RGBA
{
    byte red;
    byte green;
    byte blue;
    double alpha;
    RGBA() : red(0),green(0),blue(0),alpha(0){};
    RGBA(byte red, byte green, byte blue)
    {
        this->red = red;
        this->green = green;
        this->blue = blue;
    }
    RGBA(byte red, byte green, byte blue, double alpha)
    {
        this->red = red;
        this->green = green;
        this->blue = blue;
        this->alpha = alpha;
    }

    RGBA GetRGBA()
    {
        return *this;
    }

};
#pragma endregion RGBA