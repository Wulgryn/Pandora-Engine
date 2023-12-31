#pragma once
#include "DLL/dll.hpp"
#include "PANDORA/COMPONENTS/components.hpp"
#include "PANDORA/objects.hpp"

namespace pandora
{
    class DLL UIElement : public Component
    {
    private:
    public:
        Object ui_object;
        UIElement();
    };

} // namespace pandora