#pragma once
#include "DLL/dll.hpp"
#define GLFW_INCLUDE_NONE
#include "GLFW/glfw3.h"

#include <string>

#include "UTILS/parameters.hpp"
#include "input.hpp"

namespace io
{
    enum class Keycode
    {
        ANY = -1,
        A = GLFW_KEY_A,
        Á = (int)L'á',
        B = GLFW_KEY_B,
        C = GLFW_KEY_C,
        D = GLFW_KEY_D,
        E = GLFW_KEY_E,
        É = (int)L'é',
        F = GLFW_KEY_F,
        G = GLFW_KEY_G,
        H = GLFW_KEY_H,
        I = GLFW_KEY_I,
        Í = (int)L'í',
        J = GLFW_KEY_J,
        K = GLFW_KEY_K,
        L = GLFW_KEY_L,
        M = GLFW_KEY_M,
        N = GLFW_KEY_N,
        Ñ = (int)L'ñ',
        O = GLFW_KEY_O,
        Ó = (int)L'ó',
        P = GLFW_KEY_P,
        Q = GLFW_KEY_Q,
        R = GLFW_KEY_R,
        S = GLFW_KEY_S,
        T = GLFW_KEY_T,
        U = GLFW_KEY_U,
        Ú = (int)L'ú',
        Ü = (int)L'ü',
        Ű = (int)L'ű',
        V = GLFW_KEY_V,
        W = GLFW_KEY_W,
        X = GLFW_KEY_X,
        Y = GLFW_KEY_Y,
        Z = GLFW_KEY_Z,

        ZERO = GLFW_KEY_0,
        ONE = GLFW_KEY_1,
        TWO = GLFW_KEY_2,
        THREE = GLFW_KEY_3,
        FOUR = GLFW_KEY_4,
        FIVE = GLFW_KEY_5,
        SIX = GLFW_KEY_6,
        SEVEN = GLFW_KEY_7,
        EIGHT = GLFW_KEY_8,
        NINE = GLFW_KEY_9,

        F1 = GLFW_KEY_F1,
        F2 = GLFW_KEY_F2,
        F3 = GLFW_KEY_F3,
        F4 = GLFW_KEY_F4,
        F5 = GLFW_KEY_F5,
        F6 = GLFW_KEY_F6,
        F7 = GLFW_KEY_F7,
        F8 = GLFW_KEY_F8,
        F9 = GLFW_KEY_F9,
        F10 = GLFW_KEY_F10,
        F11 = GLFW_KEY_F11,
        F12 = GLFW_KEY_F12,

        ESCAPE = GLFW_KEY_ESCAPE,
        TAB = GLFW_KEY_TAB,
        CAPS_LOCK = GLFW_KEY_CAPS_LOCK,
        LEFT_SHIFT = GLFW_KEY_LEFT_SHIFT,
        RIGHT_SHIFT = GLFW_KEY_RIGHT_SHIFT,
        LEFT_CONTROL = GLFW_KEY_LEFT_CONTROL,
        RIGHT_CONTROL = GLFW_KEY_RIGHT_CONTROL,
        LEFT_ALT = GLFW_KEY_LEFT_ALT,
        RIGHT_ALT = GLFW_KEY_RIGHT_ALT,
        SPACE = GLFW_KEY_SPACE,
        ENTER = GLFW_KEY_ENTER,
        BACKSPACE = GLFW_KEY_BACKSPACE,

        SCROLL_LOCK = GLFW_KEY_SCROLL_LOCK,
        PAUSE = GLFW_KEY_PAUSE,
        PRINT_SCREEN = GLFW_KEY_PRINT_SCREEN,

        INSERT = GLFW_KEY_INSERT,
        DELETE = GLFW_KEY_DELETE,
        HOME = GLFW_KEY_HOME,
        END = GLFW_KEY_END,
        PAGE_UP = GLFW_KEY_PAGE_UP,
        PAGE_DOWN = GLFW_KEY_PAGE_DOWN,

        UP = GLFW_KEY_UP,
        DOWN = GLFW_KEY_DOWN,
        LEFT = GLFW_KEY_LEFT,
        RIGHT = GLFW_KEY_RIGHT,

        NUM_LOCK = GLFW_KEY_NUM_LOCK,
        NUMPAD_0 = GLFW_KEY_KP_0,
        NUMPAD_1 = GLFW_KEY_KP_1,
        NUMPAD_2 = GLFW_KEY_KP_2,
        NUMPAD_3 = GLFW_KEY_KP_3,
        NUMPAD_4 = GLFW_KEY_KP_4,
        NUMPAD_5 = GLFW_KEY_KP_5,
        NUMPAD_6 = GLFW_KEY_KP_6,
        NUMPAD_7 = GLFW_KEY_KP_7,
        NUMPAD_8 = GLFW_KEY_KP_8,
        NUMPAD_9 = GLFW_KEY_KP_9,
        NUMPAD_ADD = GLFW_KEY_KP_ADD,
        NUMPAD_SUBTRACT = GLFW_KEY_KP_SUBTRACT,
        NUMPAD_MULTIPLY = GLFW_KEY_KP_MULTIPLY,
        NUMPAD_DIVIDE = GLFW_KEY_KP_DIVIDE,
        NUMPAD_ENTER = GLFW_KEY_KP_ENTER,
        NUMPAD_DECIMAL = GLFW_KEY_KP_DECIMAL,

