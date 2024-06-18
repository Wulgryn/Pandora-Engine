#include "PandoraCore.hpp"
#include "Console.hpp"
#include "IO/Logger.hpp"
#include "IO/Monitor.hpp"
#include "Exceptions.hpp"

#include "GLFW/glfw3.h"

using namespace PandoraEngine;
using namespace Console;
using namespace std;


void error_callback(int error, const char *description)
{
#ifdef PE_DEBUG_CONSOLE
    DebugConsole::WriteLine("[GLFW ERROR] (%d) -> %s", error, description);
    Exceptions::GLFWException e(error + " -> " + string(description));
    e.print();
#else
    Logger::WriteLine("[GLFW ERROR] (%d) -> %s", error, description);
#endif
}

/**=======================================================================================================================*
 **                                                  REGION SUB_INITS
 *========================================================================================================================*/
#pragma region SUB_INITS

void init_unicode_console()
{
    setlocale(LC_ALL, "");
#ifdef PE_DEBUG_CONSOLE
    DebugConsole::WriteLine("Console locale > LC_ALL > %s", setlocale(LC_ALL, ""));
#endif
}

void init_random()
{
    srand(time(NULL));
#ifdef PE_DEBUG_CONSOLE
    DebugConsole::WriteLine("Random initialized successfully!");
#endif
}

void init_glfw()
{
    glfwSetErrorCallback(error_callback);
    if (!glfwInit())
    {
        Console::WriteLine("[GLFW ERROR] Failed to initialize GLFW!");
        Exceptions::GLFWException e("Failed to initialize GLFW!");
        e.throw_();
        return;
    }
#ifdef PE_DEBUG_CONSOLE
    DebugConsole::WriteLine("GLFW initialized successfully!");
#endif
}

void init_glfw_settings()
{
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);

#ifdef PE_DEBUG_CONSOLE
    DebugConsole::WriteLine("GLFW_VISIBLE -> default: false.");
#endif

    GLFWmonitor *monitor = glfwGetPrimaryMonitor();
    const GLFWvidmode *mode = glfwGetVideoMode(monitor);

    glfwWindowHint(GLFW_RED_BITS, mode->redBits);
    glfwWindowHint(GLFW_GREEN_BITS, mode->greenBits);
    glfwWindowHint(GLFW_BLUE_BITS, mode->blueBits);

    glfwWindowHint(GLFW_ALPHA_BITS, 8);
    glfwWindowHint(GLFW_DEPTH_BITS, 24);
    glfwWindowHint(GLFW_STENCIL_BITS, 8);
#ifdef PE_DEBUG_CONSOLE
    DebugConsole::WriteLine("GLFW settings initialized successfully!");
#endif
}

void init_logger()
{
    Logger::Initialize();
}

void init_monitors()
{
#ifdef PE_DEBUG_CONSOLE
    MonitorInfo::initialize(true);
#else
    MonitorInfo::initialize();
#endif
#ifdef PE_DEBUG_CONSOLE
    DebugConsole::WriteLine("Monitors initialized successfully!");
#endif
}

/**=======================================================================================================================*
 **                                           END OF REGION SUB_INITS
 *========================================================================================================================*/
#pragma endregion SUB_INITS

void PandoraEngine::initialize()
{
    init_logger();
#ifdef PE_DEBUG_CONSOLE
    Console::EnableLogging = true;
#endif
    Console::Write("Version: %s\nVersion Tags: %s\n", PE_VERSION, PE_TAGS);
#ifdef PE_DEBUG_CONSOLE
    DebugConsole::WriteLine("Debug mode enabled");
    DebugConsole::WriteLine("Logger initialized successfully!");
#endif
    init_monitors();
    init_unicode_console();
    init_random();
    init_glfw();
    init_glfw_settings();

    Console::WriteLine("PandoraEngine initialized successfully!");
}
