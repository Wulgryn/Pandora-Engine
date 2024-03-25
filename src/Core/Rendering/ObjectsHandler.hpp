#include <vector>

class BaseObject;

class ObjectsHandler
{
protected:
    std::vector<BaseObject*> objects;
    std::vector<BaseObject*> renderable_objects;
public:
    ObjectsHandler();
    void AddObject(BaseObject* object);
};


namespace Objects
{
    void AddObject(BaseObject* object);
}