#include "Object.hpp"

Object::Object()
{
    AddComponent<Transform2D>();
    AddComponent<Texture2D>();
    AddComponent<ShaderComponent2D>();
}