#pragma once
#include <string>
#include <vector>
#include <iostream>

#include <complex.h>

#include "UTILS/bool.hpp"
#include "DLL/dll.hpp"

/**
* @brief Contains functions for file input/output operations.
*/
namespace io
{

    /**
     * @brief Namespace containing functions for file manipulation.
     */
    namespace files
    {
            /**
             * @brief Creates a file at the specified path.
             *
             * @param path The path of the file to create.
             * @param overwrite Flag indicating whether to overwrite the file if it already exists. Default is false.
             */
            DLL void create(std::string path, utils::Bool::Bool overwrite = false);

            /**
             * @brief Creates a file at the specified path with the given content.
             *
             * @param path The path of the file to create.
             * @param content The content to write to the file.
             * @param overwrite Flag indicating whether to overwrite the file if it already exists. Default is false.
             */
            DLL void create(std::string path, std::string content, utils::Bool::Bool overwrite = false);

            /**
             * @brief Creates a file at the specified path with the given lines.
             *
             * @param path The path of the file to create.
             * @param lines The lines to write to the file.
             * @param overwrite Flag indicating whether to overwrite the file if it already exists. Default is false.
             */
            DLL void create(std::string path, std::vector<std::string> lines, utils::Bool::Bool overwrite = false);
            /**
             * @brief Removes the file at the specified path.
             *
             * @param path The path of the file to remove.
             */
            DLL void remove(std::string path);

            /**
             * @brief Reads the contents of a file into a string.
             *
             * @param path The path to the file.
             * @return The contents of the file as a string.
             */
            DLL std::string read(std::string path);

            /**
             * @brief Reads the lines from a file specified by the given path.
             *
             * @param path The path of the file to read.
             * @return A vector of strings containing the lines read from the file.
             */
            DLL std::vector<std::string> readLines(std::string path);

            /**
             * @brief Writes a string to an existing file.
             *
             * @param path The path to the file.
             * @param content The string to write.
             */
            DLL void write(std::string path, std::string content);

            /**
             * @brief Writes a vector of strings as lines to an existing file.
             *
             * @param path The path to the file.
             * @param lines The vector of strings to write as lines.
             */
            DLL void writeLines(std::string path, std::vector<std::string> lines);

            /**
             * @brief Calculates and returns the length of a file specified by the given path.
             *
             * @param path The path of the file.
             * @return The length of the file in bytes.
             */
            DLL long getLength(std::string path);

            /**
             * @brief Renames a file specified by the given path.
             *
             * @param path The path of the file to rename.
             * @param newName The new name of the file.
             * @param overwrite Flag indicating whether to overwrite the file if it already exists. Default is false.
             */
            DLL void rename(std::string path, std::string newName, utils::Bool::Bool overwrite = false);

            /**
             * @brief Copies a file specified by the given path to a new location.
             *
             * @param path The path of the file to copy.
             * @param newPath The path of the new location.
             * @param overwrite Flag indicating whether to overwrite the file if it already exists. Default is false.
             */
            DLL void copy(std::string path, std::string newPath, utils::Bool::Bool overwrite = false);

            /**
             * @brief Moves a file specified by the given path to a new location.
             *
             * @param path The path of the file to move.
             * @param newPath The path of the new location.
             * @param overwrite Flag indicating whether to overwrite the file if it already exists. Default is false.
             */
            DLL void move(std::string path, std::string newPath, utils::Bool::Bool overwrite = false);
        }
}