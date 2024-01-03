#include "input.hpp"
#include "CONSOLE/fancyLog.hpp"
#include "window.hpp"

using namespace io;
using namespace std;

void Input::keyCallback(GLFWwindow *window, int key, int scancode, int action, int mods)
{
    Input *input = static_cast<Input *>(glfwGetWindowUserPointer(window));
    if (!input)
        return;
    if (input->keys_list.size() <= key || !input->keys_list[key])
        input->registerKey(key);
    bool prev;
    switch (action)
    {
    case GLFW_PRESS:
        input->keys_list[key][0] = true;
        input->anyKey++;
        input->anyKeyPressed++;
        if (!input->getWindow()->keys.delay)
        {
            input->keys_list[key][1] = true;
            input->anyKeyDown++;
        }
        break;
    case GLFW_REPEAT:
        input->keys_list[key][0] = false;
        input->anyKeyPressed--;
        prev = input->keys_list[key][1];
        input->keys_list[key][1] = true;
        if (!prev)
            input->anyKeyDown++;
        break;
    case GLFW_RELEASE:
        input->keys_list[key][0] = false;
        prev = input->keys_list[key][1];
        input->keys_list[key][1] = false;
        if (prev)
            input->anyKeyDown--;
        input->keys_list[key][2] = true;
        input->anyKeyReleased++;
        break;
    }
}

void Input::mouseButtonCallback(GLFWwindow *window, int button, int action, int mods)
{
    Input *input = static_cast<Input *>(glfwGetWindowUserPointer(window));
    if (!input)
        return;
    if (input->mouse_buttons_list.size() <= button || !input->mouse_buttons_list[button])
        input->registerMouseButton(button);
    bool prev;
    switch (action)
    {
    case GLFW_PRESS:
        input->mouse_buttons_list[button][0] = true;
        input->anyMouseButton++;
        if (!input->getWindow()->keys.delay)
        {
            input->mouse_buttons_list[button][1] = true;
            input->anyMouseButtonDown++;
        }
        //logInfo("mouse pressed");
        break;
    case GLFW_RELEASE:
        // prev = input->mouse_buttons_list[button][0];
        input->mouse_buttons_list[button][0] = false;
        // if(prev)input->anyMouseButtonPressed--;
        prev = input->mouse_buttons_list[button][1];
        input->mouse_buttons_list[button][1] = false;
        if (prev)
            input->anyMouseButtonDown--;
        input->mouse_buttons_list[button][2] = true;
        input->mouse_buttons_list[button][4] = false;
        input->anyMouseButtonReleased++;
        // input->mouse_buttons_list[button][3] = false;
        break;
    }
}

void Input::mouseScrollCallback(GLFWwindow *window, double xoffset, double yoffset)
{
    //logInfo("Scroll: " + to_string(yoffset) + " " + to_string(xoffset));
    Input *input = static_cast<Input *>(glfwGetWindowUserPointer(window));
    if (!input)
        return;
    input->mouse_scroll = yoffset;
    //logInfo("Scroll: " + to_string(yoffset) + " " + to_string(xoffset));
}

