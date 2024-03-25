#include "BaseComponent.hpp"
#include "../../Debug/Console.hpp"

BaseComponent::BaseComponent()
{
    
}

void BaseComponent::Update()
{
    
}

void BaseComponent::Destroy()
{
    delete this;
}