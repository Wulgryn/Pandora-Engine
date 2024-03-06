#include "./PandoraCore.hpp"
#include "../Debug/Console.hpp"
#include "../IO/Monitor.hpp"

#define GLFW_INCLUDE_NONE
#include "GLFW/glfw3.h"
#include "glad/gl.h"

#include <iostream>

void error_callback(int error, const char* description)
{
    DebugConsole::Write("[GLFW ERROR] ");
    DebugConsole::WriteLine("(%d) -> %s",error,description);
}

void PandoraCore::Initialize()
{
    system("title Pandora Engine Debug Console");
    DebugConsole::WriteLine("experimental version 0.1.1 alpha");
    glfwSetErrorCallback(error_callback);
    srand(time(NULL));
    DebugConsole::WriteLine("Random initialized successfully!");
    MonitorInfo::Initialize();
    DebugConsole::WriteLine("MonitorInfo initialized successfully!");
    if(!glfwInit())
    {
        DebugConsole::WriteLine("[GLFW ERROR] Failed to initialize GLFW!");
        return;
    }
    DebugConsole::WriteLine("GLFW initialized successfully!");

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);

    DebugConsole::WriteLine("PandoraCore initialized successfully!");
}