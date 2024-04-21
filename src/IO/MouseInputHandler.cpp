#include "InputHandler.hpp"
#include "Window.hpp"
#include "Debug/Console.hpp"

#include "GLFW/glfw3.h"

using namespace std;

void InputHandler::MouseCallBack(GLFWwindow* window, int button, int action, int mods)
{
    InputHandler* inputHandler = static_cast<Window*>(glfwGetWindowUserPointer(window))->GetInput();

    if (inputHandler->IsAutoRegisterButtonsEnabled && !inputHandler->IsButtonRegistered(button, false))
    {
        DebugConsole::WriteLine("<%d>[WARNING] Button not registered, registering it now.", button);
        inputHandler->RegisterButton(button);
    }

    if(!inputHandler->IsButtonRegistered(button, inputHandler->IsNotRegisteredButtonWarningEnabled)) return;

    switch (action)
    {
    case GLFW_PRESS:
        inputHandler->buttons[button].second[0] = true;
        inputHandler->buttons[button].second[1] = true;
        break;
    case GLFW_RELEASE:
        inputHandler->buttons[button].second[0] = false;
        inputHandler->buttons[button].second[1] = false;
        inputHandler->buttons[button].second[2] = true;
        break;
    default:
        DebugConsole::WriteLine("<%d>[WARNING] Unknown button action.", button);
        inputHandler->buttons[button].second[0] = false;
        inputHandler->buttons[button].second[1] = false;
        inputHandler->buttons[button].second[2] = false;
        break;
    }
}

void InputHandler::ScrollCallBack(GLFWwindow* window, double xoffset, double yoffset)
{
    InputHandler* inputHandler = static_cast<Window*>(glfwGetWindowUserPointer(window))->GetInput();
    inputHandler->mouse_scroll_x = xoffset;
    inputHandler->mouse_scroll_y = yoffset;
    DebugConsole::WriteLine("Mouse scroll: %f, %f", xoffset, yoffset);
}

void InputHandler::RegisterButton(int button, bool* button_states, int state_count)
{
    if (IsButtonRegistered(button, IsNotRegisteredButtonWarningEnabled))
    {
        DebugConsole::WriteLine("<%d>[WARNING] Button already registered.", button);
        return;
    }
    if(buttons.size() <= button) buttons.resize(button + 1);
    int states_count = 3;
    bool* _button_states = new bool[3]{false,false,false};
    if(button_states && state_count > 0) 
    {
        states_count += state_count;
        _button_states = new bool[3 + state_count]{false,false,false, *button_states};
    }
    buttons[button] = {states_count, _button_states};
}

void InputHandler::RegisterButton(Buttons button, bool* button_states, int state_count)
{
    RegisterButton(static_cast<int>(button), button_states, state_count);
}

void InputHandler::AddButton(int b, std::vector<bool> button_states)
{
    if (IsButtonRegistered(b, IsNotRegisteredButtonWarningEnabled))
    {
        DebugConsole::WriteLine("<%d>[WARNING] Button already registered.", b);
        return;
    }
    if(buttons.size() <= b) buttons.resize(b + 1);
    vector<bool> _button_states = {false,false,false};
    if(button_states.size() > 0) 
    {
        for (int i = 0; i < button_states.size(); i++)
        {
            _button_states.push_back(button_states[i]);
        }
    }
    bool* button_states_array = new bool[_button_states.size()];
    for (size_t i = 0; i < _button_states.size(); i++)
    {
        button_states_array[i] = _button_states[i];
    }
    
    buttons[b] = {_button_states.size(), button_states_array};
}

bool InputHandler::IsButtonRegistered(int b, bool throwWaringn)
{
    if (buttons.size() <= b)
    {
        if (throwWaringn) DebugConsole::WriteLine("<%d>[WARNING] Button not registered.", b);
        return false;
    }
    return buttons[b].first;
}


bool InputHandler::GetButton(int b)
{
    return IsButtonRegistered(b, IsNotRegisteredButtonWarningEnabled) && (buttons[b].second[0] || buttons[b].second[1] || buttons[b].second[2]);
}

bool InputHandler::GetButton(Buttons button)
{
    return GetButton(static_cast<int>(button));
}

bool InputHandler::GetButtonPressed(int b)
{
    return IsButtonRegistered(b, IsNotRegisteredButtonWarningEnabled) && buttons[b].second[0];
}

bool InputHandler::GetButtonPressed(Buttons button)
{
    return GetButtonPressed(static_cast<int>(button));
}

bool InputHandler::GetButtonDown(int b)
{
    return IsButtonRegistered(b, IsNotRegisteredButtonWarningEnabled) && buttons[b].second[1];
}

bool InputHandler::GetButtonDown(Buttons button)
{
    return GetButtonDown(static_cast<int>(button));
}

bool InputHandler::GetButtonReleased(int b)
{
    return IsButtonRegistered(b, IsNotRegisteredButtonWarningEnabled) && buttons[b].second[2];
}

bool InputHandler::GetButtonReleased(Buttons button)
{
    return GetButtonReleased(static_cast<int>(button));
}

bool InputHandler::GetButtonUp(int b)
{
    return IsButtonRegistered(b, IsNotRegisteredButtonWarningEnabled) && !buttons[b].second[0] && !buttons[b].second[1] && !buttons[b].second[2];
}

bool InputHandler::GetButtonUp(Buttons button)
{
    return GetButtonUp(static_cast<int>(button));
}

ParametersApp::Position InputHandler::GetMousePosition()
{
    double x, y;
    glfwGetCursorPos(window->GetGLFWWindow(), &x, &y);
    return {x, y};
}

int InputHandler::GetYMouseScroll()
{
    return mouse_scroll_y;
}

int InputHandler::GetXMouseScroll()
{
    return mouse_scroll_x;
}