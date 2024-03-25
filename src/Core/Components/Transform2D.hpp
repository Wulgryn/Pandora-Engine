#include "BaseComponent.hpp"
#include "Core/Parameters.hpp"

class Transform2D : public BaseComponent
{
private:
    Parameters2D::Position position;
    Parameters2D::Rotation rotation;
    Parameters2D::Scale scale;
public:
    Transform2D();

    void SetPosition(double x, double y);
    void SetPosition(Parameters2D::Position pos);

    void SetRotation(double z);
    void SetRotation(Parameters2D::Rotation rot);

    void SetScale(double x, double y);
    void SetScale(Parameters2D::Scale scl);

    void Destroy();
};