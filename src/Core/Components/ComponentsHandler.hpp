#pragma once
#include <vector>
#include "../ClassObject.hpp"
#include "../Elements/ObjectsHandler.hpp"

class BaseComponent;
class BaseObject;

class ComponentsHandler
{
private:
    std::vector<BaseComponent*> components;
    BaseObject* object = nullptr;
public:
    ComponentsHandler(BaseObject* object);

    // HACK CAUTION: Maybe merge the 2 AddComponent functions into one
    /**
     *^  *=======================================================================
     *^  * DESCRIPTION: the normal addcomponent and the addcomponentbyreference, merge into one like AddCOmponent<ComponenetType>(BaseComponent* component = nullptr)
     *^  *=======================================================================
    **/

    template <typename ComponentType>
    ComponentType* AddComponent();
    template <typename ComponentType, typename Object = ClassObject*>
    ComponentType* AddComponent(ClassObject* object);
    void AddComponenetByReference(BaseComponent* component);

    template <typename ComponentType> ComponentType* GetComponent();

    template <typename ComponentType> bool HasComponent();

    bool IsEmpty();

    int GetComponentsCount() { return components.size(); }


    /// @brief Initializes all components
    void InitializeComponents();

    /// @brief Updates all components
    void UpdateComponents();

    BaseObject* GetParentObject() { return object; }
};

namespace Components
{
    template <typename ComponentType> ComponentType* Get(ComponentsHandler* handler);
    template <typename ComponentType> bool Has(ComponentsHandler* handler);
    bool isEmpty(ComponentsHandler* handler);
} // namespace Components