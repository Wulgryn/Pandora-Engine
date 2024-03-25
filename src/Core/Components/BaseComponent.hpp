#pragma once
class BaseComponent 
{
public:
    BaseComponent();

    virtual void Update();

    void Destroy();
};