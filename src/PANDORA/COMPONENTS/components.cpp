#include "components.hpp"
#include "CONSOLE/fancyLog.hpp"
#include <memory>

#include "shader.hpp"
#include "transform.hpp"
#include "image.hpp"

using namespace std;
using namespace pandora;

void Components::initComponenets()
{
    for (Component *component : components_list) {
        component->init(this);
    }
}

template void Components::add<Shader>();
template void Components::add<Transform>();
template void Components::add<Image>();

template Shader *Components::get<Shader>();
template Transform *Components::get<Transform>();
template Image *Components::get<Image>();

template<typename ComponentType>
void Components::add()
{
    static_assert(is_base_of<Component, ComponentType>::value, "Class must be a Component");
    components_list.push_back(new ComponentType());
}

template<typename ComponentType>
ComponentType *Components::get()
{
    static_assert(is_base_of<Component, ComponentType>::value, "Class must be a Component");
    for (Component *component : components_list) {
        if (dynamic_cast<ComponentType *>(component)) {
            return dynamic_cast<ComponentType *>(component);
        }
    }
    return nullptr;
}
