#ifndef UNITS_HPP
#define UNITS_HPP

#include "Macros.h"

namespace PandoraEngine::Units
{
    struct DLL RectPoint
    {
        int X;
        int Y;
    }; // struct Point

    struct DLL RectSize
    {
        int Width;
        int Height;
    }; // struct RectSize

} // namespace PandoraEngine::Units

#endif // UNITS_HPP