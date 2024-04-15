#pragma once
#include "../Core/Parameters.hpp"
#include "../Core/Event.hpp"
#include "Image.hpp"
#include <vector>
#include <map>

#include <string>

class GLFWwindow;
class Window;
class BaseWindow
{
private:
    friend Window;

    ParametersApp::Position windowPosition;
    ParametersApp::Size windowSize;
    std::string windowTitle;
    int windowID;
    int BaseWindowHandlerIndex;
    bool isCreated = false;

    std::map<char*, void*> pointers;
    GLFWwindow* glfw_window;
public:
    BaseWindow();
    virtual void Initialize();

    virtual void ResizeCallback(ParametersApp::Size size);


    void Show();

    void Close();
    int Destroy();
    
    bool ThreadCheck(const char* function = "");
    bool InitCheck(const char* function = "");
    bool IsCreated() { return isCreated; }

    GLFWwindow* GetGLFWWindow() { return glfw_window; }
    int GetWindowID() { return windowID; }
    Image GetCurrentPicture();

    void BindPointer(char* name, void* pointer);
    void* GetPointer(char* name);

    void SetSize(ParametersApp::Size size);
    ParametersApp::Size GetSize() { return windowSize; }

    double GetGLFWTime();

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

    /// @brief Invoked when the window is resized.
    /// @param BaseWindow* The window that is being resized.
    /// @param ParametersApp::Size The new size of the window.
    Event<BaseWindow*, ParametersApp::Size> OnResize;
};

/// @brief Creates and Initializes a new BaseWindow.
/// @return The Initialized BaseWindow.
BaseWindow* createBaseWindow();
