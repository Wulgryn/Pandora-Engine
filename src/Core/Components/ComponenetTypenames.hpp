#pragma once
#include "ComponentsHandler.hpp"
#include "Transform2D.hpp"
#include "ShaderComponent2D.hpp"
#include "Texture2D.hpp"
#include "TextComponenet2D.hpp"


#include "../ClassObject.hpp"

template BaseComponent* ComponentsHandler::AddComponenet<BaseComponent>();
template Transform2D* ComponentsHandler::AddComponenet<Transform2D>();
template ShaderComponent2D* ComponentsHandler::AddComponenet<ShaderComponent2D>();
template Texture2D* ComponentsHandler::AddComponenet<Texture2D>();
template TextComponent2D* ComponentsHandler::AddComponenet<TextComponent2D>();



template ShaderComponent2D* ComponentsHandler::AddComponenet<ShaderComponent2D, Shader>(ClassObject* shader);

template bool ComponentsHandler::HasComponenet<BaseComponent>();
template bool ComponentsHandler::HasComponenet<Transform2D>();
template bool ComponentsHandler::HasComponenet<ShaderComponent2D>();
template bool ComponentsHandler::HasComponenet<Texture2D>();
template bool ComponentsHandler::HasComponenet<TextComponent2D>();

template Transform2D* ComponentsHandler::GetComponenet<Transform2D>();
template ShaderComponent2D* ComponentsHandler::GetComponenet<ShaderComponent2D>();
template Texture2D* ComponentsHandler::GetComponenet<Texture2D>();
template TextComponent2D* ComponentsHandler::GetComponenet<TextComponent2D>();

template Transform2D* Components::Get<Transform2D>(ComponentsHandler* handler);
template ShaderComponent2D* Components::Get<ShaderComponent2D>(ComponentsHandler* handler);
template Texture2D* Components::Get<Texture2D>(ComponentsHandler* handler);
template TextComponent2D* Components::Get<TextComponent2D>(ComponentsHandler* handler);

template bool Components::Has<Transform2D>(ComponentsHandler* handler);
template bool Components::Has<ShaderComponent2D>(ComponentsHandler* handler);
template bool Components::Has<Texture2D>(ComponentsHandler* handler);
template bool Components::Has<TextComponent2D>(ComponentsHandler* handler);