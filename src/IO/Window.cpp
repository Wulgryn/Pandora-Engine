#include "Window.hpp"
#include "WindowsHandler.hpp"
#include "Core/Rendering/Object.hpp"
#include "Debug/Console.hpp"
#include "Core/Components/ShaderComponent.hpp"

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

Window::Window()
{
    
}

void Window::Initialize()
{
    BaseWindow::Initialize();
    WindowsHandler::AddWindow(this);
    //thread update_thread([](Window* window){
    //    while (true)
    //    {
    //        window->Update();
    //    }
    //},this, this);
}

void Window::Update()
{
    for (int  i = 0; i < objects.size(); i++)
    {
        objects[i]->Update();
    }
}

void Window::Render()
{
    if(!ThreadCheck() || !InitCheck()) return;
    if (glfwWindowShouldClose(glfw_window)) BaseWindowsHandler::RemoveWindow(this);
    if(glfwGetCurrentContext() != glfw_window) glfwMakeContextCurrent(glfw_window);
    glClear(GL_COLOR_BUFFER_BIT);
    glClearColor(sin(glfwGetTime()), cos(glfwGetTime()), sin(tan(glfwGetTime())), 1 ); // BG COLOR
    for(int i = 0; i < renderable_objects.size(); i++)
    {
        if(!renderable_objects[i]->HasComponenet<ShaderComponent>())
        renderable_objects[i]->UpdateComponenets();
    }
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