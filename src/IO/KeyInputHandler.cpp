#include "InputHandler.hpp"
#include "Window.hpp"
#include "Debug/Console.hpp"

#include "GLFW/glfw3.h"

#include <iostream>
#include <string>

using namespace  std;

// HACK CAUTION: Unicode support
/**
 *^  *=======================================================================
 *^  * DESCRIPTION: Make it so that unicode characters also working.
 *^  *=======================================================================
**/

unsigned int utf8_to_unicode(const std::string& str, size_t index) {
    unsigned int code = 0;
    unsigned char c = static_cast<unsigned char>(str[index]);
    if ((c & 0x80) == 0) {
        // 1 bájtos karakter
        code = c;
    } else if ((c & 0xE0) == 0xC0) {
        // 2 bájtos karakter
        code = (c & 0x1F) << 6;
        code |= static_cast<unsigned char>(str[index + 1]) & 0x3F;
    } else if ((c & 0xF0) == 0xE0) {
        // 3 bájtos karakter
        code = (c & 0x0F) << 12;
        code |= (static_cast<unsigned char>(str[index + 1]) & 0x3F) << 6;
        code |= static_cast<unsigned char>(str[index + 2]) & 0x3F;
    }
    return code;
}

void InputHandler::KeyCallBack(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    InputHandler* inputHandler = static_cast<Window*>(glfwGetWindowUserPointer(window))->GetInput();
    const char* keyName = glfwGetKeyName(key, scancode);
    keyName = keyName ? keyName : "Unknown";

    if(keyName != "Unknown" && (key < 256 || key > 348)) key =  utf8_to_unicode(keyName, 0);
    
    if (inputHandler->IsAutoRegisterKeysEnabled && !inputHandler->IsKeyRegistered(key, false))
    {
        DebugConsole::WriteLine("<%c(%d)>[WARNING] Key not registered, registering it now.", static_cast<char32_t>(key), key);
        inputHandler->RegisterKey(key);
    }

    if(!inputHandler->IsKeyRegistered(key, inputHandler->IsNotRegisteredKeyWarningEnabled)) return;

    switch (action)
    {
    case GLFW_PRESS:
        inputHandler->keys[key].second[0] = true;
        if(!inputHandler->IsKeyDelayed) inputHandler->keys[key].second[1] = true;
        break;
    case GLFW_REPEAT:
        //DebugConsole::WriteLine("<%c(%d)>Key repeated.", (char)key, key);
        inputHandler->keys[key].second[0] = false;
        inputHandler->keys[key].second[1] = true;
        break;
    case GLFW_RELEASE:
        //DebugConsole::WriteLine("<%c(%d)>Key released.", (char)key, key);
        inputHandler->keys[key].second[0] = false;
        inputHandler->keys[key].second[1] = false;
        inputHandler->keys[key].second[2] = true;
        break;
    default:
        DebugConsole::WriteLine("<%c(%d)>[WARNING] Unknown key action.", static_cast<char32_t>(key), key);
        inputHandler->keys[key].second[0] = false;
        inputHandler->keys[key].second[1] = false;
        inputHandler->keys[key].second[2] = false;
        break;
    }
}

InputHandler::InputHandler(Window* window)
{
    this->window = window;
    glfwSetKeyCallback(window->GetGLFWWindow(), KeyCallBack);
    glfwSetMouseButtonCallback(window->GetGLFWWindow(), MouseCallBack);
    glfwSetScrollCallback(window->GetGLFWWindow(), ScrollCallBack);
}

void InputHandler::ResetInputs()
{
    for (int i = 0; i < keys.size(); i++)
    {
        if(!IsKeyRegistered(i)) continue;
        keys[i].second[0] = false;
        keys[i].second[2] = false;
    }
    for (int i = 0; i < buttons.size(); i++)
    {
        if(!IsButtonRegistered(i)) continue;
        buttons[i].second[0] = false;
        buttons[i].second[2] = false;
    }
    mouse_scroll_x = 0;
    mouse_scroll_y = 0;
}

void InputHandler::RegisterKey(string str, bool* key_states, int state_count)
{
    unsigned int k = utf8_to_unicode(str, 0);
    if(keys.size() <= k) keys.resize(k + 1);
    int states_count = 3;
    bool* _key_states = new bool[3]{false,false,false};
    if(key_states && state_count > 0) 
    {
        states_count += state_count;
        _key_states = new bool[3 + state_count]{false,false,false, *key_states};
    }
    keys[k] = {states_count, _key_states};
}

