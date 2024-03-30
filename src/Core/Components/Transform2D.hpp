#pragma on
#include "BaseComponent.hpp"
#include "../Parameters.hpp"

class Transform2D : public BaseComponent
{
private:
    Parameters2D::Position position;
    Parameters2D::Rotation rotation;
    Parameters2D::Scale scale;
    Parameters2D::Size size;
    Parameters2D::OrentationType orentationType = Parameters2D::OrentationType::TOP_LEFT;
public:
    Transform2D();

    void SetPosition(double x, double y);
    void SetPosition(Parameters2D::Position pos);

    void SetRotation(double z);
    void SetRotation(Parameters2D::Rotation rot);

    void SetScale(double x, double y);
    void SetScale(Parameters2D::Scale scl);

    void SetSize(double width, double height);
    void SetSize(Parameters2D::Size size);

    void SetOrentationType(Parameters2D::OrentationType type);
    Parameters2D::OrentationType GetOrentationType();

    Parameters2D::Position* Position();
    Parameters2D::Rotation* Rotation();
    Parameters2D::Scale* Scale();
    Parameters2D::Size* Size();

    void Destroy();
};