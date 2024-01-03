#include "scrollbar.hpp"

#include "PANDORA/COMPONENTS/image.hpp"
#include "PANDORA/COMPONENTS/shader.hpp"
#include "PANDORA/COMPONENTS/transform.hpp"
#include "PANDORA/mainWindow.hpp"
#include "UTILS/random.hpp"
#include "IO/mouse.hpp"
#include <algorithm>
#include <vector>

#include "CONSOLE/fancyLog.hpp"

using namespace pandora;
using namespace utils;
using namespace std;

Scrollbar::Scrollbar() : UIElement()
{
    Transform *background_transform = ui_object.Components().get<Transform>();

    background_transform->size.Height = 400;
    background_transform->size.Width = 15;
    background_transform->position.x = 600;
    background_transform->position.y = 50;

    foreground.Components().add<UIElement>(this);
    foreground.Components().add<Image>()->color = {random::getByte(0, 255), random::getByte(0, 255), random::getByte(0, 255)};
    foreground.Components().add<Shader>();
    Transform *foreground_transform = foreground.Components().add<Transform>();

    foreground_transform->size.Height = background_transform->size.Height - 2;
    foreground_transform->size.Width = background_transform->size.Width - 2;
    foreground_transform->position.x = background_transform->position.x + 1;
    foreground_transform->position.y = background_transform->position.y + 1;

    // vector<pandora::Object *>::iterator ui_it = find(objects::getObjectsList().begin(), objects::getObjectsList().end(), &ui_object);
    // vector<pandora::Object *>::iterator foreground_it = find(objects::getObjectsList().begin(), objects::getObjectsList().end(), &foreground);
    // std::iter_swap(ui_it, foreground_it);
}

void Scrollbar::setValue(double value)
{
    this->value = value - (value / maximum) * step;
}

double Scrollbar::getValue()
{
    return value + (value / (maximum - step)) * step;
}

double Scrollbar::getPercentage()
{
    return value / (maximum - step);
}

void Scrollbar::setPercentage(double percentage)
{
    this->percentage = percentage;
    value = (this->percentage - (0.1 * this->percentage)) * maximum;
}

void Scrollbar::setScrollY(double y)
{

    value = -y / (ui_object.Components().get<Transform>()->size.Height) * maximum;
}

double Scrollbar::getScrollY()
{
    return getPercentage() * (ui_object.Components().get<Transform>()->size.Height);
}

void Scrollbar::bindObject(Object *object)
{
    binded_objects.push_back(object);
}

void Scrollbar::init(Components *components)
{
    Transform *foreground_transform = foreground.Components().get<Transform>();
    Transform *background_transform = ui_object.Components().get<Transform>();

    foreground_transform->size.Height = background_transform->size.Height * (step / maximum);
    double foreground_scrollHeight = background_transform->size.Height - 2;

    Position mouse_position = io::mouse::getWindowPosition().getRealPosition(pandora::mainWindow::get()->parameters.getSize());
    Position background_position = background_transform->position;

    if (io::mouse::getMouseButtonReleased(io::MouseButton::LEFT))
    {
        isSelected = false;
    }

    if (mouse_position.x > background_position.x &&
        mouse_position.x < background_position.x + background_transform->size.Width &&
        mouse_position.y > background_position.y &&
        mouse_position.y < background_position.y + background_transform->size.Height)
    {
        if (io::mouse::getMouseButtonDown(io::MouseButton::LEFT))
        {
            isSelected = true;
            // logInfo("Mouse is on scrollbar x+");
        }
        // logInfo("Mouse is on scrollbar");
    }

    if (isSelected)
    {
        // value = -io::mouse::getWindowPosition().getRealPosition(pandora::mainWindow::get()->parameters.getSize()).y + foreground_scrollHeight + 2 - background_transform->position.y;
        //foreground_transform->position.y = mouse_position.y - selection_distance;
        value = -((mouse_position.y - background_transform->position.y - background_transform->size.Height + foreground_transform->size.Height / 2) / foreground_scrollHeight) * maximum;

        //logInfo("value " + std::to_string(value) + " mouse position " + std::to_string(mouse_position.y) + " background position " + std::to_string(background_transform->position.y) + " foreground position " + std::to_string(foreground_transform->position.y) + " selection distance " + std::to_string(selection_distance));
    }

    // logInfo(" Selection distance: " + std::to_string(selection_distance) + " Mouse position: " + std::to_string(mouse_position.x) + " " + std::to_string(mouse_position.y) + " Background position: " + std::to_string(background_position.x) + " " + std::to_string(background_position.y) + " Foreground position: " + std::to_string(foreground_transform->position.x) + " " + std::to_string(foreground_transform->position.y) + " Value: " + std::to_string(value));

    value -= io::mouse::getMouseScroll() * scroll_speed * step / 2;
    if (value < 0)
    {
        value = 0;
    }
    else if (value > maximum - step)
    {
        value = maximum - step;
    }

    percentage = value / maximum;
    foreground_transform->position.y = background_transform->position.y + background_transform->size.Height - 1 - (foreground_scrollHeight * percentage) - foreground_transform->size.Height;

    // logInfo("Value: " + std::to_string(value) + " Percentage: " + std::to_string(getPercentage()) + " Fake value: " + std::to_string(getValue()) + " Maximum: " + std::to_string(maximum) + " Foreground height: " + std::to_string(foreground_scrollHeight) + " Background height: " + std::to_string(background_transform->size.Height) + " Real percentage: " + std::to_string(percentage) + " Scroll speed: " + std::to_string(scroll_speed));
    if(prev_value == value) return;
    double diff = value - prev_value;
    prev_value = value;
    for (Object *object : binded_objects)
    {
        Transform *object_transform = object->Components().get<Transform>();
        object_transform->position.y += diff;
    }

}