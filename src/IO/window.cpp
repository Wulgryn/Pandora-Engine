#include "window.hpp"

#include <iostream>
#include <thread>
#include <chrono>

#include "glad/gl.h"

#include "CONSOLE/fancyLog.hpp"
#include "UTILS/timer.hpp"
#include "PANDORA/objects.hpp"
#include "PANDORA/COMPONENTS/shader.hpp"
#include "PANDORA/COMPONENTS/transform.hpp"
#include "PANDORA/mainWindow.hpp"
#include "PANDORA/scenes.hpp"

using namespace io;
using namespace std;
using namespace utils;
using namespace pandora;

Window::Window(int width, int height, string title)
{
    GLFWwindow *window = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);
    // Set the window object
    this->glfw_window = window;
    if (!window)
    {
        // Handle window creation error
        logError("Failed to create GLFW window");
        glfwDestroyWindow(window);
        return;
    }
    logSuccess("GLFW window created successfully!");

    // Set the current context to the newly created window
    glfwMakeContextCurrent(window);

    if (!gladLoadGL(glfwGetProcAddress))
    {
        logError("Failed to initialize GLAD!");
        glfwDestroyWindow(window);
        return;
    }
    logSuccess("GLAD initialized successfully!");

    glfwSetFramebufferSizeCallback(window, window::defaultResizeCallback);
    parameters.setSize(Size(width, height));
    input = new Input(this);
}

Window::~Window()
{
    // Destroy the GLFW window
    glfwDestroyWindow(this->glfw_window);
    logInfo("GLFW window destroyed!");
}

void Window::setFixedUpdateFunction(int (*fixedUpdateFunction)(int, Window &))
{
    this->fixedUpdateFunction = fixedUpdateFunction;
}

void Window::setUpdateFunction(int (*updateFunction)(int, Window &))
{
    this->updateFunction = updateFunction;
}

void Window::setStartFunction(int (*startFunction)(Window &))
{
    this->startFunction = startFunction;
}

void Window::setSetupFunction(int (*setupFunction)())
{
    this->setupFunction = setupFunction;
}

void Window::doSetup()
{
    if (setupFunction != nullptr)
        result = setupFunction();
}

void Window::doStart()
{
    if (startFunction != nullptr)
        result = startFunction(*this);
}

void Window::setRenderFunction(void (*renderFunction)())
{
    this->renderFunction = renderFunction;
}

void Window::setTargetFPS(int targetFPS)
{
    GLFWmonitor *monitor = properties.getPrimaryMonitor();
    const GLFWvidmode *mode = glfwGetVideoMode(monitor);
    if (targetFPS == -1)
        glfwSwapInterval(0);
    // if (mode->refreshRate <= targetFPS)
    //     glfwSwapInterval(1);
    // else if(targetFPS != -1)
    //     glfwSwapInterval(targetFPS / mode->refreshRate);
    this->targetFPS = targetFPS;
}

int Window::getCurrentFPS()
{
    return currentFPS;
}

void Window::setTargetTPS(int targetTPS)
{
    this->targetTPS = targetTPS;
}

int Window::getCurrentTPS()
{
    return currentTPS;
}

GLFWwindow *Window::getWindow()
{
    return glfw_window;
}

void updateThreadCallback(int (*threadUpdateFunction)(int, Window &), int currentFPS, Window &window, int &result)
{
    int _result = threadUpdateFunction(currentFPS, window);
    if (result == -1)
        return;
    result = _result;
    return;
}

double Window::deltaTime()
{
    return _deltaTime;
}

