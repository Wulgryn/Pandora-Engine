#ifndef EXCEPTIONS_HPP
#define EXCEPTIONS_HPP

#include "Core/Macros.h"

#include <exception>
#include <string>

namespace PandoraEngine
{
    namespace Exceptions
    {
        class DLL Exception : public std::exception
        {
        private:
            std::string _message;
            virtual std::string className();
        public:
            Exception(std::string message);

            const char *what() const noexcept override;
            std::string message() const noexcept;
            virtual void throw_();
            void print(bool log = false);

            static Exception throw_(std::string message);
            static Exception print(std::string message, bool log = false);

            virtual ~Exception() = default;
        };

        class DLL RuntimeException : public Exception
        {
        public:
            RuntimeException(std::string message) : Exception(message) {}
        };

        class DLL GLFWException : public RuntimeException
        {
        public:
            GLFWException(std::string message) : RuntimeException(message) {}
        };

        class DLL GLADException : public RuntimeException
        {
        public:
            GLADException(std::string message) : RuntimeException(message) {}
        };
    } // namespace Exceptions

    // class DLL
} // namespace PandoraEngine

#endif // EXCEPTIONS_HPP