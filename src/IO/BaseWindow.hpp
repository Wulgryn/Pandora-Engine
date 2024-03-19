#pragma once
#include "../Core/Parameters.hpp"
#include "Image.hpp"
#include <thread>


class GLFWwindow;

class BaseWindow
{
private:
    Position windowPosition;
    Size windowSize;
    const char* windowTitle;
    GLFWwindow* glfw_window;
    std::thread mainThread;
    int windowID;

    bool ThreadCheck();
public:
    BaseWindow();
    void Initialize();
    void Show();

    void Render();

    void Close();
    void Destroy();

    GLFWwindow* GetGLFWWindow() { return glfw_window; }
    int GetWindowID() { return windowID; }
    Image GetCurrentPicture();
};

BaseWindow* createBaseWindow();