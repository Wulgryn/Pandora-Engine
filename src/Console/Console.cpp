#include "Console.hpp"

#include "IO/Logger.hpp"

#include <cstdarg>

#include <iostream>
#include <chrono>
using namespace std;
using namespace std::chrono;

namespace PandoraEngine
{
    bool Console::EnableTimePrefix = true;
    bool Console::EnableLogging = false;

    void Console::WriteTime()
    {
        auto now = system_clock::now();
        auto time = system_clock::to_time_t(now);
        auto duration = now.time_since_epoch();

        tm *tm = localtime(&time);
        char buffer[80];
        strftime(buffer, sizeof(buffer), "[%m.%d|%H:%M:%S]", tm);

        cout << buffer;
    }

    void Console::WriteLine(std::string message, ...)
    {
        if (EnableTimePrefix)
        {
            WriteTime();
        }

        va_list args;
        va_start(args, message);

        if (EnableLogging) Logger::WriteLine(message + "\n", args);

        vprintf(message.c_str(), args);
        printf("\n");

        va_end(args);
    }

    void Console::Write(std::string message, ...)
    {
        va_list args;
        va_start(args, message);

        if (EnableLogging) Logger::Write(message, args);

        vprintf(message.c_str(), args);

        va_end(args);
    }
} // namespace PandoraEngine
