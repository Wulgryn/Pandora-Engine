#include "ComponentsHandler.hpp"
#include "ComponenetTypenames.hpp"
#include "BaseComponent.hpp"

ComponentsHandler::ComponentsHandler(BaseObject* object)
{
    this->object = object;
}

template <typename ComponentType> ComponentType* Components::Get(ComponentsHandler* handler)
{
    return handler->GetComponent<ComponentType>();
}

template <typename ComponentType> bool Components::Has(ComponentsHandler* handler)
{
    return handler->HasComponent<ComponentType>();
}

bool Components::isEmpty(ComponentsHandler* handler)
{
    return handler->IsEmpty();
}

template <typename ComponentType> ComponentType* ComponentsHandler::AddComponent()
{
    BaseComponent* component = new ComponentType();
    component->SetHandler(this);
    
    components.push_back(component);
    return dynamic_cast<ComponentType*>(component);
}

template <typename ComponentType, typename Object> ComponentType* ComponentsHandler::AddComponent(ClassObject* object)
{
    BaseComponent* component = new ComponentType(static_cast<Object*>(object));
    component->SetHandler(this);
    
    components.push_back(component);
    return dynamic_cast<ComponentType*>(component);
}

void ComponentsHandler::AddComponenetByReference(BaseComponent* component)
{
    components.push_back(component);
}

template <typename ComponentType> ComponentType* ComponentsHandler::GetComponent()
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

template <typename ComponentType> bool ComponentsHandler::HasComponent()
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

void ComponentsHandler::InitializeComponents()
{
    for (BaseComponent* component : components)
    {
        component->Initialize();
    }
}

void ComponentsHandler::UpdateComponents()
{
    for (BaseComponent* component : components)
    {
        component->Update();
    }
}

