#include "ObjectsHandler.hpp"
#include "BaseObject.hpp"
#include "Debug/Console.hpp"

#include <vector>

using namespace std;

ObjectsHandler::ObjectsHandler(Window* window)
{
    this->window = window;
}

void ObjectsHandler::AddObject(BaseObject* object)
{
    objects.push_back(object);
    object->SetObjectsHandler(this);
    object->SetParentWindow(window);
    object->Initialize();
}