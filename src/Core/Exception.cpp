#include "Exceptions.hpp"
#include "Console.hpp"
#include "IO/Logger.hpp"

#include <typeinfo>
#include <memory>
#include <cxxabi.h>

using namespace PandoraEngine;
using namespace Exceptions;
using namespace Console;
using namespace std;

std::string Exception::className()
{
    int status = 0;
    std::unique_ptr<char[], void (*)(void *)> res{
        abi::__cxa_demangle(typeid(*this).name(), nullptr, nullptr, &status),
        std::free};
    return (status == 0) ? res.get() : typeid(*this).name();
}

Exception::Exception(std::string message)
{
    _message = message;
}

const char *Exception::what() const noexcept
{
    return _message.c_str();
}

std::string Exception::message() const noexcept
{
    return _message;
}

void Exception::throw_()
{
#ifdef PE_DEBUG
    string msg = "\"" + _message + "\" thrown from " + className() + ".";
    DebugConsole::WriteLine(msg);
#endif
    throw *this;
}

void Exception::print(bool log)
{
    string msg = "\"" + _message + "\" thrown from " + className() + ".";
#ifdef PE_DEBUG
    DebugConsole::WriteLine(msg);
#else
    if (log)
        Logger::WriteLine(msg);
    Console::WriteLine(msg);
#endif
}

Exception Exception::throw_(std::string message)
{
    Exception e(message);
    e.throw_();
    return e;
}

Exception Exception::print(std::string message, bool log)
{
    Exception e(message);
    e.print(log);
    return e;
}