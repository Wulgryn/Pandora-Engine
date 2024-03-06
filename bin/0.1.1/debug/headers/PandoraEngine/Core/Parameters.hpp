#pragma once
struct Position
{
    int i_x,i_y;
    float f_x,f_y;
    double d_x,d_y;
    long l_x,l_y;
    Position(){}; // Default constructor
    Position(int x, int y)
    {
        i_x = x;
        i_y = y;
        f_x = x;
        f_y = y;
        d_x = x;
        d_y = y;
        l_x = x;
        l_y = y;
    }

    Position(float x, float y)
    {
        i_x = (int)x;
        i_y = (int)y;
        f_x = x;
        f_y = y;
        d_x = (double)x;
        d_y = (double)y;
        l_x = (long)x;
        l_y = (long)y;
    }

    Position(double x, double y)
    {
        i_x = (int)x;
        i_y = (int)y;
        f_x = (float)x;
        f_y = (float)y;
        d_x = x;
        d_y = y;
        l_x = (long)x;
        l_y = (long)y;
    }

    Position(long x, long y)
    {
        i_x = (int)x;
        i_y = (int)y;
        f_x = (float)x;
        f_y = (float)y;
        d_x = (double)x;
        d_y = (double)y;
        l_x = x;
        l_y = y;
    }
};

struct Size
{
    int i_width,i_height;
    float f_width,f_height;
    double d_width,d_height;
    long l_width,l_height;
    Size(){}; // Default constructor
    Size(int width, int height)
    {
        i_width = width;
        i_height = height;
        f_width = width;
        f_height = height;
        d_width = width;
        d_height = height;
        l_width = width;
        l_height = height;
    }

    Size(float width, float height)
    {
        i_width = (int)width;
        i_height = (int)height;
        f_width = width;
        f_height = height;
        d_width = (double)width;
        d_height = (double)height;
        l_width = (long)width;
        l_height = (long)height;
    }

    Size(double width, double height)
    {
        i_width = (int)width;
        i_height = (int)height;
        f_width = (float)width;
        f_height = (float)height;
        d_width = width;
        d_height = height;
        l_width = (long)width;
        l_height = (long)height;
    }

    Size(long width, long height)
    {
        i_width = (int)width;
        i_height = (int)height;
        f_width = (float)width;
        f_height = (float)height;
        d_width = (double)width;
        d_height = (double)height;
        l_width = width;
        l_height = height;
    }
};