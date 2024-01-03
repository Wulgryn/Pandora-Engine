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
        UIElement* this_class = this;
        Object ui_object;
        UIElement();
        virtual Components* getComponents();
    };

} // namespace pandora