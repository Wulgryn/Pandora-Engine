#include "button.hpp"
#include "PANDORA/COMPONENTS/image.hpp"
#include "UTILS/random.hpp"
#include "IO/mouse.hpp"
#include "PANDORA/COMPONENTS/transform.hpp"
#include "PANDORA/mainWindow.hpp"

using namespace pandora;
using namespace utils;
using namespace io;

Button::Button() : UIElement()
{
    ui_object.Components().get<Image>()->color = {random::getByte(0,255),random::getByte(0,255),random::getByte(0,255)};
}

Components* Button::getComponents()
{
    return &ui_object.Components();
}

void Button::setOnClick(void (*onClick)())
{
    this->onClick = onClick;
}

void Button::setOnMouseDown(void (*onMouseDown)())
{
    this->onMouseDown = onMouseDown;
}

void Button::setOnHover(void (*onHover)())
{
    this->onHover = onHover;
}

void Button::setOnHoverExit(void (*onHoverExit)())
{
    this->onHoverExit = onHoverExit;
}

void Button::init(Components* components)
{
    Position  mousePos = mouse::getWindowPos();
    Position pos = components->get<Transform>()->position.getRealPosition(mainWindow::get()->parameters.getSize());
    Size size = components->get<Transform>()->size;
    if(pos.x < mousePos.x && pos.x + size.Width > mousePos.x && pos.y - size.Height < mousePos.y && pos.y > mousePos.y)
    {
        isOnHover = true;
        if(onMouseDown != nullptr && mouse::getMouseButton(MouseButton::LEFT)) onMouseDown();
        if(onClick != nullptr && mouse::getMouseButtonReleased(MouseButton::LEFT)) onClick();
        if(onHover != nullptr) onHover();

    }
    else if(isOnHover && onHoverExit != nullptr)
    {
        isOnHover = false;
        onHoverExit();
    }
}