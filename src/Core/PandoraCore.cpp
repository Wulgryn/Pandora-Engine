#include "PandoraCore.hpp"
#include "Debug/DebugConsole.hpp"

void error_callback(int error, const char* description)
{
    DebugConsole::Write("[GLFW ERROR] ");
    DebugConsole::WriteLine("(%d) -> %s",error,description);
}

void PandoraCore::Initialize(){
#ifndef DEBUG
    system("title Pandora Engine");
#endif
#ifdef BUILD_DLL
    logInfo("§YELLOWbuilding DLL");
#endif
    logInfo("§YELLOWexperimental version 0.0.1 alpha");
    glfwSetErrorCallback(error_callback);
    srand(time(NULL));

    if(!glfwInit())
    {
        logError("Failed to initialize GLFW!");
        return;
    }
    logSuccess("GLFW initialized successfully!");

    

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
}