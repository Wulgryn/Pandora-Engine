#ifndef CONSOLE_HPP
#define CONSOLE_HPP

#include "Core/Macros.h"

#include <string>
#include <iostream>

#ifdef PE_DEBUG
#include <cstdarg>
#define PE_DEBUG_CONSOLE
#endif

namespace PandoraEngine
{
    namespace Console
    {
        extern DLL bool EnableTimePrefix;

        // Enable or disable logging to file.
        // Default is false.
        extern DLL bool EnableLogging;

        DLL void WriteTime();

        DLL void WriteLine(std::string message, ...);

        DLL void Write(std::string message, ...);

        namespace DebugConsole
        {
            enum class ConsoleClockPrecision
            {
                SECONDS,
                MILLISECONDS,
                MICROSECONDS,
                NANOSECOND
            };

            extern DLL bool EnableTimePrefix;
            extern DLL ConsoleClockPrecision ClockPrecision;

            DLL void WriteTime();

            DLL void WriteLine(std::string message, ...);

            DLL void Write(std::string message, ...);

        }; // namespace DebugConsole
    } // namespace Console

} // namespace PandoraEngine

#endif // CONSOLE_HPP