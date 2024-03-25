#include "WindowsHandler.hpp"

#include "BaseWindow.hpp"
#include "Window.hpp"
#include "GameWindow.hpp"

#include "Debug/Console.hpp"

using namespace std;

vector<BaseWindow*> &RemovableBaseWindowsList()
{
    static vector<BaseWindow*> windows;
    return windows;
}

namespace WindowsHandler
{
    vector<Window *> &WindowsList()
    {
        static vector<Window *> windows;
        return windows;
    }

    int LiveWindowsCount()
    {
        return WindowsList().size();
    }

    int AddWindow(Window *window)
    {
        WindowsList().push_back(window);
        return WindowsList().size() - 1;
    }

    void RemoveWindow(Window *window)
    {
        BaseWindowsHandler::RemoveWindow(window);
    }

    void RemoveFromList(BaseWindow* window)
    {
        for(int i = 0; i < WindowsList().size(); i++)
        {
            if(WindowsList()[i] == window)
            {
                WindowsList().erase(WindowsList().begin() + i);
                break;
            }
        }
    }
}

namespace GameWindowsHandler
{
    vector<GameWindow *> &WindowsList()
    {
        static vector<GameWindow *> windows;
        return windows;
    }

    int LiveWindowsCount()
    {
        return WindowsList().size();
    }


    int AddWindow(GameWindow *window)
    {
        WindowsList().push_back(window);
        return WindowsList().size() - 1;
    }

    void RemoveWindow(GameWindow *window)
    {
        BaseWindowsHandler::RemoveWindow(window);
    }

    void RemoveFromList(BaseWindow* window)
    {
        for(int i = 0; i < WindowsList().size(); i++)
        {
            if(WindowsList()[i] == window)
            {
                WindowsList().erase(WindowsList().begin() + i);
                break;
            }
        }
    }
}

namespace BaseWindowsHandler
{
    vector<BaseWindow *> &WindowsList()
    {
        static vector<BaseWindow *> windows;
        return windows;
    }

    int LiveWindowsCount()
    {
        return WindowsList().size();
    }


    int AddWindow(BaseWindow *window)
    {
        WindowsList().push_back(window);
        return WindowsList().size() - 1;
    }

    void RemoveWindow(BaseWindow *window)
    {
        RemovableBaseWindowsList().push_back(window);
    }

    void RemoveWindowsEvent()
    {
        for(int i = 0; i < RemovableBaseWindowsList().size(); i++)
        {
            int index = RemovableBaseWindowsList()[i]->Destroy();
            RemovableBaseWindowsList().erase(RemovableBaseWindowsList().begin() + i);
            WindowsList().erase(WindowsList().begin() + index);
            WindowsHandler::RemoveFromList(RemovableBaseWindowsList()[i]);
            GameWindowsHandler::RemoveFromList(RemovableBaseWindowsList()[i]);
        }
    }
}