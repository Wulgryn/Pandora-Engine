#include "switch.hpp"

#include "PANDORA/COMPONENTS/image.hpp"
#include "PANDORA/COMPONENTS/shader.hpp"
#include "PANDORA/COMPONENTS/transform.hpp"
#include "PANDORA/mainWindow.hpp"
#include "UTILS/random.hpp"
#include "IO/mouse.hpp"

#include "CONSOLE/fancyLog.hpp"

using namespace pandora;
using namespace utils;
using namespace io;

Switch::Switch() : UIElement()
{
    Transform *background_transform = ui_object.Components().get<Transform>();

    background_transform->size.Height = 50;
    background_transform->size.Width = 120;
    background_transform->position.x = 210;
    background_transform->position.y = 50;

    foreground.Components().add<UIElement>(this);
    foreground.Components().add<Image>()->color = {random::getByte(0, 255), random::getByte(0, 255), random::getByte(0, 255)};
    foreground.Components().add<Shader>();
    Transform *foreground_transform = foreground.Components().add<Transform>();

    foreground_transform->size.Height = background_transform->size.Height - 4;
    foreground_transform->size.Width = (background_transform->size.Width / 2) - 1;
    foreground_transform->position.x = background_transform->position.x + 1;
    foreground_transform->position.y = background_transform->position.y + 2;
}

Object* Switch::getForeground()
{
    return &foreground;
}

Object* Switch::getBackground()
{
    return &ui_object;
}



void Switch::init(Components* components)
{
    Position mouse_pos = mouse::getWindowPosition().getRealPosition(mainWindow::get()->parameters.getSize());
    Transform *background_transform = ui_object.Components().get<Transform>();

    if(mouse_pos.x >= background_transform->position.x && mouse_pos.x <= background_transform->position.x + background_transform->size.Width &&
        mouse_pos.y >= background_transform->position.y && mouse_pos.y <= background_transform->position.y + background_transform->size.Height)
    {
        if(mouse::getMouseButtonDown(MouseButton::LEFT))
        {
            isSelected = true;
        }
        if(mouse::getMouseButtonReleased(MouseButton::LEFT) && isSelected)
        {
            isOn = !isOn;
            isSelected = false;
        }
        
    }

    Transform *foreground_transform = foreground.Components().get<Transform>();
    if(isOn)
    {
        foreground_transform->position.x = background_transform->position.x + background_transform->size.Width / 2;
    }
    else
    {
        foreground_transform->position.x = background_transform->position.x + 1;
    }
}