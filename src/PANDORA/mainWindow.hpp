#include "DLL/dll.hpp"

#include "IO/window.hpp"

namespace pandora
{
    namespace mainWindow
    {
        DLL void set(io::Window *window);
        DLL io::Window *get();
    } // namespace mainWindow
} // namespace pandora