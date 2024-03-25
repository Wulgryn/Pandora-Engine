#include "MainWindow.hpp"

#include "BaseWindow.hpp"
#include "Window.hpp"
#include "GameWindow.hpp"

namespace MainBaseWindow
{
    BaseWindow* mainBaseWindow;
    void SetWindow(BaseWindow* window)
    {
        mainBaseWindow = window;
    }
    BaseWindow* GetWindow()
    {
        return mainBaseWindow;
    }
} // namespace MainBaseWindow

namespace MainWindow
{
    Window* mainWindow;
    void SetWindow(Window* window)
    {
        mainWindow = window;
    }
    Window* GetWindow()
    {
        return mainWindow;
    }
} // namespace MainWindow

namespace MainGameWindow
{
    GameWindow* mainGameWindow;
    void SetWindow(GameWindow* window)
    {
        mainGameWindow = window;
    }
    GameWindow* GetWindow()
    {
        return mainGameWindow;
    }
} // namespace MainGameWindow