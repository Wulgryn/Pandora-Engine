#pragma once

#include "../Types.hpp"

enum class Colors
{
    WHITE,
    BLACK,
    RED,
    GREEN,
    BLUE,
    YELLOW,
    MAGENTA,
    CYAN,
    ORANGE,
    PURPLE,
    PINK,
    BROWN,
    GRAY
    // TODO : Add more colors
    //// LIGHT_GRAY,
    //// DARK_GRAY,
    //// LIGHT_RED,
    //// LIGHT_GREEN,
    //// LIGHT_BLUE,
    //// LIGHT_YELLOW,
    //// LIGHT_MAGENTA,
    //// LIGHT_CYAN,
    //// LIGHT_ORANGE,
    //// LIGHT_PURPLE,
    //// LIGHT_PINK,
    //// LIGHT_BROWN,
    //// LIGHT_GRAY,
    //// DARK_GRAY,
    //// DARK_RED,
    //// DARK_GREEN,
    //// DARK_BLUE,
    //// DARK_YELLOW,
    //// DARK_MAGENTA,
    //// DARK_CYAN,
    //// DARK_ORANGE,
    //// DARK_PURPLE,
    //// DARK_PINK,
    //// DARK_BROWN,
    //// DARK_GRAY
};



struct Color
{
    Byte r, g, b, a;
    float Fr, Fg, Fb, Fa;

    Color();
    Color(Byte r, Byte g, Byte b, Byte a = 255);
    Color(float r, float g, float b, float a = 1.0f);
    /// @brief Set the color with the given values
    /// @param r The red value
    /// @param g The green value
    /// @param b The blue value
    /// @param a The alpha value
    /// @warning The values should be between 0 and 255
    /// @note This method is only to prevent compatibility issues with INT values.
    Color(int r, int g, int b, int a = 255);
    Color(Colors color);

    void Normalize();
    void Denormalize();

    void Set(Byte r, Byte g, Byte b, Byte a = 255);
    void Set(float r, float g, float b, float a = 1.0f);
    void Set(Colors color);
    /// @brief Set the color with the given values
    /// @param r The red value
    /// @param g The green value
    /// @param b The blue value
    /// @param a The alpha value
    /// @warning The values should be between 0 and 255
    /// @note This method is only to prevent compatibility issues with INT values.
    void Set(int r, int g, int b, int a = 255);

    Color* operator=(Colors color);
};