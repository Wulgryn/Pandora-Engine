#pragma once
#include "DLL/dll.hpp"
#include "UTILS/parameters.hpp"

#include "GLFW/glfw3.h"

namespace io
{
    enum class MouseButton
    {
        ANY = -1,
        LEFT = GLFW_MOUSE_BUTTON_LEFT,
        RIGHT = GLFW_MOUSE_BUTTON_RIGHT,
        MIDDLE = GLFW_MOUSE_BUTTON_MIDDLE,
        BUTTON_4 = GLFW_MOUSE_BUTTON_4,
        BUTTON_5 = GLFW_MOUSE_BUTTON_5,
        BUTTON_6 = GLFW_MOUSE_BUTTON_6,
        BUTTON_7 = GLFW_MOUSE_BUTTON_7,
        BUTTON_8 = GLFW_MOUSE_BUTTON_8,
        LAST = GLFW_MOUSE_BUTTON_LAST
    };
    namespace mouse
    {
        DLL utils::Position getWindowPosition();
        DLL utils::Position getScreenPosition();

        DLL bool getMouseButton(MouseButton button);
        DLL bool getMouseButtonReleased(MouseButton button);
        DLL bool getMouseButtonDown(MouseButton button);

        DLL double getMouseScroll();

        DLL void setScreenPosition(utils::Position pos);
        DLL void setWindowPosition(utils::Position pos);
    }// namespace mouse
}// namespace io
