#pragma once
#include "BaseComponent.hpp"
#include "../Elements/BaseObject.hpp"
#include "../Event.hpp"
#include "../Parameters.hpp"

#include <vector>

class CollisionComponent2D : public BaseComponent
{
private:
    BaseObject* hitbos_visibility_obj;
public:
    // @brief Event that is called when the object collides with another object
    // @param CollisionComponent2D* The collision component of this object
    // @param BaseObject* The object that this object collided with
    Event<CollisionComponent2D*, BaseObject*> OnCollide;

    // @brief If true, the object will collide with other objects, and can't pass through them
    bool isColliding = true;

    // @brief If true, the object will not move when colliding with other objects
    bool isStatic = true;


    CollisionComponent2D() = default;
    ~CollisionComponent2D();

    void Initialize() override;
    //void Update() override;

    Parameters2D::Vector2 CalcPos(Parameters2D::Vector2 vec);

    void SetColliderVisible(bool isVisible);
};

namespace CollisionHandler2D
{
    std::vector<BaseObject*>& GetGameObjects();
} // namespace CollisionHandler2D
