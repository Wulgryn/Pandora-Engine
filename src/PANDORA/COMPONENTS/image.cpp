#include "image.hpp"

using namespace pandora;

Image::Image()
{
    color = utils::Color(0.3f,0.8f,0.5f);
}

void pandora::Image::setTexture(Texture* texture)
{
    this->texture = texture;
}
