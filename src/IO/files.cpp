#include "files.hpp"

#include <fstream>

#include "CONSOLE/fancyLog.hpp"

using namespace io;
using namespace utils;
using namespace std;

void files::create(string path, Bool::Bool overwrite)
{
    try
    {
        ifstream existingFile(path.c_str());
        if (existingFile && !overwrite)
        {
            existingFile.close();
            logWarning("File already exists: " + path);
            return;
        }

        ofstream file(path.c_str());
        if (file.is_open())
        {
            file.close();
            logSuccess("File created: " + path);
        }
        else
        {
            logError("Failed to create file: " + path);
        }
    }
    catch (const exception &e)
    {
        logError("Exception occurred while creating file: " + path + ", " + e.what());
    }
}

void files::create(string path, string content, Bool::Bool overwrite)
{
    try
    {
        ifstream existingFile(path.c_str());
        if (existingFile && !overwrite)
        {
            existingFile.close();
            logWarning("File already exists: " + path);
            return;
        }

        ofstream file(path.c_str());
        if (file.is_open())
        {
            file << content;
            file.close();
            logSuccess("File with content created: " + path);
        }
        else
        {
            logError("Failed to create file: " + path);
        }
    }
    catch (const exception &e)
    {
        logError("Exception occurred while creating file: " + path + ", " + e.what());
    }
}

void files::create(string path, vector<string> lines, Bool::Bool overwrite)
{
    try
    {
        ifstream existingFile(path.c_str());
        if (existingFile && !overwrite)
        {
            existingFile.close();
            logWarning("File already exists: " + path);
            return;
        }

        ofstream file(path.c_str());
        if (file.is_open())
        {
            for (string line : lines)
            {
                file << line << endl;
            }
            file.close();
            logSuccess("File with lines created: " + path);
        }
        else
        {
            logError("Failed to create file: " + path);
        }
    }
    catch (const exception &e)
    {
        logError("Exception occurred while creating file: " + path + ", " + e.what());
    }
}

void files::remove(string path)
{
    try
    {
        ifstream existingFile(path.c_str());
        if (!existingFile)
        {
            existingFile.close();
            logWarning("File does not exist: " + path);
            return;
        }
        existingFile.close();
        if (std::remove(path.c_str()) != 0)
        {
            logError("Failed to remove file: " + path);
            return;
        }

        logInfo("File removed: " + path);
    }
    catch (const exception &e)
    {
        logError("Exception occurred while removing file: " + path + ", " + e.what());
    }
}

string files::read(string path)
{
    try
    {
        ifstream file(path.c_str());
        if (!file)
        {
            logError("File does not exist: " + path);
            return "";
        }
        if (file.is_open())
        {
            string content((istreambuf_iterator<char>(file)), (istreambuf_iterator<char>()));
            file.close();
            logInfo("File read: " + path);
            return content;
        }
        else
        {
            logError("Failed to read file: " + path);
            return "";
        }
    }
    catch (const exception &e)
    {
        logError("Exception occurred while reading file: " + path + ", " + e.what());
        return "";
    }
}

vector<string> files::readLines(string path)
{
    try
    {
        ifstream file(path.c_str());
        if(!file)
        {
            logError("File does not exist: " + path);
            return vector<string>();
        }
        if (file.is_open())
        {
            vector<string> lines;
            string line;
            while (getline(file, line))
            {
                lines.push_back(line);
            }
            file.close();
            logInfo("File read: " + path);
            return lines;
        }
        else
        {
            logError("Failed to read file: " + path);
            return vector<string>();
        }
    }
    catch (const exception &e)
    {
        logError("Exception occurred while reading file: " + path + ", " + e.what());
        return vector<string>();
    }
}

void files::write(string path, string content)
{
    try
    {
        ofstream file(path.c_str());
        if(!file)
        {
            logError("File does not exist: " + path);
            return;
        }
        if (file.is_open())
        {
            file << content;
            file.close();
            logInfo("File written: " + path);
        }
        else
        {
            logError("Failed to write file: " + path);
        }
    }
    catch (const exception &e)
    {
        logError("Exception occurred while writing file: " + path + ", " + e.what());
    }
}

