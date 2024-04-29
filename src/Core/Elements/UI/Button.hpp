#pragma once
#include "../Object.hpp"

#include "../../Components/TextComponenet2D.hpp"
#include "../../../IO/InputHandler.hpp"

class Button : public Object
{
private:
    TextComponent2D* textComponent2D;
    bool isEntered = false;

    void CheckEvents(Window* window);
public:
    Parameters2D::Position* position;
    Parameters2D::Size* size;

    // HACK FEATURE: multiple trigger buttons
    /**
     * *=======================================================================
     * * DESCRIPTION: multiple trigger buttons
     * *=======================================================================
    **/
    Buttons triger_button = Buttons::LEFT;

    Event<Button*> OnClick;
    Event<Button*> OnPress;
    Event<Button*> OnRelease;
    Event<Button*> OnHover;
    Event<Button*> OnEnter;
    Event<Button*> OnLeave;

    Button();

    Button* operator=(std::string text);

    void Initialize() override;
    void Update() override;
};