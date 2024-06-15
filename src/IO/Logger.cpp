#include "Logger.hpp"

#include <iostream>
#include <fstream>
#include <sys/stat.h>
#include <direct.h>
#include <cstdio>
#include <ctime>
#include <stdarg.h>
#include <iomanip>
#include <chrono>
using namespace std;
using namespace std::chrono;

namespace PandoraEngine
{
    ofstream log_file;
    ofstream latest_log_file;
    namespace Logger
    {
        void Initialize(const char *root_dir)
        {
            string dir = string(root_dir) + "logs/";

            // Structure which would store the metadata
            struct stat sb;

            // Calls the function with path as argument
            // If the file/directory exists at the path returns 0
            // If block executes if path exists
            if (stat(dir.c_str(), &sb) != 0)
            {
#ifdef _WIN32
                _mkdir(dir.c_str());
#else
                mkdir(dir.c_str(), 0777);
#endif
            }

            std::time_t rawtime;
            std::tm *timeinfo;
            char buffer[80];

            std::time(&rawtime);
            timeinfo = std::localtime(&rawtime);

            std::strftime(buffer, 80, "%Y-%m-%d-%H-%M-%S", timeinfo);
            // std::puts(buffer);
            log_file.open(dir + "pe-" + buffer + ".log");
            latest_log_file.open(dir + "latest.log");
            latest_log_file.clear();
            latest_log_file.flush();
        }

        void WriteTime()
        {
            auto now = system_clock::now();
            auto time = system_clock::to_time_t(now);
            auto duration = now.time_since_epoch();

            tm *tm = localtime(&time);
            char buffer[80];
            strftime(buffer, sizeof(buffer), "[%m.%d|%H:%M:%S", tm);

            latest_log_file << buffer << "s." << std::setw(3) << std::setfill('0') << duration_cast<milliseconds>(duration).count() % 1000 << "ms.";
            latest_log_file << std::setw(3) << std::setfill('0') << duration_cast<microseconds>(duration).count() % 1000 << "us]";

            log_file << buffer << "s." << std::setw(3) << std::setfill('0') << duration_cast<milliseconds>(duration).count() % 1000 << "ms.";
            log_file << std::setw(3) << std::setfill('0') << duration_cast<microseconds>(duration).count() % 1000 << "us]";
        }

        void WriteLine(std::string format, va_list args)
        {
            WriteTime();

            int size = vsnprintf(nullptr, 0, format.c_str(), args) + 1;
            char *buffer = new char[size];

            vsnprintf(buffer, size, format.c_str(), args);

            latest_log_file << buffer;
            log_file << buffer;

            free(buffer); // memória felszabadítása
        }

        void Write(std::string format, va_list args)
        {
            int size = vsnprintf(nullptr, 0, format.c_str(), args) + 1;
            char *buffer = new char[size];

            vsnprintf(buffer, size, format.c_str(), args);

            latest_log_file << buffer;
            log_file << buffer;

            free(buffer); // memória felszabadítása
        }
    } // namespace Logger
} // namespace PandoraEngine