void Window::start()
{
    double currentTime = glfwGetTime();

    double targetFrameTime = 1.0 / targetFPS;
    double fps_currentTime = currentTime;

    double targetTickTime = 1.0 / targetTPS;
    double tps_currentTime = currentTime;

    int FPS_count = 0;
    // double lastFPStime = currentTime;

    int TPS_count = 0;
    // double lastTPStime = currentTime;

    double lasLogTime = currentTime;

    doSetup();

    if (result == -1)
    {
        // Close the window
        glfwSetWindowShouldClose(glfw_window, true);
        return;
    }
    doStart();
    if (result == -1)
    {
        // Close the window
        glfwSetWindowShouldClose(glfw_window, true);
        return;
    }
    thread updateThread;
    Timer timer;
    timer.timeType = "RENDER_THREAD_TIME";
    timer.logTimeOnStop = false;

    if (renderFunction == nullptr)
        renderFunction = pandora::objects::render;

    while (!glfwWindowShouldClose(glfw_window))
    {
        timer.start();
        currentTime = glfwGetTime();

        glClearColor(this->backgroundColor.getRedF(), this->backgroundColor.getGreenF(), this->backgroundColor.getBlueF(), this->backgroundColor.getAlphaF());
        glClear(GL_COLOR_BUFFER_BIT);

        if (result == -1)
        {
            // Close the window
            glfwSetWindowShouldClose(glfw_window, true);
        }
        if (glfwWindowShouldClose(glfw_window))
        {
            glfwSetWindowShouldClose(glfw_window, true);
        }

        if (targetFPS == -1 || fps_currentTime + targetFrameTime < currentTime)
        {
            fps_currentTime = currentTime;
            FPS_count++;

            // Render here
            renderFunction();

            // Swap the buffers
            glfwSwapBuffers(glfw_window);
            // Poll for events
            glfwPollEvents();
            if (fixedUpdateFunction)
                result = fixedUpdateFunction(currentFPS, *this);
        }

        if (tps_currentTime + targetTickTime < currentTime || targetTPS == -1)
        {
            _deltaTime = currentTime - tps_currentTime;
            tps_currentTime = currentTime;
            TPS_count++;

            if (updateFunction && !updateThread.joinable())
            {
                updateThread = thread(updateThreadCallback, updateFunction, currentFPS, ref(*this), ref(result));
                updateThread.detach();
            }
        }

        input->resetInputs();

        timer.stop();
        string ellapsedTime = timer.getEllapsedTime(timer::TimerClockPrecision::NANOSECOND);
        if (lasLogTime + 1.0 < currentTime)
        {
            lasLogTime = currentTime;
            currentTPS = TPS_count;
            TPS_count = 0;
            if (log.logTPS)
            {
                logType("TPS");
                logInfo("%d", currentTPS);
                logType();
            }
            currentFPS = FPS_count;
            FPS_count = 0;
            if (log.logFPS)
            {
                logType("FPS");
                logInfo("%d", currentFPS);
                logType();
            }
            if (log.logMainThreadTime)
            {
                logType("MAIN_THREAD_TIME");
                logInfo(ellapsedTime);
                logType();
            }
        }
    }
}

//______________________________________________________________________________________________________________________
// PARAMETERS  |  PARAMETERS  |  PARAMETERS  |  PARAMETERS  |  PARAMETERS  |  PARAMETERS  |  PARAMETERS  |  PARAMETERS  |  PARAMETERS  |  PARAMETERS  |  PARAMETERS  |  PARAMETERS  |  PARAMETERS  |  PARAMETERS  |  PARAMETERS  |  PARAMETERS  |  PARAMETERS
//______________________________________________________________________________________________________________________
#pragma region PARAMETERS

Window::Parameters::Parameters(Window &window)
{
    this->window = &window;
}

Position Window::Parameters::getPosition()
{
    int x, y;
    glfwGetWindowPos(window->glfw_window, &x, &y);
    return Position(x, y);
}

void Window::Parameters::setPosition(Position position)
{
    glfwSetWindowPos(window->glfw_window, position.x, position.y);
}

Size Window::Parameters::getSize()
{
    int width, height;
    glfwGetWindowSize(window->glfw_window, &width, &height);
    return Size(width, height);
}

void Window::Parameters::setSize(Size size)
{
    glfwSetWindowSize(window->glfw_window, size.Width, size.Height);
    glViewport(0, 0, size.Width, size.Height);
}

//______________________________________________________________________________________________________________________
// PARAMETERS  |  PARAMETERS  |  PARAMETERS  |  PARAMETERS  |  PARAMETERS  |  PARAMETERS  |  PARAMETERS  |  PARAMETERS  |  PARAMETERS  |  PARAMETERS  |  PARAMETERS  |  PARAMETERS  |  PARAMETERS  |  PARAMETERS  |  PARAMETERS  |  PARAMETERS  |  PARAMETERS
//______________________________________________________________________________________________________________________
#pragma endregion PARAMETERS

//______________________________________________________________________________________________________________________
// PROPERTIES  |  PROPERTIES  |  PROPERTIES  |  PROPERTIES  |  PROPERTIES  |  PROPERTIES  |  PROPERTIES  |  PROPERTIES  |  PROPERTIES  |  PROPERTIES  |  PROPERTIES  |  PROPERTIES  |  PROPERTIES  |  PROPERTIES  |  PROPERTIES  |  PROPERTIES  |  PROPERTIES
//______________________________________________________________________________________________________________________
#pragma region PROPERTIES

