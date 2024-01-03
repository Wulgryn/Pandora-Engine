#include "ui_elements.hpp"

#include "PANDORA/COMPONENTS/shader.hpp"
#include "PANDORA/COMPONENTS/image.hpp"
#include "PANDORA/COMPONENTS/transform.hpp"

#include "UTILS/random.hpp"


using namespace utils;
using namespace pandora;

UIElement::UIElement()
{
    ui_object.Components().add<UIElement>(this);
    ui_object.Components().add<Image>()->color = {random::getByte(0,255),random::getByte(0,255),random::getByte(0,255)};
    ui_object.Components().add<Shader>();
    ui_object.Components().add<Transform>();
}

Components* UIElement::getComponents()
{
    return &ui_object.Components();
}