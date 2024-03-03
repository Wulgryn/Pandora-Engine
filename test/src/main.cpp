#include "DLL/init.hpp"
#include "PANDORA/pandora.hpp"
#include "IO/window.hpp"
#include "IO/mouse.hpp"
#include "CONSOLE/fancyLog.hpp"
#include "UTILS/parameters.hpp"
using namespace io;
using namespace std;

ProgressBarObject progressBar;
ButtonObject btn_1;
ButtonObject btn_2;
ScrollbarObject scrollbar;
Object obj;

SwitchObject switch_1;

CheckBoxObject checkbox;

//pandora::Texture* text_test = new pandora::Texture("assets/textures/test.png");

int setup()
{
    return 0;
}

int start(Window& window)
{
    window.setBackgroundColor(utils::Color(0.2f, 0.2f, 0.2f, 1.0f));

    progressBar = new ProgressBar();
    progressBar->maximum = 200;
    progressBar->setPercentage(28.12345);
    progressBar->setOnProgressChange([](){
        logInfo("Progress: " + std::to_string(progressBar->value) + " " + std::to_string(progressBar->getPercentage()));
    });
    btn_1 = new Button();
    btn_1->setOnClick([](){
        progressBar->value += 10;
    });
    btn_1->getComponents()->get<Transform>()->position.y = 300;
    btn_1->getComponents()->get<Transform>()->size = {100, 100};
    btn_2 = new Button();
    btn_2->setOnMouseDown([](){
        progressBar->stepDown(); 
    });
    btn_2->getComponents()->get<Transform>()->size = {100, 100};

    obj.Components().add<Transform>()->size = {50, 50};
    obj.Components().get<Transform>()->position.x = 400;
    //obj.Components().add<Image>()->setTexture(text_test);
    obj.Components().add<Shader>(new Shader(shaders::textureVertexShader2D(),shaders::textureFragmentShader2D()));


    scrollbar = new Scrollbar();

    scrollbar->bindObject(&obj);

    scrollbar->maximum = 600;
    scrollbar->step = 10;
    scrollbar->scroll_speed = 0.2;

    switch_1 = new Switch();

    scrollbar->bindObject(switch_1->getBackground());
    scrollbar->bindObject(switch_1->getForeground());

    checkbox = new CheckBox();

    return 0;
}

int update(int fps, Window& window)
{
    //logInfo("FPS: " + std::to_string(fps));
    //if(window.events.getMouseButtonReleased(MouseButton::LEFT))
    //{
    //    logInfo("Mouse released");
    //}
    return 0;
}


int main(int argc, char const *argv[])
{
    PandoraEngine::init();
    Window window(800, 600, "Pandora");
    window.setSetupFunction(setup);
    window.setStartFunction(start);
    window.setTargetTPS(30);
    window.setUpdateFunction(update);

    window.start();
    return 0;
}
