#include "objects.hpp"

#include <algorithm>
#include "CONSOLE/fancyLog.hpp"
#include "scenes.hpp"

using namespace std;
using namespace pandora;

vector<Object *> &objects::getObjectsList()
{
    static vector<Object *> objects_list;
    return objects_list;
}

void objects::render()
{
    if (scenes::getScenesList().size() > 0 && scenes::getCurrentSceneID() != -1)
        for (Object *object : scenes::getScenesList()[scenes::getCurrentSceneID()]->getObjectsList())
        {
            object->Components().initComponenets();
        }
    for (Object *object : getObjectsList())
    {
        // logInfo("Initializing object: " + object->name);
        object->Components().initComponenets();
    }
}

Object::Object()
{
    objects::getObjectsList().push_back(this);
}

Object::Object(SceneID sceneID)
{
    if (sceneID >= scenes::getScenesList().size())
    {
        logError("SceneID out of range");
        return;
    }
    vector<SceneID>::iterator it = find(scene_IDs.begin(), scene_IDs.end(), sceneID);
    if (it != scene_IDs.end())
    {
        logError("Object already in scene");
        return;
    }
    scene_IDs.push_back(sceneID);
    scenes::getScenesList()[sceneID]->getObjectsList().push_back(this);
}

Object::~Object()
{
    vector<pandora::Object *>::iterator it = find(objects::getObjectsList().begin(), objects::getObjectsList().end(), this);
    if (it != objects::getObjectsList().end())
    {
        objects::getObjectsList().erase(it);
    }
}

Components &Object::Components()
{
    return components;
}

void Object::addToScene(SceneID sceneID)
{
    if (sceneID >= scenes::getScenesList().size())
    {
        logError("SceneID out of range");
        return;
    }
    scenes::getScenesList()[sceneID]->getObjectsList().push_back(this);
}

void Object::removeFromScene(SceneID sceneID)
{
    if (sceneID >= scenes::getScenesList().size())
    {
        logError("SceneID out of range");
        return;
    }
    vector<Object *>::iterator it = find(scenes::getScenesList()[sceneID]->getObjectsList().begin(), scenes::getScenesList()[sceneID]->getObjectsList().end(), this);
    if (it != scenes::getScenesList()[sceneID]->getObjectsList().end())
    {
        scenes::getScenesList()[sceneID]->getObjectsList().erase(it);
    }
}