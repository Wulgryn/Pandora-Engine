#pragma once

/// @brief Parameters for the application
namespace ParametersApp
{
    struct Position
    {
        int i_x, i_y;
        float f_x, f_y;
        double d_x, d_y;
        long l_x, l_y;

        Position();
        Position(int x, int y);
        Position(float x, float y);
        Position(double x, double y);
        Position(long x, long y);
    };

    struct Size
    {
        int i_width, i_height;
        float f_width, f_height;
        double d_width, d_height;
        long l_width, l_height;

        Size();
        Size(int width, int height);
        Size(float width, float height);
        Size(double width, double height);
        Size(long width, long height);
    };
}
/// @brief Parameters for the 2D Objects
namespace Parameters2D
{
    struct Position
    {
        double x, y;
        Position();
        Position(double x, double y);
    };

    struct Size
    {
        double width, height;
        Size();
        Size(double width, double height);
    };

    struct Rotation
    {
        double z;
        Rotation();
        Rotation(double z);
    };

    struct Scale
    {
        double x, y;
        Scale();
        Scale(double x, double y);
    };
}