void InputHandler::RegisterKey(int k, bool* key_states, int state_count)
{
    if(IsKeyRegistered(k, false))
    {
        DebugConsole::WriteLine("<%c(%d)>[WARNING] Key already registered.", static_cast<char32_t>(k),k);
        return;
    }
    if(keys.size() <= k) keys.resize(k + 1);
    int states_count = 3;
    bool* _key_states = new bool[3]{false,false,false};
    if(key_states && state_count > 0) 
    {
        states_count += state_count;
        _key_states = new bool[3 + state_count]{false,false,false, *key_states};
    }
    keys[k] = {states_count, _key_states};
}

void InputHandler::RegisterKey(Keys key, bool* key_states, int state_count)
{
    int k = static_cast<int>(key);
    if(IsKeyRegistered(k, false))
    {
        DebugConsole::WriteLine("<%c(%d)>[WARNING] Key already registered.", static_cast<char32_t>(k),k);
        return;
    }
    if(keys.size() <= k) keys.resize(k + 1);
    int states_count = 3;
    bool* _key_states = new bool[3]{false,false,false};
    if(key_states && state_count > 0) 
    {
        states_count += state_count;
        _key_states = new bool[3 + state_count]{false,false,false, *key_states};
    }
    keys[k] = {states_count, _key_states};
}

void InputHandler::AddKey(string str, std::vector<bool> key_states)
{
    unsigned int k = utf8_to_unicode(str, 0);
    if(keys.size() <= k) keys.resize(k + 1);
    std::vector<bool> _key_states = {false,false,false};
    if(key_states.size() > 0) 
    {
        for (size_t i = 0; i < key_states.size(); i++) _key_states.push_back(key_states[i]);
    }
    bool* key_states_array = new bool[_key_states.size()];
    for (size_t i = 0; i < _key_states.size(); i++) {
        key_states_array[i] = _key_states[i];
    }
    keys[k] = {_key_states.size(), key_states_array};
}

bool InputHandler::IsKeyRegistered(int k, bool throwWaringn)
{
    if(keys.size() <= k)
    {
        if(throwWaringn) DebugConsole::WriteLine("<%c(%d)>[WARNING] Key not registered.", static_cast<char32_t>(k),k);
        return false;
    } 
    return keys[k].first;
}


bool InputHandler::GetKey(string str)
{
    unsigned int k = utf8_to_unicode(str, 0);
    return IsKeyRegistered(k, IsNotRegisteredKeyWarningEnabled) && (keys[k].second[0] || keys[k].second[1] || keys[k].second[2]);
}

bool InputHandler::GetKey(Keys key)
{
    int k = static_cast<int>(key);
    return IsKeyRegistered(k, IsNotRegisteredKeyWarningEnabled) && (keys[k].second[0] || keys[k].second[1] || keys[k].second[2]);
}

bool InputHandler::GetKeyPressed(string str)
{
    unsigned int k = utf8_to_unicode(str, 0);
    return IsKeyRegistered(k, IsNotRegisteredKeyWarningEnabled) && keys[k].second[0];
}

bool InputHandler::GetKeyPressed(Keys key)
{
    int k = static_cast<int>(key);
    return IsKeyRegistered(k, IsNotRegisteredKeyWarningEnabled) && keys[k].second[0];
}

bool InputHandler::GetKeyDown(string str)
{
    unsigned int k = utf8_to_unicode(str, 0);
    return IsKeyRegistered(k, IsNotRegisteredKeyWarningEnabled) && keys[k].second[1];
}

bool InputHandler::GetKeyDown(Keys key)
{
    int k = static_cast<int>(key);
    return IsKeyRegistered(k, IsNotRegisteredKeyWarningEnabled) && keys[k].second[1];
}

bool InputHandler::GetKeyReleased(string str)
{
    unsigned int k = utf8_to_unicode(str, 0);
    return IsKeyRegistered(k, IsNotRegisteredKeyWarningEnabled) && keys[k].second[2];
}

bool InputHandler::GetKeyReleased(Keys key)
{
    int k = static_cast<int>(key);
    return IsKeyRegistered(k, IsNotRegisteredKeyWarningEnabled) && keys[k].second[2];
}

bool InputHandler::GetKeyUp(string str)
{
    unsigned int k = utf8_to_unicode(str, 0);
    return IsKeyRegistered(k, IsNotRegisteredKeyWarningEnabled) && !keys[k].second[0] && !keys[k].second[1] && !keys[k].second[2];
}

bool InputHandler::GetKeyUp(Keys key)
{
    int k = static_cast<int>(key);
    return IsKeyRegistered(k, IsNotRegisteredKeyWarningEnabled) && !keys[k].second[0] && !keys[k].second[1] && !keys[k].second[2];
}