#pragma once
#include "../Core/Parameters.hpp"
#include "../Core/Event.hpp"
#include "Image.hpp"
#include <thread>
#include <vector>


class GLFWwindow;

class BaseWindow
{
private:
    ParametersApp::Position windowPosition;
    ParametersApp::Size windowSize;
    const char* windowTitle;
    int windowID;
    std::thread mainThread;
    int BaseWindowHandlerIndex;
    bool isCreated = false;
protected:
    GLFWwindow* glfw_window;
public:
    BaseWindow();
    virtual void Initialize();
    void Show();

    void Close();
    int Destroy();
    
    bool ThreadCheck(const char* function = "");
    bool InitCheck(const char* function = "");
    bool IsCreated() { return isCreated; }

    GLFWwindow* GetGLFWWindow() { return glfw_window; }
    int GetWindowID() { return windowID; }
    Image GetCurrentPicture();

    /// @brief Invoked before the window is closed.
    /// @param BaseWindow* The window that is being closed.
    Event<BaseWindow*> OnClose;
    /// @brief Invoked before the window is shown.
    /// @param BaseWindow* The window that is being shown.
    Event<BaseWindow*> OnShow;
    /// @brief Invoked before the GetCurrentPicture() is returned.
    /// @param BaseWindow* The window that is being shown.
    /// @param Image* The image that is being returned.
    Event<BaseWindow*, Image*> OnGetCurrentPicture;
};

/// @brief Creates and Initializes a new BaseWindow.
/// @return The Initialized BaseWindow.
BaseWindow* createBaseWindow();
