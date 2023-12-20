#pragma once
#include "DLL/dll.hpp"
#include "COMPONENTS/components.hpp"
#include <vector>
#include <string>
namespace pandora
{
    typedef unsigned int SceneID;
    enum class ObjectType
    {
        SCENE,
        UI
    };
    class DLL Object
    {
    private:
        pandora::Components components;
        std::vector<SceneID> scene_IDs;
    public:
        std::string name = "Object";
        //if the window resized, the object will be resized too. To stay
        bool followWindowResize = false;

        Object();
        Object(SceneID sceneID);
        ~Object();

        pandora::Components &Components();

        void addToScene(SceneID sceneID);
        void removeFromScene(SceneID sceneID);
    };

    namespace objects
    {
        DLL std::vector<Object *> &getObjcectsList();
        DLL void render();
        DLL void add(Object *object);
    } // namespace objects
    
}