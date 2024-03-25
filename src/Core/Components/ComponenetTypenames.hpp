#pragma once
#include "ComponentsHandler.hpp"
#include "Transform2D.hpp"
#include "ShaderComponent.hpp"

template BaseComponent* ComponentsHandler::AddComponenet<BaseComponent>();
template Transform2D* ComponentsHandler::AddComponenet<Transform2D>();
template ShaderComponent* ComponentsHandler::AddComponenet<ShaderComponent>();

template bool ComponentsHandler::HasComponenet<BaseComponent>();
template bool ComponentsHandler::HasComponenet<Transform2D>();
template bool ComponentsHandler::HasComponenet<ShaderComponent>();

template Transform2D* ComponentsHandler::GetComponenet<Transform2D>();
template ShaderComponent* ComponentsHandler::GetComponenet<ShaderComponent>();

template Transform2D* Components::Get<Transform2D>(ComponentsHandler* handler);
template ShaderComponent* Components::Get<ShaderComponent>(ComponentsHandler* handler);

template bool Components::Has<Transform2D>(ComponentsHandler* handler);
template bool Components::Has<ShaderComponent>(ComponentsHandler* handler);