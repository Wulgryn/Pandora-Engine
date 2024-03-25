#include "../../Core/Components/ComponentsHandler.hpp"

#include <vector>

class BaseObject : public ComponentsHandler
{
public:
    bool Immortal = false;

    BaseObject();

    virtual void Update();

    void Destroy();
};