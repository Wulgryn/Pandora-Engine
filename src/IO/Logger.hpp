#ifndef LOGGER_HPP
#define LOGGER_HPP

#include "../Core/Macros.h"
#include <string>

namespace PandoraEngine
{
    namespace Logger
    {
        DLL void Initialize(const char *root_dir = "");

        DLL void WriteLine(std::string format, va_list args);
        DLL void WriteLine(std::string format, ...);

        DLL void Write(std::string format, va_list args);
        DLL void Write(std::string format, ...);
    } // namespace Logger
    
} // namespace PandoraEngine


#endif // LOGGER_HPP