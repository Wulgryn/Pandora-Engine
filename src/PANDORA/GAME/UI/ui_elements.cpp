#include "ui_elements.hpp"

#include "PANDORA/COMPONENTS/shader.hpp"
#include "PANDORA/COMPONENTS/image.hpp"
#include "PANDORA/COMPONENTS/transform.hpp"

using namespace pandora;

UIElement::UIElement()
{
    ui_object.Components().add<UIElement>(this);
    ui_object.Components().add<Image>();
    ui_object.Components().add<Shader>();
    ui_object.Components().add<Transform>();
}