#pragma once
#include <string>

#include "DLL/dll.hpp"

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


/**
 * @brief Logs an informational message.
 * 
 * @param str The message to be logged.
 * @param ... Additional arguments for formatting the message (optional).
 */
DLL void logInfo(std::string str, ...);

/**
 * @brief Logs a warning message.
 * 
 * @param str The warning message to be logged.
 * @param ... Additional arguments for formatting the message (optional).
 */
DLL void logWarning(std::string str, ...);

/**
 * @brief Logs an error message.
 * 
 * @param str The error message to be logged.
 * @param ... Additional arguments for formatting the error message (optional).
 */
DLL void logError(std::string str, ...);

/**
 * @brief Logs a success message.
 * 
 * @param str The success message to be logged.
 * @param ... Additional arguments for formatting the message (optional).
 */
void logSuccess(std::string str, ...);