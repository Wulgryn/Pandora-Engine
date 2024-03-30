#pragma once
namespace DebugConsole
{
    enum ConsoleClockPrecision
    {
        SECONDS,
        MILLISECONDS,
        MICROSECONDS,
        NANOSECOND
    };
    extern bool EnableTimePrefix;
    extern ConsoleClockPrecision consoleClockPrecision;
    void WriteTime();

    void WriteLine(const char *message, ...);
    void Write(const char *message, ...);
}