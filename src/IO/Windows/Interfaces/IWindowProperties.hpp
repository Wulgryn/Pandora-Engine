#ifndef IWINDOWPROPERTIES_HPP
#define IWINDOWPROPERTIES_HPP

#include "../../../Core/Macros.h"
#include "../../../Core/Units.hpp"
#include <string>

namespace PandoraEngine
{
    namespace Windows
    {
        namespace WindowInterface
    {
        class DLL IWindowProperties
        {
        protected:
            IWindowProperties() = default;

        public:
            /**
             * @brief Set the title object
             *
             * @param title
             *
             */
            virtual void set_title(std::string) = 0;
            virtual std::string get_title() = 0;

            /**
             * @brief Set the size object
             *
             * @param width
             * @param height
             *
             */
            virtual void set_size(int, int) = 0;
            /**
             * @brief Set the size object
             *
             * @param size
             */
            virtual void set_size(Units::RectSize) = 0;
            virtual Units::RectSize get_size() = 0;

            /**
             * @brief Set the position object
             *
             * @param x
             * @param y
             *
             */
            virtual void set_position(int, int) = 0;
            /**
             * @brief Set the position object
             *
             * @param position
             *
             */
            virtual void set_position(Units::RectPoint) = 0;
            virtual Units::RectPoint get_position() = 0;

            /**
             * @brief Set the resizable object
             *
             * @param resizable
             *
             */
            virtual void set_resizable(bool) = 0;
            virtual bool is_resizable() = 0;

            /**
             * @brief Set the decorated object
             *
             * @param decorated
             *
             */
            virtual void set_decorated(bool) = 0;
            virtual bool is_decorated() = 0;

            /**
             * @brief Set the min size object
             *
             * @param width
             * @param height
             */
            virtual void set_min_size(int, int) = 0;
            /**
             * @brief Set the min size object
             *
             * @param minSize
             */
            virtual void set_min_size(Units::RectSize) = 0;
            virtual Units::RectSize get_min_size() = 0;

            /**
             * @brief Set the max size object
             *
             * @param width
             * @param height
             */
            virtual void set_max_size(int, int) = 0;
            /**
             * @brief Set the max size object
             *
             * @param maxSize
             */
            virtual void set_max_size(Units::RectSize) = 0;
            virtual Units::RectSize get_max_size() = 0;

            /**
             * @brief Set the icon object
             *
             * @param iconPath
             */
            virtual void set_icon(std::string) = 0;
            virtual std::string get_icon() = 0;

            /**
             * @brief Set the cursor object
             *
             * @param cursorPath
             */
            virtual void set_cursor(std::string) = 0;
            virtual std::string get_cursor() = 0;

            /**
             * @brief Set the cursor mode object
             *
             * @param cursorMode
             */
            virtual void set_cursor_mode(int) = 0;
            virtual int get_cursor_mode() = 0;

            /**
             * @brief Set the cursor position object
             *
             * @param x
             * @param y
             */
            virtual void set_cursor_position(int, int) = 0;
            /**
             * @brief Set the cursor position object
             *
             * @param position
             */
            virtual void set_cursor_position(Units::RectPoint) = 0;
            virtual Units::RectPoint get_cursor_position() = 0;

            /**
             * @brief Set the opacity object
             *
             * @param opacity
             */
            virtual void set_opacity(float) = 0;
            virtual float get_opacity() = 0;
        }; // class IWindowProperties
    } // namespace WindowInterface
    } // namespace Windows
    

} // namespace PandoraEngine

#endif // IWINDOWPROPERTIES_HPP