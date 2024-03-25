#pragma once
#include <vector>

class BaseComponent;

class ComponentsHandler
{
private:
    std::vector<BaseComponent*> components;
public:
    ComponentsHandler();

    template <typename ComponentType> ComponentType* AddComponenet();
    void AddComponenet(BaseComponent* component);
    template <typename ComponentType> ComponentType* GetComponenet();
    template <typename ComponentType> bool HasComponenet();
    bool IsEmpty();

    int GetComponentsCount() { return components.size(); }

    /// @brief Updates all components
    void UpdateComponenets();
};

namespace Components
{
    template <typename ComponentType> ComponentType* Get(ComponentsHandler* handler);
    template <typename ComponentType> bool Has(ComponentsHandler* handler);
    bool isEmpty(ComponentsHandler* handler);
} // namespace Components