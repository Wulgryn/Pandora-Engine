#include "Parameters.hpp"
#include "Debug/Console.hpp"
#include "Components/Transform2D.hpp"

namespace Parameters2D
{

    Orientation::Orientation()
    {
        x_offset = 0;
        y_offset = 0;
    }

    Orientation::Orientation(OrientationType type)
    {
        this->type = type;
    }

    void Orientation::CalculateOffset(Size size)
    {
        switch (type)
        {
        case OrientationType::TOP_LEFT:
            x_offset = size.width / 2;
            y_offset = size.height / 2;
            break;
        case OrientationType::TOP_RIGHT:
            x_offset = -size.width / 2;
            y_offset = size.height / 2;
            break;
        case OrientationType::BOTTOM_LEFT:
            x_offset = size.width / 2;
            y_offset = -size.height / 2;
            break;
        case OrientationType::BOTTOM_RIGHT:
            x_offset = -size.width / 2;
            y_offset = -size.height / 2;
            break;
        case OrientationType::CENTER:
            x_offset = 0;
            y_offset = 0;
            break;
        case OrientationType::TOP_CENTER:
            x_offset = 0;
            y_offset = size.height / 2;
            break;
        case OrientationType::BOTTOM_CENTER:
            x_offset = 0;
            y_offset = -size.height / 2;
            break;
        case OrientationType::LEFT_CENTER:
            x_offset = size.width / 2;
            y_offset = 0;
            break;
        case OrientationType::RIGHT_CENTER:
            x_offset = -size.width / 2;
            y_offset = 0;
            break;
        default:
            x_offset = 0;
            y_offset = 0;
            break;
        }
    }

/**=======================================================================================================================*
 **                                                  REGION POSITION
 *========================================================================================================================*/
#pragma region POSITION
    
    Position::Position()
    {
        x = 0;
        y = 0;
    }

    Position::Position(double x, double y)
    {
        this->x = x;
        this->y = y;
    }

    Position::Position(ParametersApp::Position position)
    {
        x = position.d_x;
        y = position.d_y;
    }


    Position Position::Normalize(ParametersApp::Size size)
    {
        return Position((x + orientation.x_offset) / (size.d_width / 2) - 1, 1 - ((y + orientation.y_offset) / (size.d_height / 2)));
    }

    void Position::NormalizeThis(ParametersApp::Size size)
    {
        x = (x + orientation.x_offset ) / size.d_width - 1;
        y = 1 - ((y + orientation.y_offset ) / size.d_height);
    }

    // FIXME: Denormalize with orientation
    /**
     *& *===============================FIXIT===================================
     *& * DESCRIPTION: Denormalize the position with orientation calculated in
     *& * HINT: do the math
     *& *=======================================================================
    **/
    Position Position::Denormalize(ParametersApp::Size size)
    {
        return Position((x + 1) * size.d_width, (y + 1) * size.d_height);
    }

    void Position::DenormalizeThis(ParametersApp::Size size)
    {
        x = (x + 1) * size.d_width;
        y = (y + 1) * size.d_height;
    }

    void Position::CalcOrientation(Transform2D* transform)
    {
       orientation.type = transform->GetOrientationType();
       orientation.CalculateOffset(*transform->Size());
    }



    Position* Position::operator=(ParametersApp::Position position)
    {
        x = position.d_x;
        y = position.d_y;
        return this;
    }

    Position* Position::operator=(Position position)
    {
        x = position.x;
        y = position.y;
        return this;
    }

    Position* Position::operator=(double position)
    {
        x = position;
        y = position;
        return this;
    }

    Position* Position::operator+=(Position position)
    {
        x += position.x;
        y += position.y;
        return this;
    }

    Position* Position::operator+=(double position)
    {
        x += position;
        y += position;
        return this;
    }

    Position* Position::operator+=(Vector2 vector)
    {
        x += vector.x;
        y += vector.y;
        return this;
    }

/**=======================================================================================================================*
 **                                           END OF REGION POSITION
 *========================================================================================================================*/
#pragma endregion POSITION


/**=======================================================================================================================*
 **                                                  REGION SIZE
 *========================================================================================================================*/
#pragma region SIZE

    Size::Size()
    {
        width = 0;
        height = 0;
    }

