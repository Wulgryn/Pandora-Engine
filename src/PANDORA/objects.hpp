#pragma once
#include "DLL/dll.hpp"
#include "COMPONENTS/components.hpp"
#include <vector>
#include <string>
namespace pandora
{
    class DLL Object
    {
    private:
        pandora::Components components;
    public:
        std::string name = "Object";

        Object();
        ~Object();

        pandora::Components &Components();
    };

    namespace objects
    {
        DLL void render();
        DLL void add(Object *object);
    } // namespace objects
    
}