#ifndef PANDORA_CORE_HPP
#define PANDORA_CORE_HPP

#define PE_VERSION "0.1.1 pre-alpha"
#define PE_TAGS "experimental"

#include "Core/Macros.h"

namespace PandoraEngine
{
    DLL void initialize();

    namespace Application
    {
        DLL int start(bool stopOnExit = false);
    } // namespace Application
} // namespace PandoraEngine

#endif // PANDORA_CORE_HPP