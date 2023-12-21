#pragma once
#include "DLL/dll.hpp"
#include "IO/window.hpp"
#include "objects.hpp"

namespace pandora
{
    typedef unsigned int SceneID;
    class DLL Scene
    {
    private:
        SceneID id = -1;
        int (*setup)();
        int (*start)(io::Window &window);
        int (*fixedUpdate)(int frame, io::Window &window);
        int (*update)(int frame, io::Window &window);
        std::vector<Object *> objects;

    public:
        Scene(int (*setup)(), int (*start)(io::Window &window), int (*fixedUpdate)(int frame, io::Window &window), int (*update)(int frame, io::Window &window));

        int (*getSetup())();
        int (*getStart())(io::Window &window);
        int (*getUpdate())(int frame, io::Window &window);
        int (*getFixedUpdate())(int frame, io::Window &window);

        std::vector<Object *> &getObjectsList();

        SceneID getID();

        void addObject(Object *object);
        void removeObject(Object *object);
    };
    namespace scenes
    {
        DLL void load(SceneID id);
        DLL std::vector<Scene *> &getScenesList();
        DLL SceneID getCurrentSceneID();
    }
}