#include "Object.hpp"
#include "Debug/Console.hpp"


BaseObject::BaseObject() : ComponentsHandler(this)
{}

void BaseObject::Initialize()
{
    InitializeComponents();
}

void BaseObject::Start()
{
    
}

void BaseObject::Update()
{
    UpdateComponents();
}

void BaseObject::Destroy()
{
    delete this;
}

void BaseObject::SetObjectsHandler(ObjectsHandler* objects_handler)
{
    this->objects_handler = objects_handler;
}

ObjectsHandler* BaseObject::GetObjectsHandler()
{
    return objects_handler;
}