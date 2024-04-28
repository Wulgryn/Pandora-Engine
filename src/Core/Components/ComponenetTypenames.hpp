#pragma once
#include "ComponentsHandler.hpp"
#include "Transform2D.hpp"
#include "ShaderComponent2D.hpp"
#include "Texture2D.hpp"
#include "TextComponenet2D.hpp"
#include "CollisionComponent2D.hpp"


#include "../ClassObject.hpp"

template BaseComponent* ComponentsHandler::AddComponent<BaseComponent>();
template Transform2D* ComponentsHandler::AddComponent<Transform2D>();
template ShaderComponent2D* ComponentsHandler::AddComponent<ShaderComponent2D>();
template Texture2D* ComponentsHandler::AddComponent<Texture2D>();
template TextComponent2D* ComponentsHandler::AddComponent<TextComponent2D>();
template CollisionComponent2D* ComponentsHandler::AddComponent<CollisionComponent2D>();


template ShaderComponent2D* ComponentsHandler::AddComponent<ShaderComponent2D, Shader>(ClassObject* shader);


template bool ComponentsHandler::HasComponent<BaseComponent>();
template bool ComponentsHandler::HasComponent<Transform2D>();
template bool ComponentsHandler::HasComponent<ShaderComponent2D>();
template bool ComponentsHandler::HasComponent<Texture2D>();
template bool ComponentsHandler::HasComponent<TextComponent2D>();
template bool ComponentsHandler::HasComponent<CollisionComponent2D>();

template Transform2D* ComponentsHandler::GetComponent<Transform2D>();
template ShaderComponent2D* ComponentsHandler::GetComponent<ShaderComponent2D>();
template Texture2D* ComponentsHandler::GetComponent<Texture2D>();
template TextComponent2D* ComponentsHandler::GetComponent<TextComponent2D>();
template CollisionComponent2D* ComponentsHandler::GetComponent<CollisionComponent2D>();

template Transform2D* Components::Get<Transform2D>(ComponentsHandler* handler);
template ShaderComponent2D* Components::Get<ShaderComponent2D>(ComponentsHandler* handler);
template Texture2D* Components::Get<Texture2D>(ComponentsHandler* handler);
template TextComponent2D* Components::Get<TextComponent2D>(ComponentsHandler* handler);
template CollisionComponent2D* Components::Get<CollisionComponent2D>(ComponentsHandler* handler);

template bool Components::Has<Transform2D>(ComponentsHandler* handler);
template bool Components::Has<ShaderComponent2D>(ComponentsHandler* handler);
template bool Components::Has<Texture2D>(ComponentsHandler* handler);
template bool Components::Has<TextComponent2D>(ComponentsHandler* handler);
template bool Components::Has<CollisionComponent2D>(ComponentsHandler* handler);