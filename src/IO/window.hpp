#include "DLL/dll.hpp"
#define GLFW_INCLUDE_NONE
#include "GLFW/glfw3.h"

#include <string>

#include "UTILS/parameters.hpp"

namespace io
{
    class DLL Window
    {
    private:
        GLFWwindow *glfw_window;

        int currentFPS = 0;
        int targetFPS = 60;

        int currentTPS = 0;
        int targetTPS = 60;


        int (*updateFunction)(int, Window &);
        int (*startFunction)(Window &);
        int (*setupFunction)();

    public:
        Window(int width, int height, std::string title);
        ~Window();

        ///@param updateFunction: function that is called every
        /// frame and returns -1 if the window should close,
        /// also takes the current frame number as a parameter
        void setUpdateFunction(int (*updateFunction)(int, Window &));
        void setStartFunction(int (*startFunction)(Window &));
        void setSetupFunction(int (*setupFunction)());

        void start();

        int getCurrentFPS();
        void setTargetFPS(int targetFPS);

        int getCurrentTPS();
        void setTargetTPS(int targetTPS);

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
            utils::_2D_::Size size;
        public:
            Parameters(Window &window);

            utils::_2D_::Location getLocation();
            void setLocation(utils::_2D_::Location location);

            utils::_2D_::Size getSize();
            void setSize(utils::_2D_::Size size);
        };

        Parameters parameters{*this};
        class DLL Properties
        {
        private:
            Window *window;
            GLFWmonitor *primary_monitor;

        public:
            bool waitForUpdate = false;


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
        };
    };
    namespace window
    {
        DLL Window create(int width, int height, std::string title);
    }
}