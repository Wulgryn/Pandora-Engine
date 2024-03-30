#include "ComponentsHandler.hpp"
#include "ComponenetTypenames.hpp"
#include "BaseComponent.hpp"

ComponentsHandler::ComponentsHandler(BaseObject* object)
{
    this->object = object;
}

template <typename ComponentType> ComponentType* Components::Get(ComponentsHandler* handler)
{
    return handler->GetComponenet<ComponentType>();
}

template <typename ComponentType> bool Components::Has(ComponentsHandler* handler)
{
    return handler->HasComponenet<ComponentType>();
}

bool Components::isEmpty(ComponentsHandler* handler)
{
    return handler->IsEmpty();
}

template <typename ComponentType> ComponentType* ComponentsHandler::AddComponenet()
{
    BaseComponent* component = new ComponentType();
    component->SetHandler(this);
    
    components.push_back(component);
    return dynamic_cast<ComponentType*>(component);
}

template <typename ComponentType, typename Object> ComponentType* ComponentsHandler::AddComponenet(ClassObject* object)
{
    BaseComponent* component = new ComponentType(static_cast<Object*>(object));
    component->SetHandler(this);
    
    components.push_back(component);
    return dynamic_cast<ComponentType*>(component);
}

void ComponentsHandler::AddComponenet(BaseComponent* component)
{
    components.push_back(component);
}

template <typename ComponentType> ComponentType* ComponentsHandler::GetComponenet()
{
    for (BaseComponent* component : components)
    {
        ComponentType* comp = dynamic_cast<ComponentType*>(component);
        if (comp)
        {
            return comp;
        }
    }
    return nullptr;
}

template <typename ComponentType> bool ComponentsHandler::HasComponenet()
{
    for (BaseComponent* component : components)
    {
        if (dynamic_cast<ComponentType*>(component))
        {
            return true;
        }
    }
    return false;
}

bool ComponentsHandler::IsEmpty()
{
    return components.empty();
}

void ComponentsHandler::InitializeComponenets()
{
    for (BaseComponent* component : components)
    {
        component->Initialize();
    }
}

void ComponentsHandler::UpdateComponenets()
{
    for (BaseComponent* component : components)
    {
        component->Update();
    }
}

