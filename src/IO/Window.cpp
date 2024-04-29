#include "Window.hpp"
#include "WindowsHandler.hpp"
#include "Core/Elements/Object.hpp"
#include "Debug/Console.hpp"
#include "Core/Components/ShaderComponent2D.hpp"
#include "Core/Components/TextComponenet2D.hpp"
#include "Core/Application.hpp"

#define GLFW_INCLUDE_NONE
#include "GLFW/glfw3.h"
#include "glad/gl.h"

#include <math.h>
#include <thread>
#include <iostream>
#include <stdexcept>

using namespace std;

Window *createWindow()
{
    Window *window = new Window();
    window->Initialize();
    return window;
}

Window::Window() : ObjectsHandler(this), BaseWindow()
{
}

void Window::Initialize()
{
    BaseWindow::Initialize();
    inputHandler = new InputHandler(this);
    glfwSetWindowUserPointer(glfw_window, this);

    // TODO Set background color
    WindowsHandler::AddWindow(this);
}

void Window::Start()
{
    thread update_thread([=]()
    {
        try
        {
            // FIXME: InitCheck() error
            /**
             *& *===============================FIXIT===================================
            *& * DESCRIPTION: Throws an error when the window is closed.
            *& * HINT: optional bool for write it or not, default true.
            *& *=======================================================================
            **/

            static double currentTime = glfwGetTime();
            while (InitCheck())
            {
                currentTime = glfwGetTime();
                if ((UPS_LIMIT != -1 && (currentTime - lastUpdateTime) < 1.0 / UPS_LIMIT) || !isRunning) continue;
                UpdateCount++;
                if (lastUPSUpdateTime + 1 < currentTime)
                {
                    currentUPS = UpdateCount;
                    UpdateCount = 0;
                    lastUPSUpdateTime = currentTime;
                    currentUPSByFrameTime = 1.0 / (currentTime - lastUpdateTime);
                    if (IsPrintUPSEnabled) DebugConsole::WriteLine("[UPS] %d : %.2f", currentUPS, 1.0 / (currentTime - lastUpdateTime));
                }
                lastUpdateTime = currentTime;
                Update();
                // HACK CAUTION: Thread sleep
                /**
                 *^  *=======================================================================
                *^  * DESCRIPTION: Make it so the user can set the sleep time. AND make it so the user can disable or ednable it.
                *^  *=======================================================================
                **/
                // if(UPS_LIMIT != -1)std::this_thread::sleep_for(std::chrono::milliseconds(1));
            }
        }
        catch (const std::exception &e)
        {
            cerr << "\n"
                << e.what() << '\n';
            Application::Exit(-1);
        }
    });
    update_thread.detach();
    isRunning = true;
}

void Window::Update()
{
    OnUpdate.Invoke(this);
    for (int i = 0; i < objects.size(); i++)
    {
        objects[i]->Update();
        // FIXME: Renderable objects segmention fault
        /**
         *& *===============================FIXIT===================================
         *& * DESCRIPTION: when this ads object the render loop gets an error(segmention fault).
         *& * HINT: idk
         *& *=======================================================================
         **/
        //// if(objects[i]->HasComponenet<ShaderComponent2D>() && !(objects[i]->tag & ObjectTags::Renderable))
        //// {
        ////     objects[i]->tag |= ObjectTags::Renderable;
        ////     renderable_objects.push_back(objects[i]);
        //// }
    }
    OnLateUpdate.Invoke(this);
}

void Window::Render()
{
    if (!ThreadCheck() || !InitCheck() || !isRunning) return;
    if (glfwWindowShouldClose(glfw_window)) BaseWindowsHandler::RemoveWindow(this);
    if (glfwGetCurrentContext() != glfw_window) glfwMakeContextCurrent(glfw_window);
    static double currentTime = glfwGetTime();
    if (FPS_LIMIT != -1 && (currentTime - lastFrameTime) < 1.0 / FPS_LIMIT)
        return;
    FrameCount++;
    if (lastFPSUpdateTime + 1 < currentTime)
    {
        // FIXME: FPS not printing properly
        /**
         *& *===============================FIXIT===================================
         *& * DESCRIPTION: Not printing, just once.
         *& * HINT: glfwTime() refresh or idk
         *& *=======================================================================
        **/
        currentFPS = FrameCount;
        FrameCount = 0;
        lastFPSUpdateTime = currentTime;
        currentFPSByFrameTime = 1.0 / (currentTime - lastFrameTime);
        if(IsPrintFPSEnabled) DebugConsole::WriteLine("[FPS] %d : %.2f", currentFPS, 1.0 / (currentTime - lastFrameTime));
    }
    lastFrameTime = currentTime;
    OnWindowClear.Invoke(this);

    glClear(GL_COLOR_BUFFER_BIT);

    //// // BUG DEPRECATED: glClearColor();
    //// /**
    ////  -*~  *=======================================================================
    ////  -*~  * DESCRIPTION: Need to remove, only for testing purposes.
    ////  -*~  * REASON: Let user decide the background color.
    ////  -*~  * ALTERNATIVE: none
    ////  -*~  * EXPARATION: near future
    ////  -*~  *=======================================================================
    ////  -**/
    //// //glClearColor(cosf(glfwGetTime()) * 0.5f + 0.5f, sinf(glfwGetTime()) * 0.5f + 0.5f, 1.0f, 1);
    //// // glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    OnRender.Invoke(this);

    // FIXME: Renderable objects segmention fault
    /**
     *& *===============================FIXIT===================================
     *& * DESCRIPTION: If this loop changet to renderable_objects.size() it throws a segmention fault. on the IF statement.
     *& * HINT: When update loop ads objects to renderable_objects the render loop still uses it, so segmention fault.
     *& *=======================================================================
     **/
    //// for(int i = 0; i < renderable_objects.size(); i++)
    //// {
    ////     if(renderable_objects[i]->HasComponenet<ShaderComponent2D>() && renderable_objects[i]->tag & ObjectTags::Renderable)
    ////     {
    ////         renderable_objects[i]->GetComponenet<ShaderComponent2D>()->Render();
    ////     }
    //// }
    for (int i = 0; i < objects.size(); i++)
    {
        if (ShaderComponent2D* shc2D = objects[i]->GetComponent<ShaderComponent2D>()) //// .&& objects[i]->tag & ObjectTags::Renderable)
        {
            shc2D->Render();
        }

        // HACK CAUTION: TextComponent2D render
        /**
         *^  *=======================================================================
         *^  * DESCRIPTION: Maybe make it so all renderable stuff is inside the Texture2D / ShaderComponent2D. And the overrinde render will determine tho többi
         *^  *=======================================================================
         **/
        if (TextComponent2D* tc2D = objects[i]->GetComponent<TextComponent2D>())
        {
            tc2D->Render();
        }
    }
    OnLateRender.Invoke(this);
    glfwSwapBuffers(glfw_window);
}

void Window::SetFPSLimit(int fps)
{
    if (fps < -1)
    {
        DebugConsole::WriteLine("[INT_SET_ERROR] FPS Limit cannot be negative. (%d)", fps);
        return;
    }
    FPS_LIMIT = fps;
}

void Window::SetUPSLimit(int ups)
{
    if (ups < -1)
    {
        DebugConsole::WriteLine("[INT_SET_ERROR] UPS Limit cannot be negative. (%d)", ups);
        return;
    }
    UPS_LIMIT = ups;
}

void Window::SetBackgroundColor(Color color)
{
    BackgroundColor = color;
    color.Normalize();
    glClearColor(color.Fr, color.Fg, color.Fb, color.Fa);
}