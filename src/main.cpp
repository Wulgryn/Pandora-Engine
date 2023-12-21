#include "DLL/init.hpp"
#include "IO/window.hpp"
#include "PANDORA/pandora.hpp"
#include <vector>
#include <iostream>
#include <string>
#include <cmath>
#include "CONSOLE/fancyLog.hpp"
#include "UTILS/timer.hpp"
#include "test.hpp"
using namespace std;
using namespace io;
using namespace utils;

Scene scene(test_setup, test_start, test_update, test_fixedUpdate);

Object obj;
Object obj1(scene.getID());

int setup()
{
    obj.Components().add<Shader>();
    obj.Components().add<Transform>();
    obj.Components().add<Image>();
    obj.name = "1";
    //obj.addToScene(scene.getID());

    obj.Components().get<Image>()->setTexture(textures::loadTexture("assets/textures/test.png"));
    obj.Components().get<Shader>()->copy(Shader(shaders::textureVertexShader2D(), shaders::textureFragmentShader2D()));

    obj1.Components().add<Shader>();
    obj1.Components().add<Transform>();
    obj1.Components().add<Image>();
    obj.name = "2";

    
    
    //glfwSwapInterval(0);
    return 0;
}
int start(Window &window)
{
    window.log.logMainThreadTime = true;
    window.log.logFPS = true;

    window.keys.delay = false;
    return 0;
}

int update(int frame, Window &window)
{
    Transform *transform = obj.Components().get<Transform>();
    
    if(window.events.getKey(Keycode::A))transform->position.x -= 100 * window.deltaTime();
    if(window.events.getKey(Keycode::D))transform->position.x += 100 * window.deltaTime();
    if(window.events.getKey(Keycode::W))transform->position.y += 100 * window.deltaTime();
    if(window.events.getKey(Keycode::S))transform->position.y -= 100 * window.deltaTime();
    if(window.events.getKey(Keycode::Q))scenes::load(0);
    return 0;
}

int main(int argc, char **argv)
{
    glfwWindowHint(GLFW_DOUBLEBUFFER, GLFW_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE);

    glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GLFW_TRUE);

    PandoraEngine::init();
    
    Window window(1000, 1000, "PandoraEngine");
    //mainWindow::set(&window);
    //window.setFixedUpdateFunction(update);
    //window.setStartFunction(start);
    //window.setSetupFunction(setup);
    //window.setTargetFPS(144);
    //window.setTargetTPS(30);
    //window.properties.setDecorated(false);
    window.start();
    return 0;
}