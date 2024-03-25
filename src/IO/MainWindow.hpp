class BaseWindow;
class Window;
class GameWindow;
namespace MainBaseWindow
{
    void SetWindow(BaseWindow* window);
    BaseWindow* GetWindow();
} // namespace MainBaseWindow

namespace MainWindow
{
    void SetWindow(Window* window);
    Window* GetWindow();
} // namespace MainWindow

namespace MainGameWindow
{
    void SetWindow(GameWindow* window);
    GameWindow* GetWindow();
} // namespace MainGameWindow
