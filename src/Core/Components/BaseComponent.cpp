#include "BaseComponent.hpp"
#include "../../Debug/Console.hpp"

void BaseComponent::SetHandler(ComponentsHandler* handler)
{
    this->componenetHandler = handler;
}

void BaseComponent::Initialize(){}
void BaseComponent::Update(){}

void BaseComponent::Destroy()
{
    delete this;
}

ComponentsHandler* BaseComponent::GetHandler()
{
    return componenetHandler;
}