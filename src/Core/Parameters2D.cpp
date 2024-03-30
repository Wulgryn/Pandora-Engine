#include "Parameters.hpp"
#include "Debug/Console.hpp"
#include "Components/Transform2D.hpp"

namespace Parameters2D
{

    Orentation::Orentation()
    {
        x_offset = 0;
        y_offset = 0;
    }

    Orentation::Orentation(OrentationType type)
    {
        this->type = type;
    }

    void Orentation::CalculateOffset(Size size)
    {
        switch (type)
        {
        case OrentationType::TOP_LEFT:
            x_offset = size.width / 2;
            y_offset = size.height / 2;
            break;
        case OrentationType::TOP_RIGHT:
            x_offset = -size.width / 2;
            y_offset = size.height / 2;
            break;
        case OrentationType::BOTTOM_LEFT:
            x_offset = size.width / 2;
            y_offset = -size.height / 2;
            break;
        case OrentationType::BOTTOM_RIGHT:
            x_offset = -size.width / 2;
            y_offset = -size.height / 2;
            break;
        case OrentationType::CENTER:
            x_offset = 0;
            y_offset = 0;
            break;
        case OrentationType::TOP_CENTER:
            x_offset = 0;
            y_offset = size.height / 2;
            break;
        case OrentationType::BOTTOM_CENTER:
            x_offset = 0;
            y_offset = -size.height / 2;
            break;
        case OrentationType::LEFT_CENTER:
            x_offset = size.width / 2;
            y_offset = 0;
            break;
        case OrentationType::RIGHT_CENTER:
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
        return Position((x + orentation.x_offset) / size.d_width - 1, 1 - ((y + orentation.y_offset) / size.d_height));
    }

    void Position::NormalizeThis(ParametersApp::Size size)
    {
        x = x / size.d_width - 1;
        y = 1 - (y / size.d_height);
    }

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
       orentation.type = transform->GetOrentationType();
       orentation.CalculateOffset(*transform->Size());
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
        return Size(width / size.d_width, height / size.d_height);
    }

    void Size::NormalizeThis(ParametersApp::Size size)
    {
        width = size.d_width / width;
        height = size.d_height / height;
    }

    Size Size::Denormalize(ParametersApp::Size size)
    {
        return Size(size.d_width * width, size.d_height * height);
    }

    void Size::DenormalizeThis(ParametersApp::Size size)
    {
        width = size.d_width * width;
        height = size.d_height * height;
    }

    Size* Size::operator=(ParametersApp::Size size)
    {
        width = size.d_width;
        height = size.d_height;
        return this;
    }

    Size* Size::operator=(Size size)
    {
        width = size.width;
        height = size.height;
        return this;
    }

    Size* Size::operator=(double size)
    {
        width = size;
        height = size;
        return this;
    }

    Size* Size::operator+=(Size size)
    {
        width += size.width;
        height += size.height;
        return this;
    }

    Size* Size::operator+=(double size)
    {
        width += size;
        height += size;
        return this;
    }
    
/**=======================================================================================================================*
 **                                           END OF REGION SIZE
 *========================================================================================================================*/
#pragma endregion SIZE


    Rotation::Rotation()
    {
        z = 0;
    }

    Rotation::Rotation(double z)
    {
        this->z = z;
    }

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
}