Window::Properties::Properties(Window &window)
{
    this->window = &window;
    primary_monitor = glfwGetPrimaryMonitor();
}

GLFWmonitor *Window::Properties::getPrimaryMonitor()
{
    return primary_monitor;
}

void Window::Properties::setPrimaryMonitor(GLFWmonitor *monitor)
{
    primary_monitor = monitor;
}

bool Window::Properties::isFullscreen()
{
    return glfwGetWindowMonitor(window->glfw_window) != nullptr;
}

void Window::Properties::setFullscreen(bool fullscreen)
{
    GLFWmonitor *monitor = primary_monitor;
    const GLFWvidmode *mode = glfwGetVideoMode(monitor);
    if (fullscreen)
    {
        glfwSetWindowMonitor(window->glfw_window, monitor, 0, 0, mode->width, mode->height, GLFW_DONT_CARE);
        return;
    }
    Size s = window->parameters.getSize();
    glfwSetWindowMonitor(window->glfw_window, nullptr, 0, 0, s.Width, s.Height, GLFW_DONT_CARE);
}

void Window::Properties::toggleFullscreen()
{
    setFullscreen(!isFullscreen());
}

bool Window::Properties::isDecorated()
{
    return glfwGetWindowAttrib(window->glfw_window, GLFW_DECORATED);
}

void Window::Properties::setDecorated(bool decorated)
{
    glfwSetWindowAttrib(window->glfw_window, GLFW_DECORATED, decorated);
}

bool Window::Properties::isResizable()
{
    return glfwGetWindowAttrib(window->glfw_window, GLFW_RESIZABLE);
}

void Window::Properties::setResizable(bool resizable)
{
    glfwSetWindowAttrib(window->glfw_window, GLFW_RESIZABLE, resizable);
}

bool Window::Properties::isMaximized()
{
    return glfwGetWindowAttrib(window->glfw_window, GLFW_MAXIMIZED);
}

void Window::Properties::setMaximized(bool maximized)
{
    glfwSetWindowAttrib(window->glfw_window, GLFW_MAXIMIZED, maximized);
}

bool Window::Properties::isMinimized()
{
    return glfwGetWindowAttrib(window->glfw_window, GLFW_ICONIFIED);
}

void Window::Properties::setMinimized(bool minimized)
{
    glfwSetWindowAttrib(window->glfw_window, GLFW_ICONIFIED, minimized);
}

bool Window::Properties::isFocused()
{
    return glfwGetWindowAttrib(window->glfw_window, GLFW_FOCUSED);
}

void Window::Properties::setFocused(bool focused)
{
    glfwSetWindowAttrib(window->glfw_window, GLFW_FOCUSED, focused);
}

bool Window::Properties::isHovered()
{
    return glfwGetWindowAttrib(window->glfw_window, GLFW_HOVERED);
}

void Window::Properties::setHovered(bool hovered)
{
    glfwSetWindowAttrib(window->glfw_window, GLFW_HOVERED, hovered);
}

bool Window::Properties::isVisible()
{
    return glfwGetWindowAttrib(window->glfw_window, GLFW_VISIBLE);
}

void Window::Properties::setVisible(bool visible)
{
    glfwSetWindowAttrib(window->glfw_window, GLFW_VISIBLE, visible);
}

bool Window::Properties::isAlwaysOnTop()
{
    return glfwGetWindowAttrib(window->glfw_window, GLFW_FLOATING);
}

void Window::Properties::setAlwaysOnTop(bool alwaysOnTop)
{
    glfwSetWindowAttrib(window->glfw_window, GLFW_FLOATING, alwaysOnTop);
}

bool Window::Properties::isFocusOnShow()
{
    return glfwGetWindowAttrib(window->glfw_window, GLFW_FOCUS_ON_SHOW);
}

void Window::Properties::setFocusOnShow(bool focusOnShow)
{
    glfwSetWindowAttrib(window->glfw_window, GLFW_FOCUS_ON_SHOW, focusOnShow);
}

