#pragma once
#include <string>

#include "ESSENTIALS/dll.hpp"

enum ConsoleClockPrecision {
    SECONDS,
    MILLISECONDS,
    MICROSECONDS,
    NANOSECOND
};
/// @brief The precision of the clock displayed in the console
extern ConsoleClockPrecision consoleClockPrecision;


/**
 * @brief Indicates whether console logging is enabled or not.
 * @note By default, console logging is enabled.
 */
extern bool consoleLogEnabled; 

/// @brief Prints out a text format: (in blue) [ (time) ][INFO]> your text
///
/// @param str The text to be logged
/// @param ... Additional arguments for formatting the log message
DLL void logInfo(std::string str, ...);

/// @brief Prints out a text format: (in yellow) [ (time) ][WARNING]> your text
///
/// @param str The text to be logged
/// @param ... Additional arguments for formatting the log message
DLL void logWarning(std::string str, ...);

/// @brief Prints out a text format: (all text in red) [ (time) ][ERROR]> your text
///
/// @param str The text to be logged
/// @param ... Additional arguments for formatting the log message
DLL void logError(std::string str, ...);

/// @brief Prints out a text format: (all text in green) [ (time) ][SUCCESS]> your text
///
/// @param str The text to be logged
/// @param ... Additional arguments for formatting the log message
DLL void logSuccess(std::string str, ...);