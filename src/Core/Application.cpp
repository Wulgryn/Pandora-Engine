#include "Application.hpp"

#include "IO/WindowHandler.hpp"
#include "IO/BaseWindow.hpp"

#define GLFW_INCLUDE_NONE
#include "GLFW/glfw3.h"

#include <thread>

namespace Application
{
    bool exit = false;
    int exitCode = 0;
    int mainThreadID = 0;
    void (*updateFunction)() = nullptr;

    bool exitOnLastWindowClosed = false;

    int Start()
    {
        mainThreadID = std::hash<std::thread::id>{}(std::this_thread::get_id());
        while (!exit)
        {
            if(WindowHandlers::liveWindows > 0) 
            {   
                for (BaseWindow* window : WindowHandlers::BaseWindowsList())
                {
                    window->Render();
                }
                glfwPollEvents();
                WindowHandlers::RemoveWindowsEvent();
            }
            else if (exitOnLastWindowClosed) exit = true;
            if (updateFunction != nullptr) updateFunction();
        }
        return exitCode;
    }

    int Step(bool pollEvents)
    {
        mainThreadID = std::hash<std::thread::id>{}(std::this_thread::get_id());
        if(WindowHandlers::liveWindows > 0) 
        {   
            for (BaseWindow* window : WindowHandlers::BaseWindowsList())
            {
                window->Render();
            }
            if (pollEvents)glfwPollEvents();
            WindowHandlers::RemoveWindowsEvent();
        }
        else if (exitOnLastWindowClosed) exit = true;
        if (updateFunction != nullptr) updateFunction();
        if (exit) return exitCode;
        return 0;
    }

    void Exit(int exitCode)
    {
        Application::exitCode = exitCode;
        exit = true;
    }

    int GetMainThreadID()
    {
        return mainThreadID;
    }

    void SetUpdateFunction(void (*updateFunction)())
    {
        Application::updateFunction = updateFunction;
    }
}