#include "button.hpp"
#include "IO/mouse.hpp"
#include "PANDORA/COMPONENTS/image.hpp"
#include "PANDORA/COMPONENTS/transform.hpp"
#include "PANDORA/mainWindow.hpp"
#include "CONSOLE/fancyLog.hpp"

using namespace pandora;
using namespace utils;
using namespace io;

Button::Button() : UIElement()
{
    
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
    Position  mousePos = mouse::getWindowPosition();
    Position pos = components->get<Transform>()->position.getRealPosition(mainWindow::get()->parameters.getSize());
    Size size = components->get<Transform>()->size;
    if(pos.x < mousePos.x && pos.x + size.Width > mousePos.x && pos.y - size.Height < mousePos.y && pos.y > mousePos.y )
    {
        isOnHover = true;
        if(onMouseDown != nullptr && mouse::getMouseButton(MouseButton::LEFT)) onMouseDown();
        bool isMouseReleased = mouse::getMouseButtonReleased(MouseButton::LEFT);
        if(onClick != nullptr && isMouseReleased) onClick();
        if(onHover != nullptr) onHover();

    }
    else if(isOnHover && onHoverExit != nullptr)
    {
        isOnHover = false;
        onHoverExit();
    }
    //logInfo("mousePos: " + std::to_string(mousePos.x) + " " + std::to_string(mousePos.y) + " pos: " + std::to_string(pos.x) + " " + std::to_string(pos.y) + " size: " + std::to_string(size.Width) + " " + std::to_string(size.Height));
    
}