//______________________________________________________________________________________________________________________
// PROPERTIES  |  PROPERTIES  |  PROPERTIES  |  PROPERTIES  |  PROPERTIES  |  PROPERTIES  |  PROPERTIES  |  PROPERTIES  |  PROPERTIES  |  PROPERTIES  |  PROPERTIES  |  PROPERTIES  |  PROPERTIES  |  PROPERTIES  |  PROPERTIES  |  PROPERTIES  |  PROPERTIES
//______________________________________________________________________________________________________________________
#pragma endregion PROPERTIES

Window::Log::Log(Window &window)
{
    this->window = &window;
}

//______________________________________________________________________________________________________________________
// EVENTS  |  EVENTS  |  EVENTS  |  EVENTS  |  EVENTS  |  EVENTS  |  EVENTS  |  EVENTS  |  EVENTS  |  EVENTS  |  EVENTS
//______________________________________________________________________________________________________________________
#pragma region EVENTS

Window::Events::Events(Window &window)
{
    this->window = &window;
}

bool Window::Events::getKey(Keycode keycode)
{
    return window->input->getKey(static_cast<int>(keycode));
}

bool Window::Events::getKeyPressed(Keycode keycode)
{
    return window->input->getKeyPressed(static_cast<int>(keycode));
}

bool Window::Events::getKeyDown(Keycode keycode)
{
    return window->input->getKeyDown(static_cast<int>(keycode));
}

bool Window::Events::getKeyReleased(Keycode keycode)
{
    return window->input->getKeyReleased(static_cast<int>(keycode));
}

bool Window::Events::getKeyUp(Keycode keycode)
{
    return window->input->getKeyUp(static_cast<int>(keycode));
}

bool Window::Events::getMouseButton(MouseButton button)
{
    return window->input->getMouseButton(static_cast<int>(button));
}

bool Window::Events::getMouseButtonReleased(MouseButton button)
{
    return window->input->getMouseButtonReleased(static_cast<int>(button));
}

bool Window::Events::getMouseButtonDown(MouseButton button)
{
    return window->input->getMouseButtonDown(static_cast<int>(button));
}

//______________________________________________________________________________________________________________________
// EVENTS  |  EVENTS  |  EVENTS  |  EVENTS  |  EVENTS  |  EVENTS  |  EVENTS  |  EVENTS  |  EVENTS  |  EVENTS  |  EVENTS
//______________________________________________________________________________________________________________________
#pragma endregion EVENTS

Window::Keys::Keys(Window &window)
{
    this->window = &window;
}

void window::defaultResizeCallback(GLFWwindow *window, int width, int height)
{
    for (pandora::Object *object : pandora::objects::getObjcectsList())
    {
        if (!object->followWindowResize)
        {
            Size size = object->Components().get<pandora::Transform>()->size.toWindowRate(pandora::mainWindow::get()->parameters.getSize());
            std::vector<float> vertices = {
                // positions                                // texture coords
                static_cast<float>(-size.Width), static_cast<float>(-size.Height), 0.0f, 0.0f, 0.0f, // bottom left
                static_cast<float>(size.Width), static_cast<float>(-size.Height), 0.0f, 1.0f, 0.0f,  // bottom right
                static_cast<float>(size.Width), static_cast<float>(size.Height), 0.0f, 1.0f, 1.0f,   // top right
                static_cast<float>(-size.Width), static_cast<float>(size.Height), 0.0f, 0.0f, 1.0f   // top left
            };
            object->Components().get<pandora::Shader>()->setVerticies(vertices);
        }
    }
    if (scenes::getCurrentSceneID() != -1)
    {
        for (Object *object : scenes::getScenesList()[scenes::getCurrentSceneID()]->getObjectsList())
        {
            if (!object->followWindowResize)
            {
                Size size = object->Components().get<pandora::Transform>()->size.toWindowRate(pandora::mainWindow::get()->parameters.getSize());
                std::vector<float> vertices = {
                    // positions                                // texture coords
                    static_cast<float>(-size.Width), static_cast<float>(-size.Height), 0.0f, 0.0f, 0.0f, // bottom left
                    static_cast<float>(size.Width), static_cast<float>(-size.Height), 0.0f, 1.0f, 0.0f,  // bottom right
                    static_cast<float>(size.Width), static_cast<float>(size.Height), 0.0f, 1.0f, 1.0f,   // top right
                    static_cast<float>(-size.Width), static_cast<float>(size.Height), 0.0f, 0.0f, 1.0f   // top left
                };
                object->Components().get<pandora::Shader>()->setVerticies(vertices);
            }
        }
    }
    glViewport(0, 0, width, height);
}