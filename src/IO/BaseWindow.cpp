#include "BaseWindow.hpp"
#include "IO/Monitor.hpp"
#include "Debug/Console.hpp"
#include "WindowsHandler.hpp"
#include "Core/Application.hpp"
#include "Core/Thread.hpp"

#define GLFW_INCLUDE_NONE
#include "GLFW/glfw3.h"
#include "glad/gl.h"

#include <stdexcept>
#include <thread>
#include <iostream>

using namespace std;
using namespace ParametersApp;

static int windowCount = 0;                     


BaseWindow* createBaseWindow()
{
    BaseWindow* window = new BaseWindow();
    window->Initialize();
    return window;
}

void glfwWindowSizeCallback(GLFWwindow* window, int width, int height)
{
    BaseWindow* baseWindow = (BaseWindow*)glfwGetWindowUserPointer(window);
    baseWindow->ResizeCallback(Size(width, height));
}



BaseWindow::BaseWindow()
{
    windowSize = Size(800, 600);
    windowPosition = Position(MonitorInfo::GetPrimaryMonitorParameters().size().i_width / 2 - 400, MonitorInfo::GetPrimaryMonitorParameters().size().i_height / 2 - 300);
    windowID = windowCount++;
    windowTitle = "Base Window - " + to_string(windowID);
}

void BaseWindow::Initialize()
{
    glfw_window = glfwCreateWindow(windowSize.i_width, windowSize.i_height, windowTitle.c_str(), NULL, NULL);
    if (!glfw_window)
    {
        glfwTerminate();
        cerr << "[RTE][" << windowID << "] Failed to create GLFW window" << endl;
        system("pause");
        Application::Exit(-1);
    }
    DebugConsole::WriteLine("[%d] Window created successfully with name: %s",windowID, windowTitle.c_str());
    glfwMakeContextCurrent(glfw_window);

    if (!gladLoadGL(glfwGetProcAddress))
    {
        glfwTerminate();
        cerr << "[RTE][" << windowID << "] Failed to initialize GLAD" << endl;
        system("pause");
        Application::Exit(-1);
    }
    DebugConsole::WriteLine("[%d] GLAD initialized successfully",windowID);

    glfwSetWindowUserPointer(glfw_window, this);
    glfwSetWindowSizeCallback(glfw_window, glfwWindowSizeCallback);
    glfwSetWindowPos(glfw_window, windowPosition.i_x, windowPosition.i_y);
    BaseWindowHandlerIndex = BaseWindowsHandler::AddWindow(this);

    glViewport(0, 0, windowSize.i_width, windowSize.i_height);
    isCreated = true;

    DebugConsole::WriteLine("[%d] Window initialized successfully",windowID);
}

void BaseWindow::ResizeCallback(Size size)
{
    if(!InitCheck("ResizeCallback")) return;
    windowSize = size;
    glViewport(0, 0, windowSize.i_width, windowSize.i_height);
    OnResize.Invoke(this, windowSize);
}

void BaseWindow::Show()
{
    if(!InitCheck("Show")) return;
    DebugConsole::WriteLine("[%d] Showing window", windowID);
    OnShow.Invoke(this);
    glfwShowWindow(glfw_window);
}

void BaseWindow::Close()
{
    if(!InitCheck("Close")) return;
    DebugConsole::WriteLine("[%d] Closing window", windowID);
    OnClose.Invoke(this);
    glfwSetWindowShouldClose(glfw_window, GLFW_TRUE);
}

int BaseWindow::Destroy()
{
    if(!InitCheck("Destroy")) return -1;
    if(!ThreadCheck("Destroy")) return -1;
    DebugConsole::WriteLine("[%d] Destroying window.", windowID);
    glfwDestroyWindow(glfw_window);
    isCreated = false;
    return BaseWindowHandlerIndex;
}

Image BaseWindow::GetCurrentPicture()
{
    
    if(!ThreadCheck("GetCurrentPicture")) return Image(nullptr, 0, Size(0, 0));
    static unsigned char* pixels = new unsigned char[windowSize.i_width * windowSize.i_height * 3];
    glReadPixels(0, 0, windowSize.i_width, windowSize.i_height, GL_BGR, GL_UNSIGNED_BYTE, pixels);
    static Image img = Image(pixels, windowSize.i_width * windowSize.i_height * 3, windowSize);
    OnGetCurrentPicture.Invoke(this, &img);
    return img;
}

bool BaseWindow::ThreadCheck(const char* funtion)
{
    if(Application::GetMainThreadID() != Thread::GetCurrentThreadID())
    {
        if(funtion == "")DebugConsole::WriteLine("[THREAD_ERROR/%d] Cannot call this function from a different thread. Only from the main thread.",windowID);
        else DebugConsole::WriteLine("[THREAD_ERROR/%d] Cannot call function <%s> from a different thread. Only from the main thread.",windowID,funtion);
        return false;
    }
    return true;
}

bool BaseWindow::InitCheck(const char* function, bool throwRTE)
{
    if(!isCreated)
    {
        if(function == "" || function == nullptr) DebugConsole::WriteLine("[INIT_ERROR/%d] Window not initialized.",windowID);
        // FIXME: funtction name <>
        /**
         *& *===============================FIXIT===================================
         *& * DESCRIPTION: if function is null it still writes else.
         *& * HINT: idk, also try write the name even if not set.
         *& *=======================================================================
        **/
        else DebugConsole::WriteLine("[INIT_ERROR/%d] Window not initialized. Cannot call function <%s>.",windowID,function);
        if(throwRTE) 
        {
            cerr << "[RTE][" << windowID << "] Window not initialized. Cannot call function <" << function << ">." << endl;
            system("pause");
            Application::Exit(-1);
        }
        return false;
    }
    return true;
}

void BaseWindow::BindPointer(char* name, void* pointer)
{
    pointers[name] = pointer;
}

void* BaseWindow::GetPointer(char* name)
{
    return pointers[name];
}

void BaseWindow::SetSize(Size size)
{
    if(!InitCheck("SetSize")) return;
    glfwSetWindowSize(glfw_window, size.i_width, size.i_height);
}

double BaseWindow::GetGLFWTime()
{
    if(!InitCheck("GetGLFWTime")) return -1;
    return glfwGetTime();
}