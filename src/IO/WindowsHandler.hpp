#pragma once
#include <vector>

class BaseWindow;
class Window;
class GameWindow;

namespace BaseWindowsHandler
{
    std::vector<BaseWindow*>& WindowsList();
    int LiveWindowsCount();
    
    /// @brief Adds window to windowHandler, but it's a BaseWindow type so
    /// it won't be called from the Application by default
    /// @param window The Base Window.
    /// @return The index in the list of this BaseWindow.
    int AddWindow(BaseWindow* window);
    void RemoveWindow(BaseWindow* window);

    void RemoveWindowsEvent();
}

namespace WindowsHandler
{
    std::vector<Window*>& WindowsList();
    int LiveWindowsCount();

    /// @brief Adds window to windowHandler, and it's a Window type so
    /// it will be called from the Application by default
    /// @param window The Window.
    /// @return The index in the list of this Window.
    int AddWindow(Window* window);
    void RemoveWindow(Window* window);
}

namespace GameWindowsHandler
{
    std::vector<GameWindow*>& WindowsList();
    int LiveWindowsCount();

    /// @brief Adds window to windowHandler, and it's a GameWindow type so
    /// it will be called from the Application by default
    /// @param window The GameWindow.
    /// @return The index in the list of this GameWindow.
    int AddWindow(GameWindow* window);
    void RemoveWindow(GameWindow* window);
}