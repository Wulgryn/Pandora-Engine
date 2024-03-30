#include "Window.hpp"
#include "WindowsHandler.hpp"
#include "Core/Rendering/Object.hpp"
#include "Debug/Console.hpp"
#include "Core/Components/ShaderComponent2D.hpp"

#define GLFW_INCLUDE_NONE
#include "GLFW/glfw3.h"
#include "glad/gl.h"

#include <math.h>
#include <thread>

using namespace std;

Window* createWindow()
{
    Window* window = new Window();
    window->Initialize();
    return window;
}

Window::Window() : ObjectsHandler(this)
{
}

void Window::Initialize()
{
    BaseWindow::Initialize();
    // TODO Set background color
    WindowsHandler::AddWindow(this);
}

void Window::Start()
{
    thread update_thread([=](){

        // FIXME: InitCheck() error
        /**
         *& *===============================FIXIT===================================
         *& * DESCRIPTION: Throws an error when the window is closed.
         *& * HINT: optional bool for write it or not, default true.
         *& *=======================================================================
        **/
        while (InitCheck())
        {
            Update();
        }
    });
    update_thread.detach();
    isRunning = true;
}

void Window::Update()
{
    double currentTime = glfwGetTime();
    if((UPS_LIMIT != -1 && (currentTime - lastUpdateTime) < 1.0/UPS_LIMIT) || !isRunning) return;

    UpdateCount++;
    if(lastUPSUpdateTime + 1 < currentTime)
    {
        currentUPS = UpdateCount;
        UpdateCount = 0;
        lastUPSUpdateTime = currentTime;
        DebugConsole::WriteLine("[UPS] %d",currentUPS);
    }


    OnUpdate.Invoke(this);
    for (int  i = 0; i < objects.size(); i++)
    {
        objects[i]->Update();
        if(objects[i]->HasComponenet<ShaderComponent2D>() && !(objects[i]->tag & ObjectTags::Renderable)) 
        {
            objects[i]->tag |= ObjectTags::Renderable;
            renderable_objects.push_back(objects[i]);

        }
    }
    OnLateUpdate.Invoke(this);
}

void Window::Render()
{
    // TODO Add fps limiter
    if(!ThreadCheck() || !InitCheck() || !isRunning) return;
    if (glfwWindowShouldClose(glfw_window)) BaseWindowsHandler::RemoveWindow(this);
    if(glfwGetCurrentContext() != glfw_window) glfwMakeContextCurrent(glfw_window);
    double currentTime = glfwGetTime();
    if(FPS_LIMIT != -1 && (currentTime - lastFrameTime) < 1.0/FPS_LIMIT) return;

    FrameCount++;
    if(lastFPSUpdateTime + 1 < currentTime)
    {
        currentFPS = FrameCount;
        FrameCount = 0;
        lastFPSUpdateTime = currentTime;
        DebugConsole::WriteLine("[FPS] %d",currentFPS);
    }
    OnWindowClear.Invoke(this);

    glClear(GL_COLOR_BUFFER_BIT);

    // BUG DEPRECATED: glClearColor(1, cos(glfwGetTime()), sin(glfwGetTime()), 1 );
    /**
     *~  *=======================================================================
     *~  * DESCRIPTION: Need to remove, only for testing purposes.
     *~  * REASON: Let user decide the background color.
     *~  * ALTERNATIVE: none
     *~  * EXPARATION: near future
     *~  *=======================================================================
    **/
    glClearColor(sin(glfwGetTime()), cos(glfwGetTime()), sin(glfwGetTime()), 1 );
    OnRender.Invoke(this);

    for(int i = 0; i < objects.size(); i++)
    {
        if(objects[i]->HasComponenet<ShaderComponent2D>() && objects[i]->tag & ObjectTags::Renderable)
        {
            objects[i]->GetComponenet<ShaderComponent2D>()->Render();
        } 
    }
    OnLateRender.Invoke(this);
    glfwSwapBuffers(glfw_window);
}

void Window::SetFPSLimit(int fps)
{
    if(fps < -1)
    {
        DebugConsole::WriteLine("[INT_SET_ERROR] FPS Limit cannot be negative. (%d)",fps);
        return;
    } 
    FPS_LIMIT = fps;
}

void Window::SetUPSLimit(int ups)
{
    if(ups < -1)
    {
        DebugConsole::WriteLine("[INT_SET_ERROR] UPS Limit cannot be negative. (%d)",ups);
        return;
    } 
    UPS_LIMIT = ups;
}