Input::Input(Window *window)
{
    this->window = window;
    glfwSetWindowUserPointer(window->getWindow(), this);
    glfwSetKeyCallback(window->getWindow(), keyCallback);
    glfwSetMouseButtonCallback(window->getWindow(), mouseButtonCallback);
    glfwSetScrollCallback(window->getWindow(), mouseScrollCallback);
    // auto sum = [](int a, int b) {
    //     return a + b;
    // };
    registerKey(static_cast<int>(Keycode::A));
    registerKey(static_cast<int>(Keycode::Á));
    registerKey(static_cast<int>(Keycode::B));
    registerKey(static_cast<int>(Keycode::C));
    registerKey(static_cast<int>(Keycode::D));
    registerKey(static_cast<int>(Keycode::E));
    registerKey(static_cast<int>(Keycode::É));
    registerKey(static_cast<int>(Keycode::F));
    registerKey(static_cast<int>(Keycode::G));
    registerKey(static_cast<int>(Keycode::H));
    registerKey(static_cast<int>(Keycode::I));
    registerKey(static_cast<int>(Keycode::Í));
    registerKey(static_cast<int>(Keycode::J));
    registerKey(static_cast<int>(Keycode::K));
    registerKey(static_cast<int>(Keycode::L));
    registerKey(static_cast<int>(Keycode::M));
    registerKey(static_cast<int>(Keycode::N));
    registerKey(static_cast<int>(Keycode::Ñ));
    registerKey(static_cast<int>(Keycode::O));
    registerKey(static_cast<int>(Keycode::Ó));
    registerKey(static_cast<int>(Keycode::P));
    registerKey(static_cast<int>(Keycode::Q));
    registerKey(static_cast<int>(Keycode::R));
    registerKey(static_cast<int>(Keycode::S));
    registerKey(static_cast<int>(Keycode::T));
    registerKey(static_cast<int>(Keycode::U));
    registerKey(static_cast<int>(Keycode::Ú));
    registerKey(static_cast<int>(Keycode::Ü));
    registerKey(static_cast<int>(Keycode::Ű));
    registerKey(static_cast<int>(Keycode::V));
    registerKey(static_cast<int>(Keycode::W));
    registerKey(static_cast<int>(Keycode::X));
    registerKey(static_cast<int>(Keycode::Y));
    registerKey(static_cast<int>(Keycode::Z));

    registerKey(static_cast<int>(Keycode::ZERO));
    registerKey(static_cast<int>(Keycode::ONE));
    registerKey(static_cast<int>(Keycode::TWO));
    registerKey(static_cast<int>(Keycode::THREE));
    registerKey(static_cast<int>(Keycode::FOUR));
    registerKey(static_cast<int>(Keycode::FIVE));
    registerKey(static_cast<int>(Keycode::SIX));
    registerKey(static_cast<int>(Keycode::SEVEN));
    registerKey(static_cast<int>(Keycode::EIGHT));
    registerKey(static_cast<int>(Keycode::NINE));

    registerKey(static_cast<int>(Keycode::F1));
    registerKey(static_cast<int>(Keycode::F2));
    registerKey(static_cast<int>(Keycode::F3));
    registerKey(static_cast<int>(Keycode::F4));
    registerKey(static_cast<int>(Keycode::F5));
    registerKey(static_cast<int>(Keycode::F6));
    registerKey(static_cast<int>(Keycode::F7));
    registerKey(static_cast<int>(Keycode::F8));
    registerKey(static_cast<int>(Keycode::F9));
    registerKey(static_cast<int>(Keycode::F10));
    registerKey(static_cast<int>(Keycode::F11));
    registerKey(static_cast<int>(Keycode::F12));

    registerKey(static_cast<int>(Keycode::SPACE));
    registerKey(static_cast<int>(Keycode::ENTER));
    registerKey(static_cast<int>(Keycode::ESCAPE));
    registerKey(static_cast<int>(Keycode::BACKSPACE));
    registerKey(static_cast<int>(Keycode::TAB));
    registerKey(static_cast<int>(Keycode::CAPS_LOCK));
    registerKey(static_cast<int>(Keycode::LEFT_SHIFT));
    registerKey(static_cast<int>(Keycode::RIGHT_SHIFT));
    registerKey(static_cast<int>(Keycode::LEFT_CONTROL));
    registerKey(static_cast<int>(Keycode::RIGHT_CONTROL));
    registerKey(static_cast<int>(Keycode::LEFT_ALT));
    registerKey(static_cast<int>(Keycode::RIGHT_ALT));

    registerMouseButton(GLFW_MOUSE_BUTTON_LEFT);
    registerMouseButton(GLFW_MOUSE_BUTTON_RIGHT);
    registerMouseButton(GLFW_MOUSE_BUTTON_MIDDLE);
    registerMouseButton(GLFW_MOUSE_BUTTON_4);
    registerMouseButton(GLFW_MOUSE_BUTTON_5);
    registerMouseButton(GLFW_MOUSE_BUTTON_6);
    registerMouseButton(GLFW_MOUSE_BUTTON_7);
    registerMouseButton(GLFW_MOUSE_BUTTON_8);
}

