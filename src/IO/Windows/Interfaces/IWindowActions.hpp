#ifndef IWINDOWACTIONS_HPP
#define IWINDOWACTIONS_HPP

#include "../../../Core/Macros.h"

namespace PandoraEngine
{
    namespace Windows
    {
        namespace WindowInterface
        {
            class DLL IWindowActions
            {
            protected:
                IWindowActions() = default;

            public:
                virtual void show() = 0;
                virtual void hide() = 0;
                virtual void hide_cursor() = 0;
                virtual void show_cursor() = 0;

                /**
                 * @brief Set the fullscreen object
                 *
                 * @param fullscreen
                 */
                virtual void set_fullscreen(bool) = 0;

                /**
                 * @brief Set the vsync object
                 *
                 * @param vsync
                 */
                virtual void set_vsync(bool) = 0;
                virtual void minimize() = 0;
                virtual void maximize() = 0;
                virtual void focus() = 0;
                virtual void unfocus() = 0;

                /**
                 * @brief Set the always on top object
                 *
                 * @param alwaysOnTop
                 */
                virtual void set_always_on_top(bool) = 0;
                virtual void destroy() = 0;
            }; // class IWindowActions
        } // namespace WindowInterfaces
    } // namespace Windows

} // namespace PandoraEngine

#endif // IWINDOWACTIONS_HPP