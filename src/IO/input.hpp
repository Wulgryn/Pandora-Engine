#pragma once
#include "DLL/dll.hpp"

#define GLFW_INCLUDE_NONE
#include "GLFW/glfw3.h"

#include <vector>
#include <map>

namespace io
{
    class Window;

    class DLL Input
    {
    private:
        std::vector<bool*> keys_list;
        Window *window;
        static void keyCallback(GLFWwindow *window, int key, int scancode, int action, int mods);
        static void mouseButtonCallback(GLFWwindow *window, int button, int action, int mods);
        std::vector<bool*> mouse_buttons_list;
    public:
        int anyKey = 0;
        int anyKeyPressed = 0;
        int anyKeyDown = 0;
        int anyKeyReleased = 0;
        int anyKeyUp = 0;

        int anyMouseButton = 0;
        int anyMouseButtonReleased = 0;
        int anyMouseButtonDown = 0;
        Input(Window *window);

        Window *getWindow();

        void registerKey(int key);
        void registerMouseButton(int key);


        bool getKey(int key);
        bool getKeyPressed(int key);
        bool getKeyDown(int key);
        bool getKeyReleased(int key);
        bool getKeyUp(int key);

        bool getMouseButtonDown(int button);
        bool getMouseButton(int button);
        bool getMouseButtonReleased(int button);

        void resetInputs();
    };
}