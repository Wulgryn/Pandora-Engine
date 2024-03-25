#include "Object.hpp"
#include "Debug/Console.hpp"


BaseObject::BaseObject(){}

void BaseObject::Update()
{
    UpdateComponenets();
}

void BaseObject::Destroy()
{
    delete this;
}