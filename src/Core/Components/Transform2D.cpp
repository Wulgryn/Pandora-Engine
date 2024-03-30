#include "Transform2D.hpp"
#include "ComponentsHandler.hpp"

using namespace Parameters2D;

Transform2D::Transform2D()
{
    position = Parameters2D::Position();
    rotation = Parameters2D::Rotation();
    scale = Parameters2D::Scale();
    size = Parameters2D::Size(100,100);
    position.CalcOrientation(this);
}

void Transform2D::SetPosition(double x, double y)
{
    position = Parameters2D::Position(x, y);
}

void Transform2D::SetPosition(Parameters2D::Position pos)
{
    position = pos;
}

void Transform2D::SetRotation(double z)
{
    rotation = Parameters2D::Rotation(z);
}

void Transform2D::SetRotation(Parameters2D::Rotation rot)
{
    rotation = rot;
}

void Transform2D::SetScale(double x, double y)
{
    scale = Parameters2D::Scale(x, y);
}

void Transform2D::SetScale(Parameters2D::Scale scl)
{
    scale = scl;
}

void Transform2D::SetSize(double width, double height)
{
    size = Parameters2D::Size(width, height);
}

void Transform2D::SetSize(Parameters2D::Size size)
{
    this->size = size;
}

void Transform2D::SetOrentationType(Parameters2D::OrentationType type)
{
    orentationType = type;
    position.CalcOrientation(this);
}

Parameters2D::OrentationType Transform2D::GetOrentationType()
{
    return orentationType;
}

Parameters2D::Position* Transform2D::Position()
{
    return &position;
}

Parameters2D::Rotation* Transform2D::Rotation()
{
    return &rotation;
}

Parameters2D::Scale* Transform2D::Scale()
{
    return &scale;
}

Parameters2D::Size* Transform2D::Size()
{
    return &size;
}


void Transform2D::Destroy()
{
    delete this;
}


