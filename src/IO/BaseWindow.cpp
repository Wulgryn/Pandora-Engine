#include "BaseWindow.hpp"
#include "IO/Monitor.hpp"
#include "Debug/Console.hpp"
#include "WindowHandler.hpp"
#include "Core/Application.hpp"
#include "Core/Thread.hpp"

#define GLFW_INCLUDE_NONE
#include "GLFW/glfw3.h"
#include "glad/gl.h"

#include <stdexcept>
#include <thread>
#include <iostream>
#include <math.h>
#include <string>

using namespace std;

static int windowCount = 0;

BaseWindow* createBaseWindow()
{
    return new BaseWindow();
}

BaseWindow::BaseWindow()
{
    windowSize = Size(800, 600);
    windowPosition = Position(MonitorInfo::GetPrimaryMonitorParameters().size().i_width / 2 - 400, MonitorInfo::GetPrimaryMonitorParameters().size().i_height / 2 - 300);
    windowID = windowCount++;
    windowTitle = string("Base Window - " + to_string(windowID)).c_str();
}

void BaseWindow::Initialize()
{
    glfw_window = glfwCreateWindow(windowSize.i_width, windowSize.i_height, windowTitle, NULL, NULL);
    if (!glfw_window)
    {
        glfwTerminate();
        throw std::runtime_error("[RTE][" + string(to_string(windowID) + "") + "] Failed to create GLFW window");
    }
    DebugConsole::WriteLine("[%d] Window created successfully",windowID);
    glfwMakeContextCurrent(glfw_window);

    if (!gladLoadGL(glfwGetProcAddress))
    {
        std::runtime_error("[RTE][" + string(to_string(windowID) + "") + "] Failed to initialize GLAD");
        system("pause");
        throw std::runtime_error("");
    }
    DebugConsole::WriteLine("[%d] GLAD initialized successfully",windowID);
    glfwSetWindowPos(glfw_window, windowPosition.i_x, windowPosition.i_y);
    WindowHandlers::AddWindow(this);
    mainThread = std::thread(&BaseWindow::WindowMain, this);
    mainThread.detach();
}

bool BaseWindow::ThreadCheck()
{
    if(Application::GetMainThreadID() != Thread::GetCurrentThreadID())
    {
        DebugConsole::WriteLine("[THREAD_ERROR/%d] Cannot call this function from a different thread. Only from the main thread.",windowID);
        return false;
    }
    return true;
}

void BaseWindow::Show()
{
    glfwShowWindow(glfw_window);
}

void BaseWindow::Close()
{
    DebugConsole::WriteLine("[%d] Closing window", windowID);
    glfwSetWindowShouldClose(glfw_window, GLFW_TRUE);
}

void BaseWindow::Destroy()
{
    if(!ThreadCheck()) return;
    DebugConsole::WriteLine("[%d] Destroying window.", windowID);
    glfwDestroyWindow(glfw_window);
}

void BaseWindow::WindowMain()
{
    while (!glfwWindowShouldClose(glfw_window))
    {
       
    }
    WindowHandlers::RemoveWindow(this);
}

void BaseWindow::Render()
{
    if(!ThreadCheck()) return;
    if (glfwWindowShouldClose(glfw_window)) WindowHandlers::RemoveWindow(this);
    if(glfwGetCurrentContext() != glfw_window) glfwMakeContextCurrent(glfw_window);
    glClear(GL_COLOR_BUFFER_BIT);
    glClearColor(sin(glfwGetTime()), cos(glfwGetTime()), sin(glfwGetTime()), 1 ); // BG COLOR
    glfwSwapBuffers(glfw_window);
}
