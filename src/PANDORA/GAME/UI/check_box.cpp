#include "check_box.hpp"

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

CheckBox::CheckBox() : UIElement()
{
    Transform *background_transform = ui_object.Components().get<Transform>();

    background_transform->size.Height = 50;
    background_transform->size.Width = 50;
    background_transform->position.x = 130;
    background_transform->position.y = 50;

    foreground.Components().add<UIElement>(this);
    Image* foreground_image = foreground.Components().add<Image>();
    foreground_image->color = {random::getByte(0, 255), random::getByte(0, 255), random::getByte(0, 255)};
    foreground_image->isVisible = false;
    foreground_image->texture = -1;
    foreground.Components().add<Shader>();
    Transform *foreground_transform = foreground.Components().add<Transform>();

    foreground_transform->size.Height = background_transform->size.Height - 10;
    foreground_transform->size.Width = background_transform->size.Width - 10;
    foreground_transform->position.x = background_transform->position.x + 5;
    foreground_transform->position.y = background_transform->position.y + 5;
}

Object* CheckBox::getForeground()
{
    return &foreground;
}

Object* CheckBox::getBackground()
{
    return &ui_object;
}



void CheckBox::init(Components* components)
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
            isChecked = !isChecked;
            isSelected = false;
        }
        
    }

    foreground.Components().get<Image>()->isVisible = isChecked;
}