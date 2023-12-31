#pragma once
#include "DLL/dll.hpp"
#include <vector>

//#include "shader.hpp"

namespace pandora
{
    class DLL Components;
    class DLL Component
    {
    public:
        virtual void init(Components* components){};
    };

    class DLL Components
    {
    private:
        std::vector<Component *> components_list;
    public:
        Components(){};
        void initComponenets();

        template<typename ComponentType> ComponentType* add(ComponentType* component = nullptr);
        template<typename ComponentType> ComponentType* get();

        bool isEmpty();

        template<typename ComponentType>bool has();

    };
}