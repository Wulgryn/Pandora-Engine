#include "mouse.hpp"
#include "PANDORA/mainWindow.hpp"

using namespace io;
using namespace utils;

Position mouse::getWindowPosition()
{
    // Get the mouse position relative to the main window
    double mouseX, mouseY;
    glfwGetCursorPos(pandora::mainWindow::get()->getWindow(), &mouseX, &mouseY);

    // Create a Position object with the mouse position
    Position windowPos(static_cast<int>(mouseX), static_cast<int>(mouseY));

    return windowPos;
}

Position mouse::getScreenPosition()
{
    // Get the mouse position relative to the screen
    double mouseX, mouseY;
    glfwGetCursorPos(pandora::mainWindow::get()->getWindow(), &mouseX, &mouseY);

    Position windowPos = pandora::mainWindow::get()->parameters.getPosition();

    // Create a Position object with the mouse position
    Position screenPos(static_cast<int>(mouseX) + windowPos.x, static_cast<int>(mouseY) + windowPos.y);

    return screenPos;
}

bool mouse::getMouseButton(MouseButton button)
{
    return pandora::mainWindow::get()->events.getMouseButton(button);
}

bool mouse::getMouseButtonReleased(MouseButton button)
{
    return pandora::mainWindow::get()->events.getMouseButtonReleased(button);
}

bool mouse::getMouseButtonDown(MouseButton button)
{
    return pandora::mainWindow::get()->events.getMouseButtonDown(button);
}

double mouse::getMouseScroll()
{
    return pandora::mainWindow::get()->events.getMouseScroll();
}

void mouse::setScreenPosition(Position pos)
{
    Position windowPos = pandora::mainWindow::get()->parameters.getPosition();
    // Set the mouse position relative to the screen
    glfwSetCursorPos(pandora::mainWindow::get()->getWindow(), pos.x - windowPos.x, pos.y - windowPos.y);
}

void mouse::setWindowPosition(Position pos)
{
    // Set the mouse position relative to the main window
    glfwSetCursorPos(pandora::mainWindow::get()->getWindow(), pos.x, pos.y);
}