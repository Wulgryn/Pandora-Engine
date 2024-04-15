#pragma once
#include "../../Core/Components/ComponentsHandler.hpp"
#include "ObjectsHandler.hpp"
#include "../../IO/Window.hpp"
#include "../Event.hpp"
#include "../Types.hpp"
#include <vector>

class BaseObject : public ComponentsHandler
{
private:
    ObjectsHandler* objects_handler;
    Window* window;
public:
    Tag tag = ObjectTags::None;

    BaseObject();

    virtual void Initialize();
    virtual void Start();
    virtual void Update();

    void Destroy();

    void SetObjectsHandler(ObjectsHandler* objects_handler);
    ObjectsHandler* GetObjectsHandler();

    void SetParentWindow(Window* window) { this->window = window; }
    Window* GetParentWindow() { return window; }

    /// @brief Invoked every Ojbect update before the componenets updated.
    /// @param BaseObject* The Object that is being updated.
    Event<BaseObject*> OnUpdate;

    /// @brief Invoked every Ojbect update after the componenets updated.
    /// @param BaseObject* The Object that is being updated.
    Event<BaseObject*> OnLateUpdate;
};