    Size::Size(double width, double height)
    {
        this->width = width;
        this->height = height;
    }

    Size::Size(ParametersApp::Size size)
    {
        width = size.d_width;
        height = size.d_height;
    }

    Size Size::Normalize(ParametersApp::Size size)
    {
        return Size(width / (size.d_width / 2), height / (size.d_height / 2));
    }

    void Size::NormalizeThis(ParametersApp::Size size)
    {
        width = size.d_width / width;
        height = size.d_height / height;
        OnChange.Invoke(this);
    }

    Size Size::Denormalize(ParametersApp::Size size)
    {
        return Size(size.d_width * width, size.d_height * height);
    }

    void Size::DenormalizeThis(ParametersApp::Size size)
    {
        width = size.d_width * width;
        height = size.d_height * height;
        OnChange.Invoke(this);
    }

    Size* Size::SetWidth(double width)
    {
        this->width = width;
        OnChange.Invoke(this);
        return this;
    }

    Size* Size::SetHeight(double height)
    {
        this->height = height;
        OnChange.Invoke(this);
        return this;
    }

    Size* Size::AddWidth(double width)
    {
        this->width += width;
        OnChange.Invoke(this);
        return this;
    }

    Size* Size::AddHeight(double height)
    {
        this->height += height;
        OnChange.Invoke(this);
        return this;
    }

    Size* Size::operator=(ParametersApp::Size size)
    {
        width = size.d_width;
        height = size.d_height;
        OnChange.Invoke(this);
        return this;
    }

    Size* Size::operator=(Size size)
    {
        width = size.width;
        height = size.height;
        OnChange.Invoke(this);
        return this;
    }

    Size* Size::operator=(double size)
    {
        width = size;
        height = size;
        OnChange.Invoke(this);
        return this;
    }

    Size* Size::operator+=(Size size)
    {
        width += size.width;
        height += size.height;
        OnChange.Invoke(this);
        return this;
    }

    Size* Size::operator+=(double size)
    {
        width += size;
        height += size;
        OnChange.Invoke(this);
        return this;
    }

    double& Size::operator[](int index)
    {
        switch (index)
        {
        case 0:
            return width;
        case 1:
            return height;
        default:
            return width;
        }
        
    }
    
/**=======================================================================================================================*
 **                                           END OF REGION SIZE
 *========================================================================================================================*/
#pragma endregion SIZE

/**=======================================================================================================================*
 **                                                  REGION ROTATION
 *========================================================================================================================*/
#pragma region ROTATION

    Rotation::Rotation()
    {
        z = 0;
    }

    Rotation::Rotation(double z)
    {
        this->z = z;
    }

/**=======================================================================================================================*
 **                                           END OF REGION ROTATION
 *========================================================================================================================*/
#pragma endregion ROTATION

/**=======================================================================================================================*
 **                                                  REGION SCALE
 *========================================================================================================================*/
#pragma region SCALE

    Scale::Scale()
    {
        x = 0;
        y = 0;
    }

    Scale::Scale(double x, double y)
    {
        this->x = x;
        this->y = y;
    }

    Scale* Scale::operator=(double scale)
    {
        x = scale;
        y = scale;
        return this;
    }

/**=======================================================================================================================*
 **                                           END OF REGION SCALE
 *========================================================================================================================*/
#pragma endregion SCALE

/**=======================================================================================================================*
 **                                                  REGION VECTOR2
 *========================================================================================================================*/
#pragma region VECTOR2

    Vector2::Vector2()
    {
        x = 0;
        y = 0;
    }

    Vector2::Vector2(double x, double y)
    {
        this->x = x;
        this->y = y;
    }

    Vector2* Vector2::operator=(double value)
    {
        x = value;
        y = value;
        return this;
    }

    Vector2* Vector2::operator=(Vector2 vector)
    {
        x = vector.x;
        y = vector.y;
        return this;
    }

    Vector2* Vector2::operator+=(Vector2 vector)
    {
        x += vector.x;
        y += vector.y;
        return this;
    }

    Vector2* Vector2::operator+=(double value)
    {
        x += value;
        y += value;
        return this;
    }

/**=======================================================================================================================*
 **                                           END OF REGION VECTOR2
 *========================================================================================================================*/
#pragma endregion VECTOR2
 
}
