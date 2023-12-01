#include "DLL/dll.hpp"
#define GLFW_INCLUDE_NONE
#include "GLFW/glfw3.h"

#include <string>

namespace io {
    class DLL Window
    {
    private:
        GLFWwindow* glfw_window;
    public:
        Window(int width, int height, std::string title);
        ~Window();
        
        ///@param updateFunction: function that is called every 
        ///frame and returns -1 if the window should close,
        /// also takes the current frame number as a parameter
        void setUpdateFunction(int (*updateFunction)(int));
    };
    namespace window
    {
        DLL Window create(int width, int height, std::string title);
    }
}