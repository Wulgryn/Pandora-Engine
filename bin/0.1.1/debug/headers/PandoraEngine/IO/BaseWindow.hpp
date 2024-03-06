#pragma once
#include "../Core/Parameters.hpp"

class BaseWindow
{
private:
    Position windowPosition;
    Size windowSize;
    const char* windowTitle;
public:
    BaseWindow();
};

BaseWindow* createBaseWindow()
{
    return new BaseWindow();
}