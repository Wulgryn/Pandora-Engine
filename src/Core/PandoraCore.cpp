#include "PandoraCore.hpp"
#include "Debug/Console.hpp"
#include "IO/Monitor.hpp"

#define GLFW_INCLUDE_NONE
#include "GLFW/glfw3.h"
#include "glad/gl.h"

#include <iostream>
using namespace std;

void error_callback(int error, const char *description)
{
    DebugConsole::WriteLine("[GLFW ERROR] (%d) -> %s", error, description);
}

void PandoraCore::Initialize(bool printMonitorInfos)
{
    system("title \"Pandora Engine Debug Console\"");
#ifdef PE_DEBUG
    DebugConsole::WriteLine("Debug mode enabled");
#endif
    DebugConsole::WriteLine("experimental version 0.1.1 alpha");
    glfwSetErrorCallback(error_callback);
    srand(time(NULL));
    DebugConsole::WriteLine("Random initialized successfully!");
    MonitorInfo::Initialize(printMonitorInfos);
    DebugConsole::WriteLine("MonitorInfo initialized successfully!");
    if (!glfwInit())
    {
        DebugConsole::WriteLine("[GLFW ERROR] Failed to initialize GLFW!");
        return;
    }
    DebugConsole::WriteLine("GLFW initialized successfully!");

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);

    GLFWmonitor *monitor = glfwGetPrimaryMonitor();
	const GLFWvidmode *mode = glfwGetVideoMode(monitor);

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

	glfwWindowHint(GLFW_RED_BITS, mode->redBits);
	glfwWindowHint(GLFW_GREEN_BITS, mode->greenBits);
	glfwWindowHint(GLFW_BLUE_BITS, mode->blueBits);

	glfwWindowHint(GLFW_ALPHA_BITS, 8);
	glfwWindowHint(GLFW_DEPTH_BITS, 24);
	glfwWindowHint(GLFW_STENCIL_BITS, 8);

    DebugConsole::WriteLine("PandoraCore initialized successfully!");
}