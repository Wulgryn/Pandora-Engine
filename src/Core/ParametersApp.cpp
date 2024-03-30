#include "Parameters.hpp"

namespace ParametersApp
{
    //______________________________________________________________________________________________________________________
// POSITION  |  POSITION  |  POSITION  |  POSITION  |  POSITION  |  POSITION  |  POSITION  |  POSITION  |  POSITION  |  POSITION  |  POSITION  |  POSITION  |  POSITION  |  POSITION  |  POSITION  |  POSITION  |  POSITION
//______________________________________________________________________________________________________________________
#pragma region POSITION

    Position::Position()
    {
        i_x = 0;
        i_y = 0;
        f_x = 0;
        f_y = 0;
        d_x = 0;
        d_y = 0;
        l_x = 0;
        l_y = 0;
    }

    Position::Position(int x, int y)
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

    Position::Position(float x, float y)
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

    Position::Position(double x, double y)
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

    Position::Position(long x, long y)
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

//______________________________________________________________________________________________________________________
// POSITION  |  POSITION  |  POSITION  |  POSITION  |  POSITION  |  POSITION  |  POSITION  |  POSITION  |  POSITION  |  POSITION  |  POSITION  |  POSITION  |  POSITION  |  POSITION  |  POSITION  |  POSITION  |  POSITION
//______________________________________________________________________________________________________________________
#pragma endregion POSITION

//______________________________________________________________________________________________________________________
// SIZE  |  SIZE  |  SIZE  |  SIZE  |  SIZE  |  SIZE  |  SIZE  |  SIZE  |  SIZE  |  SIZE  |  SIZE  |  SIZE  |  SIZE  |  SIZE  |  SIZE  |  SIZE  |  SIZE
//______________________________________________________________________________________________________________________
#pragma region SIZE

    Size::Size()
    {
        i_width = 0;
        i_height = 0;
        f_width = 0;
        f_height = 0;
        d_width = 0;
        d_height = 0;
        l_width = 0;
        l_height = 0;
    }

    Size::Size(int width, int height)
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

    Size::Size(float width, float height)
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

    Size::Size(double width, double height)
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

    Size::Size(long width, long height)
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

    Size* Size::operator=(Size size)
    {
        i_width = size.i_width;
        i_height = size.i_height;
        f_width = size.f_width;
        f_height = size.f_height;
        d_width = size.d_width;
        d_height = size.d_height;
        l_width = size.l_width;
        l_height = size.l_height;
        return this;
    }

//______________________________________________________________________________________________________________________
// SIZE  |  SIZE  |  SIZE  |  SIZE  |  SIZE  |  SIZE  |  SIZE  |  SIZE  |  SIZE  |  SIZE  |  SIZE  |  SIZE  |  SIZE  |  SIZE  |  SIZE  |  SIZE  |  SIZE
//______________________________________________________________________________________________________________________
#pragma endregion SIZE
}
