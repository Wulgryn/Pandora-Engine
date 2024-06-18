#ifndef IWINDOEVENTS_HPP
#define IWINDOEVENTS_HPP

#include "../../Core/Macros.h"

namespace PandoraEngine::Windows::WindowEvents
{
    class DLL WindowPropertyChangeEvents
    {
    protected:
        WindowPropertyChangeEvents() = default;

    public:
    };

    class DLL WindowActionEvents
    {
    protected:
        WindowActionEvents() = default;

    public:
    };

    class DLL WindowInputEvents
    {
    protected:
        WindowInputEvents() = default;

    public:
    };
} // namespace PandoraEngine::Windows::WindowInterface

#endif // IWINDOEVENTS_HPP