        LAST = GLFW_KEY_LAST

    };
    enum class MouseButton
    {
        ANY = -1,
        LEFT = GLFW_MOUSE_BUTTON_LEFT,
        RIGHT = GLFW_MOUSE_BUTTON_RIGHT,
        MIDDLE = GLFW_MOUSE_BUTTON_MIDDLE,
        BUTTON_4 = GLFW_MOUSE_BUTTON_4,
        BUTTON_5 = GLFW_MOUSE_BUTTON_5,
        BUTTON_6 = GLFW_MOUSE_BUTTON_6,
        BUTTON_7 = GLFW_MOUSE_BUTTON_7,
        BUTTON_8 = GLFW_MOUSE_BUTTON_8,
        LAST = GLFW_MOUSE_BUTTON_LAST
    };
    class DLL Window
    {
    private:
        GLFWwindow *glfw_window;

        int currentFPS = 0;
        int targetFPS = 60;

        int currentTPS = 0;
        int targetTPS = 60;


        int (*fixedUpdateFunction)(int, Window &) = nullptr;
        int (*updateFunction)(int, Window &) = nullptr;
        int (*startFunction)(Window &) = nullptr;
        int (*setupFunction)() = nullptr;

        void (*renderFunction)() = nullptr;
        Input *input;

        double _deltaTime = 0;

        int result = 0;
    public:

        utils::Color backgroundColor;

        Window(int width, int height, std::string title);
        ~Window();

        ///@param updateFunction: function that is called every
        /// frame and returns -1 if the window should close,
        /// also takes the current frame number as a parameter
        /// called every frame
        void setFixedUpdateFunction(int (*FixedUpdateFunction)(int, Window &));

        /// called every frame but as new thread 
        void setUpdateFunction(int (*updateFunction)(int, Window &));
        void setStartFunction(int (*startFunction)(Window &));
        void setSetupFunction(int (*setupFunction)());

        void doSetup();
        void doStart();

        //the function that runs throught every Object and renders it(by default).
        void setRenderFunction(void (*renderFunction)() = nullptr);

        void start();

        int getCurrentFPS();
        void setTargetFPS(int targetFPS);

        int getCurrentTPS();
        void setTargetTPS(int targetTPS);

        GLFWwindow *getWindow();

        double deltaTime();



        class DLL Log
        {
        private:
            Window *window;
        public:
            Log(Window &window);

            bool logFPS = false;
            bool logTPS = false;
            bool logMainThreadTime = false;
        };
        Log log{*this};
        class DLL Parameters
        {
        private:
            Window *window;
            utils::Size size;
        public:
            Parameters(Window &window);

            utils::Position getPosition();
            void setPosition(utils::Position position);

            utils::Size getSize();
            void setSize(utils::Size size);
        };

        Parameters parameters{*this};
        class DLL Properties
        {
        private:
            Window *window;
            GLFWmonitor *primary_monitor;

        public:


            Properties(Window &window);

            GLFWmonitor *getPrimaryMonitor();
            void setPrimaryMonitor(GLFWmonitor *monitor);

            bool isFullscreen();
            void setFullscreen(bool fullscreen);
            void toggleFullscreen();

            bool isResizable();
            void setResizable(bool resizable);

            bool isDecorated();
            void setDecorated(bool decorated);

            bool isMaximized();
            void setMaximized(bool maximized);

            bool isMinimized();
            void setMinimized(bool minimized);

            bool isFocused();
            void setFocused(bool focused);

            bool isHovered();
            void setHovered(bool hovered);

            bool isVisible();
            void setVisible(bool visible);

            bool isAlwaysOnTop();
            void setAlwaysOnTop(bool alwaysOnTop);

            bool isFocusOnShow();
            void setFocusOnShow(bool focusOnShow);
        };
        Properties properties{*this};
        class DLL Events
        {
        private:
            Window *window;
        public:
            Events(Window &window);

            bool getKey(Keycode keycode);
            bool getKey(char chr);
            bool getKeyPressed(Keycode keycode);
            bool getKeyPressed(char chr);
            bool getKeyDown(Keycode keycode);
            bool getDown(char chr);
            bool getKeyReleased(Keycode keycode);
            bool getKeyReleased(char chr);
            bool getKeyUp(Keycode keycode);
            bool getKeyUp(char chr);

            bool getMouseButton(MouseButton button);
            bool getMouseButtonReleased(MouseButton button);
            bool getMouseButtonDown(MouseButton button);
        };
        Events events{*this};

        class DLL Keys
        {
        private:
            Window *window;
        public:
            bool delay = true;
            Keys(Window &window);
        };
        Keys keys{*this};
    };
    namespace window
    {
        //creates a window and starts it in a new thread
        DLL Window* create(int width, int height, std::string title);
        DLL void defaultResizeCallback(GLFWwindow *window, int width, int height);
    }
}