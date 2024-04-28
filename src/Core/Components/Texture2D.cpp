#include "Texture2D.hpp"

void Texture2D::SetTexture(Texture* texture)
{
    this->texture = texture;
}

void Texture2D::SetColor(Color* color)
{
    this->color = color;
}

Texture* Texture2D::GetTexture()
{
    return texture;
}

Color* Texture2D::GetColor()
{
    return color;
}

bool Texture2D::HasTexture()
{
    return texture != nullptr;
}