Window *Input::getWindow()
{
    return window;
}

void Input::registerKey(int key)
{
    if (keys_list.size() <= key)
        keys_list.resize(key + 1);
    keys_list[key] = new bool[5]{false, false, false, false, false};
}

void Input::registerMouseButton(int key)
{
    if (mouse_buttons_list.size() <= key)
        mouse_buttons_list.resize(key + 1);
    mouse_buttons_list[key] = new bool[4]{false, false, false, false};
}
//______________________________________________________________________________________________________________________
// KEY  |  KEY  |  KEY  |  KEY  |  KEY  |  KEY  |  KEY  |  KEY  |  KEY  |  KEY  |  KEY  |  KEY  |  KEY  |  KEY  |  KEY  |  KEY  |  KEY
//______________________________________________________________________________________________________________________
#pragma region KEY

bool Input::getKey(int key)
{
    if (keys_list.size() <= key && key != -1)
    {
        logType("KEY(" + to_string(key) + ")");
        logWarning("Key not registered");
        logType();
        return false;
    }
    if (key == -1)
    {
        return anyKey > 0;
    }
    if (keys_list[key][0])
        keys_list[key][3] = true;
    if (keys_list[key][2])
        keys_list[key][4] = true;
    return keys_list[key][0] || keys_list[key][1] || keys_list[key][2];
}

bool Input::getKeyPressed(int key)
{
    if (keys_list.size() <= key && key != -1)
    {
        logType("KEY(" + to_string(key) + ")");
        logWarning("Key not registered");
        logType();
        return false;
    }
    // bool keys[] = {keys_list[key][0], keys_list[key][1], keys_list[key][2], keys_list[key][3]};
    if (key == -1)
    {
        return anyKeyPressed > 0;
    }
    keys_list[key][3] = true;
    bool b = keys_list[key][0];
    // keys_list[key][0] = false;
    return b;
}

bool Input::getKeyDown(int key)
{
    if (keys_list.size() <= key && key != -1)
    {
        logType("KEY(" + to_string(key) + ")");
        logWarning("Key not registered");
        logType();
        return false;
    }
    if (key == -1)
    {
        return anyKeyDown > 0;
    }
    return keys_list[key][1];
}

bool Input::getKeyReleased(int key)
{
    if (keys_list.size() <= key && key != -1)
    {
        logType("KEY(" + to_string(key) + ")");
        logWarning("Key not registered");
        logType();
        return false;
    }
    if (key == -1)
    {
        return anyKeyReleased > 0;
    }
    keys_list[key][4] = true;
    bool b = keys_list[key][2];
    // keys_list[key][2] = false;
    return b;
}

bool Input::getKeyUp(int key)
{
    if (keys_list.size() <= key && key != -1)
    {
        logType("KEY(" + to_string(key) + ")");
        logWarning("Key not registered");
        logType();
        return false;
    }
    if (key == -1)
    {
        return anyKeyUp > 0;
    }
    return !keys_list[key][0] && !keys_list[key][1] && !keys_list[key][2];
}

//______________________________________________________________________________________________________________________
// KEY  |  KEY  |  KEY  |  KEY  |  KEY  |  KEY  |  KEY  |  KEY  |  KEY  |  KEY  |  KEY  |  KEY  |  KEY  |  KEY  |  KEY  |  KEY  |  KEY
//______________________________________________________________________________________________________________________
#pragma endregion KEY

//______________________________________________________________________________________________________________________
// MOUSE  |  MOUSE  |  MOUSE  |  MOUSE  |  MOUSE  |  MOUSE  |  MOUSE  |  MOUSE  |  MOUSE  |  MOUSE  |  MOUSE  |  MOUSE  |  MOUSE  |  MOUSE  |  MOUSE  |  MOUSE  |  MOUSE
//______________________________________________________________________________________________________________________
#pragma region MOUSE

