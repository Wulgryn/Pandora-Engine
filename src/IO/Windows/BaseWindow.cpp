#include "BaseWindow.hpp"
#include "Exceptions.hpp"
#include "Console.hpp"

using namespace PandoraEngine;
using namespace PandoraEngine::Windows;
using namespace PandoraEngine::Console;

#define GLFW_INCLUDE_NONE
#include "GLFW/glfw3.h"
#include "glad/gl.h"

int windowCount = 0;

/**=======================================================================================================================*
 **                                                  REGION BASE WINDOW
 *========================================================================================================================*/
#pragma region BASE WINDOW

void BaseWindow::set_gl_glfw_settigs()
{
    // glfwSetWindowUserPointer(_GLFWwindow, this);
    // glfwSetWindowSizeCallback(_GLFWwindow, glfwWindowSizeCallback);
    // glfwSetWindowPos(_GLFWwindow, windowPosition.i_x, windowPosition.i_y);
    

    // glViewport(0, 0, windowSize.i_width, windowSize.i_height);
}

BaseWindow::BaseWindow(std::string title)
{
    _title = title;
    _windowID = windowCount++;
}

void BaseWindow::initialize()
{
    _GLFWwindow = glfwCreateWindow(800, 600, "PandoraEngine Window", NULL, NULL);
    if (!_GLFWwindow)
    {
        Exceptions::GLFWException glfw_exc("Failed to create GLFW window.");
        glfw_exc.print(true);
    }
#ifdef PE_DEBUG
    DebugConsole::WriteLine("[%d] Window created successfully with name: %s", _windowID, _title.c_str());
#endif
    glfwMakeContextCurrent(_GLFWwindow);

    if (!gladLoadGL(glfwGetProcAddress))
    {
        Exceptions::GLADException glad_exc("Failed to initialize GLAD.");
        glad_exc.print(true);
    }
#ifdef PE_DEBUG
    DebugConsole::WriteLine("[%d] GLAD initialized successfully", _windowID);
#endif

    set_gl_glfw_settigs();
    // _handlerIndex = BaseWindowsHandler::AddWindow(this);
    _isCreated = true;

#ifdef PE_DEBUG
    DebugConsole::WriteLine("[%d] Window initialized successfully", _windowID);
#endif
}

/**=======================================================================================================================*
 **                                           END OF REGION BASE WINDOW
 *========================================================================================================================*/
#pragma endregion BASE WINDOW