#ifndef BASEWINDOW_HPP
#define BASEWINDOW_HPP

#include "../../Core/Macros.h"
#include "Interfaces/IWindow.hpp"
#include "Interfaces/IWindowActions.hpp"
#include "Interfaces/IWindowProperties.hpp"

namespace PandoraEngine
{
    namespace Windows
    {
        class DLL BaseWindow : public WindowInterface::IWindow, public WindowInterface::IWindowActions, public WindowInterface::IWindowProperties
        {
        private:
            GLFWwindow *_GLFWwindow;
            int _windowID;
            int _handlerIndex;
            std::string _title;
            bool _isCreated = false;

            void set_gl_glfw_settigs();
        public:
            BaseWindow(std::string title = "");

            void initialize() override;

        }; // class BaseWindow
    } // namespace Windows

} // namespace PandoraEngine

#endif // BASEWINDOW_HPP