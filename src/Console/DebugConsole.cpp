#include "Console.hpp"

#include "IO/Logger.hpp"

#include <cstdarg>
#include <chrono>
#include <stdarg.h>
#include <iomanip>
#include <iostream>

using namespace std;
using namespace std::chrono;

bool PandoraEngine::DebugConsole::EnableTimePrefix = true;
PandoraEngine::DebugConsole::ConsoleClockPrecision PandoraEngine::DebugConsole::ClockPrecision = PandoraEngine::DebugConsole::ConsoleClockPrecision::MILLISECONDS;

void PandoraEngine::DebugConsole::WriteTime()
{
    auto now = system_clock::now();
    auto time = system_clock::to_time_t(now);
    auto duration = now.time_since_epoch();

    tm *tm = localtime(&time);
    char buffer[80];
    strftime(buffer, sizeof(buffer), "[%m.%d|%H:%M:%S", tm);

    switch (ClockPrecision)
    {
    case ConsoleClockPrecision::SECONDS:
        cout << buffer << "]";
        break;
    case ConsoleClockPrecision::MILLISECONDS:
        cout << buffer << "s." << std::setw(3) << std::setfill('0') << duration_cast<milliseconds>(duration).count() % 1000 << "ms]";
        break;
    case ConsoleClockPrecision::MICROSECONDS:
        cout << buffer << "s." << std::setw(3) << std::setfill('0') << duration_cast<milliseconds>(duration).count() % 1000 << "ms.";
        cout << std::setw(3) << std::setfill('0') << duration_cast<microseconds>(duration).count() % 1000 << "us]";
        break;
    case ConsoleClockPrecision::NANOSECOND:
        cout << buffer << "s." << std::setw(3) << std::setfill('0') << duration_cast<milliseconds>(duration).count() % 1000 << "ms.";
        cout << std::setw(3) << std::setfill('0') << duration_cast<microseconds>(duration).count() % 1000 << "us.";
        cout << std::setw(3) << std::setfill('0') << duration_cast<nanoseconds>(duration).count() % 1000 << "ns]";
        break;
    }
}

void PandoraEngine::DebugConsole::WriteLine(std::string message, ...)
{
    va_list args;
    va_start(args, message);

    if (EnableTimePrefix)
    {
        WriteTime();
    }

    vprintf(message.c_str(), args);
    printf("\n");

    va_end(args);

    Logger::WriteLine(message + "\n", args);
}

void PandoraEngine::DebugConsole::Write(std::string message, ...)
{
    va_list args;
    va_start(args, message);
    vprintf(message.c_str(), args);
    va_end(args);

    Logger::Write(message, args);
}