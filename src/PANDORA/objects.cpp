#include "objects.hpp"

#include <algorithm>
#include "CONSOLE/fancyLog.hpp"

using namespace std;
using namespace pandora;

vector<Object *> &getObjcectsList()
{
    static vector<Object *> objects_list;
    return objects_list;
}

void objects::render()
{
    for (Object *object : getObjcectsList()) {
        //logInfo("Initializing object: " + object->name);
        object->Components().initComponenets();
    }
}

Object::Object()
{
    getObjcectsList().push_back(this);
}

Object::~Object()
{
    vector<pandora::Object *>::iterator it = find(getObjcectsList().begin(), getObjcectsList().end(), this);
    if (it != getObjcectsList().end()) {
        getObjcectsList().erase(it);
    }
}

Components &Object::Components()
{
    return components;
}