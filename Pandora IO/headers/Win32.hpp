#pragma once
namespace Windows
{
    class Win32
    {
        public:
        /**
         * 
         * The *ClsExtra* specifies the number of extra bytes to allocate following the window class structure.
         *
         * This extra space is typically used to store additional data associated with the window class, such as a pointer to an object or a data structure that holds information related to the class.
         * 
         * Here's an example of defining a ClsExtra value of 4:
         * ```cpp
         * #include "Pandora IO.hpp"
         * Win32 window;
         * window.ClsExtra = 4;
         * window.Create();
         * ```
        */
        int ClsExtra = 0;

        /**
         * The *WndExtra* specifies the number of extra bytes to allocate following the window instance.
         *
         * This extra space is typically used to store additional data associated with the window instance, such as a pointer to an object or a data structure that holds information related to the specific window. The value of *WndExtra* can be set to 0 if no extra data needs to be stored.
         *
         * Here's an example of defining a *WndExtra* value of 8:
         * ```cpp
         * #include "Pandora IO.hpp"
         * Win32 window;
         * window.WndExtra = 8;
         * window.Create();
         * ```
        */
        int WndExtra = 0;

        /**
         * 
        */
        
    };
};