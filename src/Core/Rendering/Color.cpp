#include "Color.hpp"

Color::Color()
{
    r = g = b = a = 255;
    Fr = Fg = Fb = Fa = 1.0f;
}

Color::Color(Byte r, Byte g, Byte b, Byte a)
{
    this->r = r;
    this->g = g;
    this->b = b;
    this->a = a;
    Normalize();
}

Color::Color(float r, float g, float b, float a)
{
    Fr = r;
    Fg = g;
    Fb = b;
    Fa = a;
    Denormalize();
}

Color::Color(int r, int g, int b, int a)
{
    this->r = r;
    this->g = g;
    this->b = b;
    this->a = a;
    Normalize();
}

Color::Color(Colors color)
{
    Set(color);
}

void Color::Normalize()
{
    Fr = r / 255.0f;
    Fg = g / 255.0f;
    Fb = b / 255.0f;
    Fa = a / 255.0f;
}

void Color::Denormalize()
{
    r = Fr * 255;
    g = Fg * 255;
    b = Fb * 255;
    a = Fa * 255;
}

void Color::Set(Byte r, Byte g, Byte b, Byte a)
{
    this->r = r;
    this->g = g;
    this->b = b;
    this->a = a;
    Normalize();
}

void Color::Set(float r, float g, float b, float a)
{
    Fr = r;
    Fg = g;
    Fb = b;
    Fa = a;
    Denormalize();
}

void Color::Set(Colors color)
{
    switch (color)
    {
    case Colors::WHITE:
        Set(255,255,255);
        break;
    case Colors::BLACK:
        Set(0,0,0);
        break;
    case Colors::RED:
        Set(255,0,0);
        break;
    case Colors::GREEN:
        Set(0,255,0);
        break;
    case Colors::BLUE:
        Set(0,0,255);
        break;
    case Colors::YELLOW:
        Set(255,255,0);
        break;
    case Colors::MAGENTA:
        Set(255,0,255);
        break;
    case Colors::CYAN:
        Set(0,255,255);
        break;
    case Colors::ORANGE:
        Set(255,165,0);
        break;
    case Colors::PURPLE:
        Set(128,0,128);
        break;
    case Colors::PINK:
        Set(255,192,203);
        break;
    case Colors::BROWN:
        Set(165,42,42);
        break;
    case Colors::GRAY:
        Set(128,128,128);
        break;
    default:
        break;
    }
}

void Color::Set(int r, int g, int b, int a)
{
    this->r = r;
    this->g = g;
    this->b = b;
    this->a = a;
    Normalize();
}

Color* Color::operator=(Colors color)
{
    Set(color);
    return this;
}