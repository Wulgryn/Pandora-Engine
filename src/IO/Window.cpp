#include "Window.hpp"
#include "WindowsHandler.hpp"
#include "Core/Elements/Object.hpp"
#include "Debug/Console.hpp"
#include "Core/Components/ShaderComponent2D.hpp"
#include "Core/Components/TextComponenet2D.hpp"

#define GLFW_INCLUDE_NONE
#include "GLFW/glfw3.h"
#include "glad/gl.h"

#define GLT_IMPLEMENTATION
#include "Core/External/gltext.h"

#include <math.h>
#include <thread>
#include <stdexcept>

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
            //if(UPS_LIMIT != -1)std::this_thread::sleep_for(std::chrono::milliseconds(1));
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
        currentUPSByFrameTime = 1.0/(currentTime - lastUpdateTime);
        DebugConsole::WriteLine("[UPS] %d : %.2f",currentUPS, 1.0/(currentTime - lastUpdateTime));
    }
    lastUpdateTime = currentTime;


    OnUpdate.Invoke(this);
    for (int  i = 0; i < objects.size(); i++)
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
        currentFPSByFrameTime = 1.0/(currentTime - lastFrameTime);
        DebugConsole::WriteLine("[FPS] %d : %.2f",currentFPS, 1.0/(currentTime - lastFrameTime));
    }
    lastFrameTime = currentTime;
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
    glClearColor(cosf(glfwGetTime()) * 0.5f + 0.5f,sinf(glfwGetTime()) * 0.5f + 0.5f, 1.0f, 1 );
    //glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    
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
    for(int i = 0; i < objects.size(); i++)
    {
        if(objects[i]->HasComponenet<ShaderComponent2D>()) //// .&& objects[i]->tag & ObjectTags::Renderable)
        {
            objects[i]->GetComponenet<ShaderComponent2D>()->Render();
        }

        // HACK CAUTION: TextComponent2D render
        /**
         *^  *=======================================================================
         *^  * DESCRIPTION: Maybe make it so all rednerable stuff is inside the Texture2D / ShaderComponent2D. And the overrinde render will determine tho többi
         *^  *=======================================================================
        **/
        if(objects[i]->HasComponenet<TextComponent2D>())
        {
            objects[i]->GetComponenet<TextComponent2D>()->Render();
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