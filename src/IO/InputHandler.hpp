#pragma once

#include "../Core/Parameters.hpp"

#include <vector>
#include <string>

class Window;
class GLFWwindow;

enum class Keys
{
    ANY, // FIXME CAUTION: not working
    ESCAPE = 256,
    F1 = 290,
    F2 = 291,
    F3 = 292,
    F4 = 293,
    F5 = 294,
    F6 = 295,
    F7 = 296,
    F8 = 297,
    F9 = 298,
    F10 = 299,
    F11 = 300,
    F12 = 301,
    PRINT_SCREEN = 283,
    SCROLL_LOCK = 281,    
    PAUSE = 284,
    INSERT = 260,
    DELETE = 261,
    HOME = 268,
    END = 269,
    PAGE_UP = 266,
    PAGE_DOWN = 267,
    ARROW_UP = 265,
    ARROW_DOWN = 264,
    ARROW_LEFT = 263,
    ARROW_RIGHT = 262,
    RIGHT_SHIFT = 344,
    RIGHT_CONTROL = 345,
    LEFT_SHIFT = 340,
    LEFT_CONTROL = 341,
    LEFT_ALT = 342,
    TAB = 258,
    CAPS_LOCK = 280,
    BACKSPACE = 259,
    ENTER = 257,
    NUM_LOCK = 282,
    SPACE = 32,
    RIGHT_ALT = 346,
    NUM_0 = 347,
    NUM_1 = 348,
    NUM_2 = 349,
    NUM_3 = 350,
    NUM_4 = 351,
    NUM_5 = 352,
    NUM_6 = 353,
    NUM_7 = 354,
    NUM_8 = 355,
    NUM_9 = 356,
    NUM_DECIMAL = 358,
    NUM_ADD = 361,
    NUM_SUBTRACT = 359,
    NUM_MULTIPLY = 363,
    NUM_ENTER = 335,

};

enum class Buttons
{
    ANY, // FIXME CAUTION: not working
    LEFT = 0,
    RIGHT = 1,
    MIDDLE = 2,
};

class InputHandler
{
private:
    Window* window;

    // @brief The keys that are registered.
    // @param int the key states count.
    // @param bool* the key states.
    std::vector<std::pair<int,bool*>> keys;

    // @brief The buttons that are registered.
    // @param int the button states count.
    // @param bool* the button states.
    std::vector<std::pair<int,bool*>> buttons;
    
    double mouse_scroll_y = 0;
    double mouse_scroll_x = 0;

    static void KeyCallBack(GLFWwindow* window, int key, int scancode, int action, int mods);
    static void MouseCallBack(GLFWwindow* window, int button, int action, int mods);
    static void ScrollCallBack(GLFWwindow* window, double xoffset, double yoffset);
public:
    // @brief If true, the keys will be registered automatically on press.
    // @note  Default is true.
    // @note  If false, you have to call RegisterKey() manually.
    bool IsAutoRegisterKeysEnabled = true;
    bool IsKeyDelayed = false;
    bool IsNotRegisteredKeyWarningEnabled = true;

    bool IsAutoRegisterButtonsEnabled = true;
    bool IsNotRegisteredButtonWarningEnabled = true;

    InputHandler(Window* window);

    // @brief Resets all the inputs.
    void ResetInputs();

    // @brief Registers a key.
    // @param str The key to register.
    // @param key The key states to register. If set, it will be inserted after the 3 default ones {default_bool, default_bool, default_bool, your bools...}.
    // @param state_count The count of your key states.
    void RegisterKey(std::string key, bool* key_states = nullptr, int state_count = 0);

    // @brief Registers a key.
    // @param k The key to register.
    // @param key The key states to register. If set, it will be inserted after the 3 default ones {default_bool, default_bool, default_bool, your bools...}.
    // @param state_count The count of your key states.
    void RegisterKey(int key, bool* key_states = nullptr, int state_count = 0);

    // @brief Registers a key.
    // @param k The key to register.
    // @param key The key states to register. If set, it will be inserted after the 3 default ones {default_bool, default_bool, default_bool, your bools...}.
    // @param state_count The count of your key states.
    void RegisterKey(Keys key, bool* key_states = nullptr, int state_count = 0);

    // @brief Registers a key.
    // @param str The key to register.
    // @param key_states The key states to register in addition the default ones. If set, it will be inserted after the 3 default ones {default_bool, default_bool, default_bool, your bools...}.
    void AddKey(std::string str, std::vector<bool> key_states = {});


    void RegisterButton(int button, bool* button_states = nullptr, int state_count = 0);
    void RegisterButton(Buttons button, bool* button_states = nullptr, int state_count = 0);
    void AddButton(int b, std::vector<bool> button_states = {});


    bool IsKeyRegistered(int k, bool throwWaringn = true);
    bool IsButtonRegistered(int b, bool throwWaringn = true);


    bool GetKey(std::string str);
    bool GetKey(Keys key);

    bool GetKeyPressed(std::string str);
    bool GetKeyPressed(Keys key);

    bool GetKeyDown(std::string str);
    bool GetKeyDown(Keys key);

    bool GetKeyReleased(std::string str);
    bool GetKeyReleased(Keys key);

    bool GetKeyUp(std::string str);
    bool GetKeyUp(Keys key);

    
    bool GetButton(int b);
    bool GetButton(Buttons button);

    bool GetButtonPressed(int b);
    bool GetButtonPressed(Buttons button);

    bool GetButtonDown(int b);
    bool GetButtonDown(Buttons button);

    bool GetButtonReleased(int b);
    bool GetButtonReleased(Buttons button);

    bool GetButtonUp(int b);
    bool GetButtonUp(Buttons button);

    ParametersApp::Position GetMousePosition();
    int GetYMouseScroll();
    int GetXMouseScroll();
};