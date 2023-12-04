#include "window.hpp"

#include <iostream>

#include "glad/gl.h"

#include "CONSOLE/fancyLog.hpp"
#include <thread>
#include <future>
#include <chrono>
#include "UTILS/timer.hpp"

using namespace io;
using namespace std;
using namespace utils;
using namespace utils::_2D_;

Window::Window(int width, int height, string title)
{
    GLFWwindow *window = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);
    // Set the window object
    this->glfw_window = window;
    parameters.setSize(Size(width, height));
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
}

Window::~Window()
{
    // Destroy the GLFW window
    glfwDestroyWindow(this->glfw_window);
    logInfo("GLFW window destroyed!");
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

void Window::setTargetFPS(int targetFPS)
{
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

void updateThreadCallback(int (*updateFunction)(int, Window &), int currentFPS, Window &window, int &result)
{
    result = updateFunction(currentFPS, window);
}

void Window::start()
{
    double currentTime = glfwGetTime();

    double targetFrameTime = 1.0 / targetFPS;
    double fps_currentTime = currentTime;

    double targetTickTime = 1.0 / targetTPS;
    double tps_currentTime = currentTime;
    
    int FPS_count = 0;
    //double lastFPStime = currentTime;

    int TPS_count = 0;
    //double lastTPStime = currentTime;

    double lasLogTime = currentTime;

    int result = setupFunction();

    if (result == -1)
    {
        // Close the window
        glfwSetWindowShouldClose(glfw_window, true);
        return;
    }
    result = startFunction(*this);
    if (result == -1)
    {
        // Close the window
        glfwSetWindowShouldClose(glfw_window, true);
        return;
    }
    future<void> updateFuture;
    thread updateThread;
    Timer timer;
    timer.timeType = "RENDER_THREAD_TIME";
    timer.logTimeOnStop = false;
    while (!glfwWindowShouldClose(glfw_window))
    {
        timer.start();
        currentTime = glfwGetTime();


        if (result == -1)
        {
            // Close the window
            glfwSetWindowShouldClose(glfw_window, true);
        }


        if ( tps_currentTime + targetTickTime < currentTime || targetTPS == -1)
        {
            tps_currentTime = currentTime;
            TPS_count++;
            if (!properties.waitForUpdate)
            {
                if(!updateFuture.valid()) updateFuture = async(launch::async, updateThreadCallback, updateFunction, currentFPS, ref(*this), ref(result));
                // updateThread = thread(updateThreadCallback, updateFunction, currentFPS, ref(*this), ref(result));
                // updateThread.detach();
            }
            else result = updateFunction(currentFPS, *this);
        }



        if (fps_currentTime + targetFrameTime < currentTime || targetFPS == -1)
        {
            fps_currentTime = currentTime;
            FPS_count++;

            // Swap the buffers
            glfwSwapBuffers(glfw_window);
            // Poll for events
            glfwPollEvents();
        }



        timer.stop();

        if(lasLogTime + 1.0 < currentTime)
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
            if(log.logMainThreadTime)
            {
                logType("MAIN_THREAD_TIME");
                logInfo(timer.getEllapsedTime(timer::TimerClockPrecision::NANOSECOND));
                logType();
            }
        }
    }
    if (updateFuture.valid())
        updateFuture.wait();
}

Window::Parameters::Parameters(Window &window)
{
    this->window = &window;
}

Location Window::Parameters::getLocation()
{
    int x, y;
    glfwGetWindowPos(window->glfw_window, &x, &y);
    return Location(x, y);
}

void Window::Parameters::setLocation(Location location)
{
    glfwSetWindowPos(window->glfw_window, location.ix, location.iy);
}

Size Window::Parameters::getSize()
{
    Size size;
    int width, height;
    glfwGetWindowSize(window->glfw_window, &width, &height);
    return size.set(width, height);
}

void Window::Parameters::setSize(Size size)
{
    glfwSetWindowSize(window->glfw_window, size.iHeight, size.iHeight);
}

Window::Properties::Properties(Window &window)
{
    this->window = &window;
    primary_monitor = glfwGetPrimaryMonitor();
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
    glfwSetWindowMonitor(window->glfw_window, nullptr, 0, 0, s.iWidth, s.iHeight, GLFW_DONT_CARE);
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

Window::Log::Log(Window &window)
{
    this->window = &window;
}