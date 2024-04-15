#include "Application.hpp"

#include "IO/WindowsHandler.hpp"
#include "IO/BaseWindow.hpp"
#include "IO/Window.hpp"
#include "Debug/Console.hpp"

#define GLFW_INCLUDE_NONE
#include "GLFW/glfw3.h"

#include <thread>

using namespace std;

vector<Method<void>>& GetInvokeQueue()
{
    static vector<Method<void>> invokeQueue;
    return invokeQueue;
}

namespace Application
{
    bool exit = false;
    int exitCode = 0;
    int mainThreadID = 0;
    void (*updateFunction)() = nullptr;

    bool exitOnLastWindowClosed = false;

    int Start(bool stopOnExit)
    {
        mainThreadID = std::hash<std::thread::id>{}(std::this_thread::get_id());
        
        while (!exit)
        {
            if(WindowsHandler::LiveWindowsCount() > 0) 
            {   
                for (Window* window : WindowsHandler::WindowsList())
                {
                    window->Render();
                }
                glfwPollEvents();
                BaseWindowsHandler::RemoveWindowsEvent();
            }
            else if (exitOnLastWindowClosed) exit = true;
            if (updateFunction != nullptr) updateFunction();
            while (GetInvokeQueue().size() > 0)
            {
                GetInvokeQueue()[0]();
                GetInvokeQueue().erase(GetInvokeQueue().begin());
            }
        }
        if(stopOnExit)system("pause");
        return exitCode;
    }

    int Step(bool pollEvents)
    {
        mainThreadID = std::hash<std::thread::id>{}(std::this_thread::get_id());
        if(WindowsHandler::LiveWindowsCount() > 0) 
        {   
            for (Window* window : WindowsHandler::WindowsList())
            {
                window->Render();
            }
            if (pollEvents)glfwPollEvents();
            BaseWindowsHandler::RemoveWindowsEvent();
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

void Application::EnqueueInvoke(Method<void> method)
{
    GetInvokeQueue().push_back(method);
}