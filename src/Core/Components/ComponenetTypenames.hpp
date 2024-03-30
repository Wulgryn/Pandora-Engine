#pragma once
#include "ComponentsHandler.hpp"
#include "Transform2D.hpp"
#include "ShaderComponent2D.hpp"

#include "../ClassObject.hpp"

template BaseComponent* ComponentsHandler::AddComponenet<BaseComponent>();
template Transform2D* ComponentsHandler::AddComponenet<Transform2D>();
template ShaderComponent2D* ComponentsHandler::AddComponenet<ShaderComponent2D>();



template ShaderComponent2D* ComponentsHandler::AddComponenet<ShaderComponent2D, Shader>(ClassObject* shader);

template bool ComponentsHandler::HasComponenet<BaseComponent>();
template bool ComponentsHandler::HasComponenet<Transform2D>();
template bool ComponentsHandler::HasComponenet<ShaderComponent2D>();

template Transform2D* ComponentsHandler::GetComponenet<Transform2D>();
template ShaderComponent2D* ComponentsHandler::GetComponenet<ShaderComponent2D>();

template Transform2D* Components::Get<Transform2D>(ComponentsHandler* handler);
template ShaderComponent2D* Components::Get<ShaderComponent2D>(ComponentsHandler* handler);

template bool Components::Has<Transform2D>(ComponentsHandler* handler);
template bool Components::Has<ShaderComponent2D>(ComponentsHandler* handler);