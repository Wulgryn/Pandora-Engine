#include "Console.hpp"

#include <iostream>
#include <chrono>
#include <cstdarg>
#include <stdarg.h>
#include <iomanip>

using namespace std;
using namespace std::chrono;

bool DebugConsole::EnableTimePrefix = true;
DebugConsole::ConsoleClockPrecision DebugConsole::consoleClockPrecision = DebugConsole::ConsoleClockPrecision::MILLISECONDS;

void DebugConsole::WriteTime()
{
    auto now = system_clock::now();
    auto time = system_clock::to_time_t(now);
    auto duration = now.time_since_epoch();

    tm *tm = localtime(&time);
    char buffer[80];
    strftime(buffer, sizeof(buffer), "[%m.%d|%H:%M:%S", tm);

    switch (consoleClockPrecision)
    {
    case SECONDS:
        cout << buffer << "]";
        break;
    case MILLISECONDS:
        cout << buffer << "s." << std::setw(3) << std::setfill('0') << duration_cast<milliseconds>(duration).count() % 1000 << "ms]";
        break;
    case MICROSECONDS:
        cout << buffer << "s." << std::setw(3) << std::setfill('0') << duration_cast<milliseconds>(duration).count() % 1000 << "ms.";
        cout << std::setw(3) << std::setfill('0') << duration_cast<microseconds>(duration).count() % 1000 << "us]";
        break;
    case NANOSECOND:
        cout << buffer << "s." << std::setw(3) << std::setfill('0') << duration_cast<milliseconds>(duration).count() % 1000 << "ms.";
        cout << std::setw(3) << std::setfill('0') << duration_cast<microseconds>(duration).count() % 1000 << "us.";
        cout << std::setw(3) << std::setfill('0') << duration_cast<nanoseconds>(duration).count() % 1000 << "ns]";
        break;
    }
}

void DebugConsole::WriteLine(const char* message, ...)
{
    if(DebugConsole::EnableTimePrefix) WriteTime();
    string formattedMessage = (string)message + "\n";
    va_list args;
    va_start(args, message);
    vprintf(formattedMessage.c_str(), args);
    va_end(args);
    //cout << endl;
}

void DebugConsole::Write(const char* message, ...)
{
    va_list args;
    va_start(args, message);
    vprintf(message, args);
    va_end(args);
}