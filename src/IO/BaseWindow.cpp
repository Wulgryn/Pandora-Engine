#include "BaseWindow.hpp"
#include "IO/Monitor.hpp"

BaseWindow::BaseWindow()
{
    windowPosition = Position(0, 0);
    windowSize = Size(800, 600);
    windowTitle = "Base Window";
}