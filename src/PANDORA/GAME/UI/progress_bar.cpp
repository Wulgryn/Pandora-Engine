#include "progress_bar.hpp"
#include "PANDORA/COMPONENTS/image.hpp"
#include "PANDORA/COMPONENTS/shader.hpp"
#include "PANDORA/COMPONENTS/transform.hpp"
#include "UTILS/random.hpp"
#include <algorithm>
#include <vector>
#include "CONSOLE/fancyLog.hpp"

using namespace pandora;
using namespace utils;
using namespace std;

ProgressBar::ProgressBar() : UIElement()
{
    Transform* foreground_transform = ui_object.Components().get<Transform>();
    foreground_transform->size.Height = 40;
    foreground_transform->size.Width = 250;
    foreground_transform->position.x = 200;
    foreground_transform->position.y = 200;

    background.Components().add<UIElement>(this);
    background.Components().add<Image>()->color = {random::getByte(0,255),random::getByte(0,255),random::getByte(0,255)};
    background.Components().add<Shader>();
    Transform* background_transform = background.Components().add<Transform>();

    background_transform->size.Height = foreground_transform->size.Height + 10;
    background_transform->size.Width = foreground_transform->size.Width + 10;
    background_transform->position.x = foreground_transform->position.x - 5;
    background_transform->position.y = foreground_transform->position.y - 5;

    vector<pandora::Object *>::iterator ui_it = find(objects::getObjectsList().begin(), objects::getObjectsList().end(), &ui_object);
    vector<pandora::Object *>::iterator background_it = find(objects::getObjectsList().begin(), objects::getObjectsList().end(), &background);
    std::iter_swap(ui_it, background_it);
}

double ProgressBar::getPercentage()
{
    return percentage;
}

void ProgressBar::setPercentage(double percentage)
{
    this->percentage = percentage;
    value = (percentage / 100) * maximum;
}

void ProgressBar::stepUp()
{
    value += step;
    if(value > maximum) value = maximum;
}

void ProgressBar::stepDown()
{
    value -= step;
    if(value < minimum) value = minimum;
}

void ProgressBar::setBackgroundColor(utils::Color color)
{
    background.Components().get<Image>()->color = color;
}

void ProgressBar::setOnProgressChange(void (*onProgressChange)())
{
    this->onProgressChange = onProgressChange;
}

void ProgressBar::init(Components* components)
{
    percentage = (value / maximum) * 100;
    if (value != last_value)
    {
        if (onProgressChange != nullptr)
            onProgressChange();
        last_value = value;
    }

    Transform* foreground_transform = ui_object.Components().get<Transform>();
    foreground_transform->size.Width = (percentage / 100) * (background.Components().get<Transform>()->size.Width - 10);

    
}