bool Input::getMouseButtonDown(int button)
{
    if (mouse_buttons_list.size() <= button && button != -1)
    {
        logType("MOUSE_BUTTON(" + to_string(button) + ")");
        logWarning("Mouse button not registered");
        logType();
        return false;
    }
    if (button == -1)
    {
        return anyMouseButtonDown > 0;
    }
    return mouse_buttons_list[button][0];
}

bool Input::getMouseButton(int button)
{
    if (mouse_buttons_list.size() <= button && button != -1)
    {
        logType("MOUSE_BUTTON(" + to_string(button) + ")");
        logWarning("Mouse button not registered");
        logType();
        return false;
    }
    if (button == -1)
    {
        return anyMouseButton > 0;
    }
    // bool btns[5] = {mouse_buttons_list[button][0], mouse_buttons_list[button][1], mouse_buttons_list[button][2], mouse_buttons_list[button][3], mouse_buttons_list[button][4]};
    // if(mouse_buttons_list[button][0]) mouse_buttons_list[button][3] = true;
    if (mouse_buttons_list[button][2])
        mouse_buttons_list[button][4] = true;
    return mouse_buttons_list[button][0] || mouse_buttons_list[button][1] || mouse_buttons_list[button][2];
}

bool Input::getMouseButtonReleased(int button)
{
    if (mouse_buttons_list.size() <= button && button != -1)
    {
        logType("MOUSE_BUTTON(" + to_string(button) + ")");
        logWarning("Mouse button not registered");
        logType();
        return false;
    }
    if (button == -1)
    {
        return anyMouseButtonReleased > 0;
    }
    mouse_buttons_list[button][4] = true;
    //if(mouse_buttons_list[button][2])
    //{
    //    bool btns[5] = {mouse_buttons_list[button][0], mouse_buttons_list[button][1], mouse_buttons_list[button][2], mouse_buttons_list[button][3], mouse_buttons_list[button][4]};
    //}
    return mouse_buttons_list[button][2];
}
//______________________________________________________________________________________________________________________
// MOUSE  |  MOUSE  |  MOUSE  |  MOUSE  |  MOUSE  |  MOUSE  |  MOUSE  |  MOUSE  |  MOUSE  |  MOUSE  |  MOUSE  |  MOUSE  |  MOUSE  |  MOUSE  |  MOUSE  |  MOUSE  |  MOUSE
//______________________________________________________________________________________________________________________
#pragma endregion MOUSE

void Input::resetInputs()
{
    bool pressed, down;
    anyKeyUp = 0;
    for (int i = 0; i < keys_list.size(); i++)
    {
        if (!keys_list[i])
            continue;
        pressed = keys_list[i][0];
        down = keys_list[i][1];
        if (!pressed && !down)
            anyKeyUp++;
        if (keys_list[i][0] && keys_list[i][3])
            keys_list[i][0] = false;
        if (keys_list[i][2] && keys_list[i][4])
            keys_list[i][2] = false;
        keys_list[i][3] = false;
        keys_list[i][4] = false;
    }
    // anyKey = 0;
    anyKeyPressed = 0;
    // anyKeyDown = 0;
    anyKeyReleased = 0;
    bool pressedMouse, downMouse;
    for (int i = 0; i < mouse_buttons_list.size(); i++)
    {
        if (!mouse_buttons_list[i])
            continue;
        pressedMouse = mouse_buttons_list[i][0];
        downMouse = mouse_buttons_list[i][1];

        if (mouse_buttons_list[i][0] && mouse_buttons_list[i][3]) mouse_buttons_list[i][0] = false;
        mouse_buttons_list[i][2] = false;
        mouse_buttons_list[i][4] = false;
        mouse_buttons_list[i][3] = false;
    }
    // anyMouseButton = 0;
    anyMouseButtonReleased = 0;
    mouse_scroll = 0;
}

double Input::getMouseScroll()
{
    return mouse_scroll;
}