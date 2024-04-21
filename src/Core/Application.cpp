#include "Application.hpp"

#include "IO/WindowsHandler.hpp"
#include "IO/BaseWindow.hpp"
#include "IO/Window.hpp"
#include "Debug/Console.hpp"

#define GLFW_INCLUDE_NONE
#include "GLFW/glfw3.h"

#include <thread>
#include <iostream>
#include <vector>
#include <stdexcept>

using namespace std;

vector<Method<void>> &GetInvokeQueue()
{
    static vector<Method<void>> invokeQueue;
    return invokeQueue;
}

namespace Application
{
    bool app_exit = false;
    int exitCode = 0;
    int mainThreadID = 0;
    void (*updateFunction)() = nullptr;

    bool exitOnLastWindowClosed = false;

    int Start(bool stopOnExit)
    {
        mainThreadID = std::hash<std::thread::id>{}(std::this_thread::get_id());
        try
        {
            while (!app_exit)
            {
                if (WindowsHandler::LiveWindowsCount() > 0)
                {
                    glfwPollEvents();
                    for (Window *window : WindowsHandler::WindowsList())
                    {
                        window->Render();
                        window->GetInput()->ResetInputs();
                    }
                    // glfwPollEvents();
                    BaseWindowsHandler::RemoveWindowsEvent();
                }
                else if (exitOnLastWindowClosed) app_exit = true;
                if (updateFunction != nullptr) updateFunction();
                // HACK CAUTION: InvokeQueue
                /**
                 *^  *=======================================================================
                 *^  * DESCRIPTION: Make thet only a certain amount of methods can be invoked per frame. Maybe make it so the user can set it.
                 *^  *=======================================================================
                 **/
                while (GetInvokeQueue().size() > 0)
                {
                    GetInvokeQueue()[0]();
                    GetInvokeQueue().erase(GetInvokeQueue().begin());
                }
            }
        }
        catch (const std::exception &e)
        {
            cerr << "\n" << e.what() << '\n';
            system("pause");
            return exitCode;
        }

        if (stopOnExit) system("pause");
        return exitCode;
    }

    int Step(bool pollEvents)
    {
        mainThreadID = std::hash<std::thread::id>{}(std::this_thread::get_id());
        if (WindowsHandler::LiveWindowsCount() > 0)
        {
            for (Window *window : WindowsHandler::WindowsList())
            {
                window->Render();
            }
            if (pollEvents)
                glfwPollEvents();
            BaseWindowsHandler::RemoveWindowsEvent();
        }
        else if (exitOnLastWindowClosed)
            app_exit = true;
        if (updateFunction != nullptr)
            updateFunction();
        if (app_exit)
            return exitCode;
        return 0;
    }

    void Exit(int exitCode)
    {
        Application::exitCode = exitCode;
        app_exit = true;
        exit(exitCode);
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