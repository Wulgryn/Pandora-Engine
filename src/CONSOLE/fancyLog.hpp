#pragma once
#include <string>

enum ConsoleClockPrecision {
    SECONDS,
    MILLISECONDS,
    MICROSECONDS,
    NANOSECOND
};
/// @brief The precision of the clock displayed in the console
extern ConsoleClockPrecision consoleClockPrecision;

/// @brief Prints out a text format: (in blue) [ (time) ][INFO]> your text
///
/// @param str The text to be logged
/// @param ... Additional arguments for formatting the log message
void logInfo(std::string str, ...);

/// @brief Prints out a text format: (in yellow) [ (time) ][WARNING]> your text
///
/// @param str The text to be logged
/// @param ... Additional arguments for formatting the log message
void logWarning(std::string str, ...);

/// @brief Prints out a text format: (all text in red) [ (time) ][ERROR]> your text
///
/// @param str The text to be logged
/// @param ... Additional arguments for formatting the log message
void logError(std::string str, ...);

/// @brief Prints out a text format: (all text in green) [ (time) ][SUCCESS]> your text
///
/// @param str The text to be logged
/// @param ... Additional arguments for formatting the log message
void logSuccess(std::string str, ...);