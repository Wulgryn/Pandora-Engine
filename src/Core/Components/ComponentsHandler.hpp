#pragma once
#include <vector>
#include "../ClassObject.hpp"
#include "../Rendering/ObjectsHandler.hpp"

class BaseComponent;
class BaseObject;

class ComponentsHandler
{
private:
    std::vector<BaseComponent*> components;
    BaseObject* object = nullptr;
public:
    ComponentsHandler(BaseObject* object);
    template <typename ComponentType> ComponentType* AddComponenet();
    template <typename ComponentType, typename Object = ClassObject*> ComponentType* AddComponenet(ClassObject* object);
    void AddComponenet(BaseComponent* component);

    template <typename ComponentType> ComponentType* GetComponenet();

    template <typename ComponentType> bool HasComponenet();

    bool IsEmpty();

    int GetComponentsCount() { return components.size(); }


    /// @brief Initializes all components
    void InitializeComponenets();

    /// @brief Updates all components
    void UpdateComponenets();

    BaseObject* GetParentObject() { return object; }
};

namespace Components
{
    template <typename ComponentType> ComponentType* Get(ComponentsHandler* handler);
    template <typename ComponentType> bool Has(ComponentsHandler* handler);
    bool isEmpty(ComponentsHandler* handler);
} // namespace Components