#include "fancyLog.hpp"

#include <chrono>
#include <iostream>
#include <cstdarg>
#include <string>
#include <string.h>
#include <windows.h>
#include <vector>

#include "UTILS/string.hpp"
using namespace utils;

using namespace std;
using namespace chrono;

ConsoleClockPrecision consoleClockPrecision = SECONDS;
bool consoleLogEnabled = true;

static const char *formatColoredText(const char *str)
{
    string str_ = str;
    strings::replace(str_, "§BLACK", "\033[0;30m");
    strings::replace(str_, "§RED", "\033[0;31m");
    strings::replace(str_, "§GREEN", "\033[0;32m");
    strings::replace(str_, "§YELLOW", "\033[0;33m");
    strings::replace(str_, "§BLUE", "\033[0;34m");
    strings::replace(str_, "§MAGENTA", "\033[0;35m");
    strings::replace(str_, "§CYAN", "\033[0;36m");
    strings::replace(str_, "§WHITE", "\033[0;37m");
    strings::replace(str_, "§DEFAULT", "\033[0m");
    strcpy((char *)str, str_.c_str());
    return str;
}

static void PrintTime()
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
        cout << buffer << "s." << duration_cast<milliseconds>(duration).count() % 1000 << "ms]";
        break;
    case MICROSECONDS:
        cout << buffer << "s." << duration_cast<milliseconds>(duration).count() % 1000 << "ms.";
        cout << duration_cast<microseconds>(duration).count() % 1000 << "us]";
        break;
    case NANOSECOND:
        cout << buffer << "s." << duration_cast<milliseconds>(duration).count() % 1000 << "ms.";
        cout << duration_cast<microseconds>(duration).count() % 1000 << "us.";
        cout << duration_cast<nanoseconds>(duration).count() % 1000 << "ns]";
        break;
    }
}

void logInfo(string str, ...)
{
    if(!consoleLogEnabled) return;
    cout << "\033[0m";

    PrintTime();

    cout << "\033[0;34m[INFO]> \033[0m";

    va_list args;
    va_start(args, str);

    char *buffer = (char *)malloc(str.size() + 1);
    vsnprintf(buffer, str.size() + 1, str.c_str(), args);

    va_end(args);

    cout << formatColoredText(buffer) << "\033[0m" << endl;
}

void logWarning(string str, ...)
{
    if(!consoleLogEnabled) return;
    cout << "\033[0m";

    PrintTime();

    cout << "\033[1;33m[WARNING]> \033[0m";

    va_list args;
    va_start(args, str);

    char *buffer = (char *)malloc(str.size() + 1);
    vsnprintf(buffer, str.size() + 1, str.c_str(), args);

    va_end(args);

    cout << formatColoredText(buffer) << "\033[0m" << endl;
}

void logError(string str, ...)
{
    if(!consoleLogEnabled) return;
    cout << "\033[1;31m";

    PrintTime();

    cout << "[ERROR]> ";

    va_list args;
    va_start(args, str);

    char *buffer = (char *)malloc(str.size() + 1);
    vsnprintf(buffer, str.size() + 1, str.c_str(), args);

    va_end(args);

    cout << formatColoredText(buffer) << "\033[0m" << endl;
}

void logSuccess(string str, ...)
{
    if(!consoleLogEnabled) return;
    cout << "\033[0;32m";

    PrintTime();

    cout << "[SUCCESS]> ";

    va_list args;
    va_start(args, str);

    char *buffer = (char *)malloc(str.size() + 1);
    vsnprintf(buffer, str.size() + 1, str.c_str(), args);

    va_end(args);

    cout << formatColoredText(buffer) << "\033[0m" << endl;
}