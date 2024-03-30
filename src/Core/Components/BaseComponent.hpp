#pragma once

#include "ComponentsHandler.hpp"
class BaseComponent 
{
protected:
    ComponentsHandler* componenetHandler;
public:
    void SetHandler(ComponentsHandler* handler);

    virtual void Initialize();
    virtual void Update();

    void Destroy();

    ComponentsHandler* GetHandler();
};