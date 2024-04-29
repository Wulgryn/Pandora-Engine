#include "Button.hpp"

using namespace Parameters2D;

Button::Button()
{
    textComponent2D = AddComponent<TextComponent2D>();
    Transform2D* transform = GetComponent<Transform2D>();
    transform->SetOrientationType(OrientationType::TOP_LEFT);
    position = transform->Position();
    size = transform->Size();

    size->width = 100;
    size->height = 50;
    textComponent2D->SetText("Button :)");
}

Button* Button::operator=(std::string text)
{
    textComponent2D->SetText(text);
    return this;
}

void Button::Initialize()
{
    Object::Initialize();
    GetParentWindow()->OnRender += Method<void,Window*>(&Button::CheckEvents, this);
}

void Button::CheckEvents(Window* window)
{
    ParametersApp::Position mousePosition = GetParentWindow()->GetInput()->GetMousePosition();
    InputHandler* inputHandler = GetParentWindow()->GetInput();
    if(mousePosition.d_x >= position->x && mousePosition.d_x <= position->x + size->width &&
       mousePosition.d_y >= position->y && mousePosition.d_y <= position->y + size->height)
    {
        if(!isEntered) 
        {
            isEntered = true;
            OnEnter.Invoke(this);
        }
        OnHover.Invoke(this);

        if(inputHandler->GetButtonPressed(triger_button)) OnClick.Invoke(this);
        if(inputHandler->GetButtonDown(triger_button)) OnPress.Invoke(this);
        if(inputHandler->GetButtonReleased(triger_button)) OnRelease.Invoke(this);
        
    }
    else if(isEntered)
    {
        isEntered = false;
        OnLeave.Invoke(this);
    }
}

void Button::Update()
{
    Object::Update();
    Size textSize = textComponent2D->GetSize();
    textComponent2D->position.x = position->x + (size->width - textSize.width) / 2;
    textComponent2D->position.y = position->y + (size->height - textSize.height) / 2;
}