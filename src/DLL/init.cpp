#include "init.hpp"

#include "CONSOLE/fancyLog.hpp"

#define GLFW_INCLUDE_NONE
#include "GLFW/glfw3.h"
#include "glad/gl.h"

#include <string>
#include <cstdlib>
#include <time.h>

using namespace std;

void error_callback(int error, const char* description)
{
    logType("GLFW");
    logError("(%d) -> %s",error,string(description));
    logType();
}

void PandoraEngine::init()
{
#ifndef DEBUG
    system("title Pandora Engine");
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