void files::writeLines(string path, vector<string> lines)
{
    try
    {
        ofstream file(path.c_str());
        if(!file)
        {
            logError("File does not exist: " + path);
            return;
        }
        if (file.is_open())
        {
            for (string line : lines)
            {
                file << line << endl;
            }
            file.close();
            logInfo("File lines written: " + path);
        }
        else
        {
            logError("Failed to write file: " + path);
        }
    }
    catch (const exception &e)
    {
        logError("Exception occurred while writing file: " + path + ", " + e.what());
    }
}

long files::getLength(string path)
{
    try
    {
        ifstream file(path.c_str(), ios::binary | ios::ate);
        if(!file)
        {
            logError("File does not exist: " + path);
            return 0;
        }
        if (file.is_open())
        {
            long length = file.tellg();
            file.close();
            logInfo("File length retrieved: " + path);
            return length;
        }
        else
        {
            logError("Failed to retrieve file length: " + path);
            return 0;
        }
    }
    catch (const exception &e)
    {
        logError("Exception occurred while retrieving file length: " + path + ", " + e.what());
        return 0;
    }
}

void files::rename(string path, string newName, Bool::Bool overwrite)
{
    try
    {
        ifstream existingFile(path.c_str());
        if (!existingFile)
        {
            existingFile.close();
            logError("File does not exist: " + path);
            return;
        }
        existingFile.close();

        ifstream newFile(newName.c_str());
        if (newFile && !overwrite)
        {
            newFile.close();
            logWarning("File already exists: " + newName);
            return;
        }
        newFile.close();

        if (std::rename(path.c_str(), newName.c_str()) != 0)
        {
            logError("Failed to rename file: " + path);
            return;
        }

        logSuccess("File renamed: " + path + " -> " + newName);
    }
    catch (const exception &e)
    {
        logError("Exception occurred while renaming file: " + path + ", " + e.what());
    }
}

void files::copy(string path, string newPath, Bool::Bool overwrite)
{
    try
    {
        ifstream file(path.c_str(), ios::binary);
        if (!file)
        {
            file.close();
            logError("File does not exist: " + path);
            return;
        }

        ifstream newFile(newPath.c_str());
        if (newFile && !overwrite)
        {
            newFile.close();
            logWarning("File already exists: " + newPath);
            return;
        }
        newFile.close();

        ofstream outputFile(newPath.c_str(), ios::binary);
        if (file.is_open() && outputFile.is_open())
        {
            outputFile << file.rdbuf();
            file.close();
            outputFile.close();
            logSuccess("File copied: " + path + " -> " + newPath);
        }
        else
        {
            logError("Failed to copy file: " + path + " -> " + newPath);
        }
    }
    catch (const exception &e)
    {
        logError("Exception occurred while copying file: " + path + " -> " + newPath + ", " + e.what());
    }
}

void files::move(string path, string newPath, Bool::Bool overwrite)
{
    try
    {
        ifstream file(path.c_str(), ios::binary);
        if (!file)
        {
            file.close();
            logError("File does not exist: " + path);
            return;
        }

        ifstream newFile(newPath.c_str());
        if (newFile && !overwrite)
        {
            newFile.close();
            logWarning("File already exists: " + newPath);
            return;
        }
        newFile.close();

        ofstream outputFile(newPath.c_str(), ios::binary);
        if (file.is_open() && outputFile.is_open())
        {
            outputFile << file.rdbuf();
            file.close();
            outputFile.close();
            logSuccess("File moved: " + path + " -> " + newPath);
        }
        else
        {
            logError("Failed to move file: " + path + " -> " + newPath);
            return;
        }

        std::remove(path.c_str());
    }
    catch (const exception &e)
    {
        logError("Exception occurred while moving file: " + path + " -> " + newPath + ", " + e.what());
    }
}