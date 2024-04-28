#include "CollisionComponent2D.hpp"
#include "Transform2D.hpp"
#include "Texture2D.hpp"
#include "Debug/Console.hpp"

#include <math.h>
#include "ShaderComponent2D.hpp"

using namespace Parameters2D;

// TODO collision detection /update and /calc call
// * IMPORTANT: Maybe on move push the object but not the neighour of that object so obj1 pushes obj2 but obj2 doesn't push obj3 <- only happens on /update check

std::vector<BaseObject*>& CollisionHandler2D::GetGameObjects()
{
    static std::vector<BaseObject*> gameObjects;
    return gameObjects;
}

CollisionComponent2D::~CollisionComponent2D()
{
    for (int i = 0; i < CollisionHandler2D::GetGameObjects().size(); i++)
    {
        if (CollisionHandler2D::GetGameObjects()[i] == componenetHandler->GetParentObject())
        {
            CollisionHandler2D::GetGameObjects().erase(CollisionHandler2D::GetGameObjects().begin() + i);
            break;
        }
    }
}

void CollisionComponent2D::Initialize()
{
    CollisionHandler2D::GetGameObjects().push_back(componenetHandler->GetParentObject());

    hitbos_visibility_obj = new BaseObject();
    hitbos_visibility_obj->AddComponenetByReference(componenetHandler->GetParentObject()->GetComponent<Transform2D>());
    Texture2D* tex = hitbos_visibility_obj->AddComponent<Texture2D>();
    tex->SetColor(new Color(Colors::RED));
    tex->GetColor()->a = 0;
    tex->drawType = DrawType::OUTLINE;
    hitbos_visibility_obj->AddComponent<ShaderComponent2D>();
    componenetHandler->GetParentObject()->GetParentWindow()->AddObject(hitbos_visibility_obj);
}

//void CollisionComponent2D::Update()
//{
//    for(int i = 0; i < CollisionHandler2D::GetGameObjects().size(); i++)
//    {
//        BaseObject* object = CollisionHandler2D::GetGameObjects()[i];
//        if(object == componenetHandler->GetParentObject()) continue;
//
//        Transform2D* transform = object->GetComponent<Transform2D>();
//        if(!transform) continue;
//
//        CollisionComponent2D* collision = object->GetComponent<CollisionComponent2D>();
//        if(!collision) continue;
//        if(!isColliding || !collision->isColliding) continue;
//
//        Parameters2D::Position* pos = transform->Position();
//        Parameters2D::Size* size = transform->Size();
//
//        Parameters2D::Position* thisPos = componenetHandler->GetComponent<Transform2D>()->Position();
//        Parameters2D::Size* thisSize = componenetHandler->GetComponent<Transform2D>()->Size();
//        
//        double centerX = pos->x + size->width / 2;
//        double centerY = pos->y + size->height / 2;
//
//        double thisCenterX = thisPos->x + thisSize->width / 2;
//        double thisCenterY = thisPos->y + thisSize->height / 2;
//
//        double dX = centerX - thisCenterX;
//        double dY = centerY - thisCenterY;
//
//        if(abs(dX) < size->width / 2 + thisSize->width / 2 && abs(dY) < size->height / 2 + thisSize->height / 2)
//        {
//            if(collision->isStatic)
//            {
//                if(thisPos->y + thisSize->height > pos->y && thisPos->y < pos->y + size->height) thisPos->x += dX - (thisSize->width / 2 + size->width / 2);
//                if(thisPos->x + thisSize->width > pos->x && thisPos->x < pos->x + size->width) thisPos->y += dY - (thisSize->height / 2 + size->height / 2);
//                continue;
//            }
//
//            if(thisPos->y + thisSize->height > pos->y && thisPos->y < pos->y + size->height) 
//            {
//                
//                //vec.x = dX - dX1 + vec.x / 2;
//                //pos->x -= vec.x;
//            }
//            if(thisPos->x + thisSize->width > pos->x && thisPos->x < pos->x + size->width)
//            {
//                //vec.y = dY - dY1 + vec.y / 2;
//                //pos->y -= vec.y;
//            }
//        }
//    }
//}

// BUG IMPORTANT: So the 0.5 px movement
/**
 * *=======================================================================
 * * DESCRIPTION: This can lead to 1 px off render because as value it's okay, but the render is in int
 * *=======================================================================
**/

Vector2 CollisionComponent2D::CalcPos(Vector2 vec)
{
    for(int i = 0; i < CollisionHandler2D::GetGameObjects().size(); i++)
    {
        BaseObject* object = CollisionHandler2D::GetGameObjects()[i];
        if(object == componenetHandler->GetParentObject()) continue;

        Transform2D* transform = object->GetComponent<Transform2D>();
        if(!transform) continue;

        CollisionComponent2D* collision = object->GetComponent<CollisionComponent2D>();
        if(!collision) continue;
        if(!isColliding || !collision->isColliding) continue;

        Parameters2D::Position* pos = transform->Position();
        Parameters2D::Size* size = transform->Size();

        Parameters2D::Position* thisPos = componenetHandler->GetComponent<Transform2D>()->Position();
        Parameters2D::Size* thisSize = componenetHandler->GetComponent<Transform2D>()->Size();
        
        double centerX = pos->x + size->width / 2;
        double centerY = pos->y + size->height / 2;

        double thisCenterX = thisPos->x + thisSize->width / 2;
        double thisCenterY = thisPos->y + thisSize->height / 2;

        double dX = centerX - (thisCenterX + vec.x);
        double dY = centerY - (thisCenterY + vec.y);

        double dX1 = centerX - thisCenterX;
        double dY1 = centerY - thisCenterY;

        if(abs(dX) < size->width / 2 + thisSize->width / 2 && abs(dY) < size->height / 2 + thisSize->height / 2)
        {
            if(collision->isStatic)
            {
                if(thisPos->y + thisSize->height > pos->y && thisPos->y < pos->y + size->height) vec.x = dX - dX1 + vec.x;
                if(thisPos->x + thisSize->width > pos->x && thisPos->x < pos->x + size->width) vec.y = dY - dY1 + vec.y;
                OnCollide.Invoke(this, object);
                continue;
            }
            // HACK CAUTION: Make pushable
            /**
             *^  *=======================================================================
             *^  * DESCRIPTION: DO IT
             *^  *=======================================================================
            **/
            //Vector2 otherVec;
            //if(thisPos->y + thisSize->height > pos->y && thisPos->y < pos->y + size->height) 
            //{
            //    //otherVec.x = vec.x;
            //    vec.x = dX - dX1 + vec.x;
            //    pos->x -= vec.x + 1;
            //}
            //if(thisPos->x + thisSize->width > pos->x && thisPos->x < pos->x + size->width)
            //{
            //    //otherVec.y = vec.y;
            //    vec.y = dY - dY1 + vec.y;
            //    pos->y -= vec.y + 1;
            //}
            //BUG: This move fn is causing recursive behaviour so on bigger object count it will be laggy
            //Vector2 thisVec = transform->Move(otherVec);
            //vec.x = thisVec.x;
            //vec.y = thisVec.y;
        }
    }
    return vec;
}

void CollisionComponent2D::SetColliderVisible(bool isVisible)
{
    if(isVisible) hitbos_visibility_obj->GetComponent<Texture2D>()->GetColor()->a = 255;
    else hitbos_visibility_obj->GetComponent<Texture2D>()->GetColor()->a = 0;
}