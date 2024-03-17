#include "WindowHandler.hpp"

#include "BaseWindow.hpp"

using namespace std;

vector<int>& RemovableBaseWindowsList()
{
    static vector<int> window_ids;
    return window_ids;
}

vector<BaseWindow*>& WindowHandlers::BaseWindowsList()
{
    static vector<BaseWindow*> windows;
    return windows;
}

int WindowHandlers::liveWindows = 0; // Declare and initialize the static variable

void WindowHandlers::AddWindow(BaseWindow* window)
{
    liveWindows++;
    BaseWindowsList().push_back(window);
}

void WindowHandlers::RemoveWindow(BaseWindow* window)
{
    RemovableBaseWindowsList().push_back(window->GetWindowID());
}

void WindowHandlers::RemoveWindowsEvent()
{
    for (int i = 0; i < RemovableBaseWindowsList().size(); i++)
    {
        for (auto it = BaseWindowsList().begin(); it != BaseWindowsList().end(); it++)
        {
            if ((*it)->GetWindowID() == RemovableBaseWindowsList()[i])
            {
                (*it)->Destroy();
                BaseWindowsList().erase(it);
                liveWindows = BaseWindowsList().size();
                RemovableBaseWindowsList().erase(RemovableBaseWindowsList().begin() + i);
                break;
            }
        }
    }
}