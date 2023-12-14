#include "mainWindow.hpp"

using namespace pandora;
using namespace io;

Window *main_window = nullptr;

void mainWindow::set(Window *window)
{
    main_window = window;
}

Window *mainWindow::get()
{
    return main_window;
}