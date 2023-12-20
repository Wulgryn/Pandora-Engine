#include "scenes.hpp"
#include "CONSOLE/fancyLog.hpp"
#include <vector>
#include "mainWindow.hpp"
#include "objects.hpp"
#include <algorithm>
#include "COMPONENTS/shader.hpp"
#include "UTILS/parameters.hpp"
#include "COMPONENTS/transform.hpp"

using namespace pandora;
using namespace std;
using namespace utils;

SceneID currentSceneID = -1;

vector<Scene *> &scenes::getScenesList()
{
    static vector<Scene *> _scenes;
    return _scenes;
}

Scene::Scene(int (*setup)(), int (*start)(io::Window &window), int (*update)(int frame, io::Window &window), int (*fixedUpdate)(int frame, io::Window &window))
{
    this->setup = setup;
    this->start = start;
    this->update = update;
    this->fixedUpdate = fixedUpdate;
    id = scenes::getScenesList().size();
    scenes::getScenesList().push_back(this);
}

int (*Scene::getSetup())()
{
    return setup;
}

int (*Scene::getStart())(io::Window &window)
{
    return start;
}

int (*Scene::getUpdate())(int frame, io::Window &window)
{
    return update;
}

int (*Scene::getFixedUpdate())(int frame, io::Window &window)
{
    return fixedUpdate;
}

std::vector<Object *> &Scene::getObjectsList()
{
    return objects;
}

SceneID Scene::getID()
{
    return id;
}

void Scene::addObject(Object *object)
{
    objects.push_back(object);
}

void Scene::removeObject(Object *object)
{
    vector<Object *>::iterator it = find(objects.begin(), objects.end(), object);
    if (it != objects.end())
    {
        objects.erase(it);
    }
}

void scenes::load(SceneID id)
{
    if (id == -1)
    {
        logError("Scene ID is invalid!");
        return;
    }
    if (id >= getScenesList().size())
    {
        logError("Scene ID is out of range!");
        return;
    }
    Scene *scene = getScenesList()[id];
    if (scene == nullptr)
    {
        logError("Scene is null!");
        return;
    }

    currentSceneID = id;

    if (scene->getSetup() == nullptr)
    {
        logWarning("Scene setup function is null!");
    }
    if (scene->getStart() == nullptr)
    {
        logWarning("Scene start function is null!");
    }
    if (scene->getUpdate() == nullptr)
    {
        logWarning("Scene update function is null!");
    }
    if (scene->getFixedUpdate() == nullptr)
    {
        logWarning("Scene fixed update function is null!");
    }
    io::Window *window = mainWindow::get();
    if (window == nullptr)
    {
        logError("Window is null!");
    }

    objects::getObjcectsList().clear();

    for (Object *object : scene->getObjectsList())
    {
        if (!object->followWindowResize)
        {
            Size size = object->Components().get<pandora::Transform>()->size.toWindowRate(pandora::mainWindow::get()->parameters.getSize());
            std::vector<float> vertices = {
                // positions                                                                // texture coords
                static_cast<float>(-size.Width), static_cast<float>(-size.Height), 0.0f,    0.0f, 0.0f, // bottom left
                static_cast<float>(size.Width), static_cast<float>(-size.Height), 0.0f,     1.0f, 0.0f,  // bottom right
                static_cast<float>(size.Width), static_cast<float>(size.Height), 0.0f,      1.0f, 1.0f,   // top right
                static_cast<float>(-size.Width), static_cast<float>(size.Height), 0.0f,     0.0f, 1.0f   // top left
            };
            object->Components().get<pandora::Shader>()->setVerticies(vertices);
        }
    }

    window->setSetupFunction(scene->getSetup());
    window->setStartFunction(scene->getStart());
    window->setUpdateFunction(scene->getUpdate());
    window->setFixedUpdateFunction(scene->getFixedUpdate());
    window->doSetup();
    window->doStart();
}

SceneID scenes::getCurrentSceneID()
{
    return currentSceneID;
}