#include "Transform2D.hpp"
#include "ComponentsHandler.hpp"

using namespace Parameters2D;

Transform2D::Transform2D()
{
    position = Position();
    rotation = Rotation();
    scale = Scale();
}

void Transform2D::SetPosition(double x, double y)
{
    position = Position(x, y);
}

void Transform2D::SetPosition(Position pos)
{
    position = pos;
}

void Transform2D::SetRotation(double z)
{
    rotation = Rotation(z);
}

void Transform2D::SetRotation(Rotation rot)
{
    rotation = rot;
}

void Transform2D::SetScale(double x, double y)
{
    scale = Scale(x, y);
}

void Transform2D::SetScale(Scale scl)
{
    scale = scl;
}

void Transform2D::Destroy()
{
    delete this;
}
