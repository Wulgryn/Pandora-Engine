#include "components.hpp"
#include "CONSOLE/fancyLog.hpp"
#include <memory>

#include "shader.hpp"
#include "transform.hpp"
#include "image.hpp"
#include "PANDORA/GAME/UI/ui_elements.hpp"

using namespace std;
using namespace pandora;

void Components::initComponenets()
{
    for (Component *component : components_list) {
        component->init(this);
    }
}

template Shader* Components::add<Shader>(Shader *component);
template Transform* Components::add<Transform>(Transform *component);
template Image* Components::add<Image>(Image *component);
template UIElement* Components::add<UIElement>(UIElement *component);

template Shader *Components::get<Shader>();
template Transform *Components::get<Transform>();
template Image *Components::get<Image>();
template UIElement *Components::get<UIElement>();

template bool Components::has<Shader>();
template bool Components::has<Transform>();
template bool Components::has<Image>();
template bool Components::has<UIElement>();

template<typename ComponentType>
ComponentType* Components::add(ComponentType *component)
{
    static_assert(is_base_of<Component, ComponentType>::value, "Class must be a Component");
    if(component != nullptr){
        components_list.push_back(component);
        return component;
    }
    components_list.push_back(new ComponentType());
    return dynamic_cast<ComponentType*>(components_list.back());
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

bool Components::isEmpty()
{
    return components_list.size() == 0;
}

template<typename ComponentType>
bool Components::has()
{
    static_assert(is_base_of<Component, ComponentType>::value, "Class must be a Component");
    for (Component *component : components_list) {
        if (dynamic_cast<ComponentType *>(component)) {
            return true;
        }
    }
    return false;
}