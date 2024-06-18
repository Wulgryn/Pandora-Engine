#ifndef IWINDOW_HPP
#define IWINDOW_HPP

#include "../../../Core/Macros.h"

class GLFWwindow;

namespace PandoraEngine
{
    namespace Windows
    {
        namespace WindowInterface
        {
            class DLL IWindow
            {
            protected:
                IWindow() = default;

            public:
                virtual ~IWindow() = default;

                virtual void initialize() = 0;

                /**
                 * @brief Set the floating object
                 *
                 * @param floating
                 *
                 */
                virtual void set_floating(bool) = 0;
                virtual bool is_floating() = 0;

                virtual void SetMonitor(int) = 0;
                /**
                 * @brief Set the Context Version object
                 *
                 * @param major
                 * @param minor
                 *
                 */
                virtual void SetContextVersion(int, int) = 0;
                /**
                 * @brief Set the Context Profile object
                 *
                 * @param profile
                 *
                 */
                virtual void SetContextProfile(int) = 0;
                /**
                 * @brief Set the Context Robustness object
                 *
                 * @param robustness
                 *
                 */
                virtual void SetContextRobustness(int) = 0;

                virtual GLFWwindow &get_window() = 0;
            }; // class IWindow
        } // namespace WindowInterface
    } // namespace Windows

} // namespace PandoraEngine

#endif // IWINDOW_HPP