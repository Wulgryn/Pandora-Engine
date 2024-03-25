#include "ObjectsHandler.hpp"
#include "BaseObject.hpp"

#include <vector>

using namespace std;

ObjectsHandler::ObjectsHandler()
{
    
}

void ObjectsHandler::AddObject(BaseObject* object)
{
    objects.push_back(object);
}
