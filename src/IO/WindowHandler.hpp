#pragma once
#include <vector>
class BaseWindow;

namespace WindowHandlers
{
    extern int liveWindows;

    std::vector<BaseWindow*>& BaseWindowsList();

    void AddWindow(BaseWindow* window);
    void RemoveWindow(BaseWindow* window);

    void RemoveWindowsEvent();
}