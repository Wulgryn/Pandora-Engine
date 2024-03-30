#pragma once
#include <vector>

class BaseObject;
class Window;
class ObjectsHandler
{
private:
    Window* window;
protected:
    std::vector<BaseObject*> objects;
    std::vector<BaseObject*> renderable_objects;
public:
    ObjectsHandler(Window* window);
    void AddObject(BaseObject* object);

    Window* GetWindow() { return window; }
};

namespace Objects
{
    void AddObject(BaseObject* object);
}

enum ObjectTags
{
    None = 0b00000000,
    Immortal = 0b00000001,
    Renderable = 0b00000010
};