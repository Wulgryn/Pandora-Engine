#pragma once
#include "Event.hpp"

class Transform2D;

/// @brief Parameters for the application
namespace ParametersApp
{
    struct Position
    {
        int i_x, i_y;
        float f_x, f_y;
        double d_x, d_y;
        long l_x, l_y;

        Position();
        Position(int x, int y);
        Position(float x, float y);
        Position(double x, double y);
        Position(long x, long y);
    };

    struct Size
    {
        int i_width, i_height;
        float f_width, f_height;
        double d_width, d_height;
        long l_width, l_height;

        Size();
        Size(int width, int height);
        Size(float width, float height);
        Size(double width, double height);
        Size(long width, long height);

        Size* operator=(Size size);
    };
}

/// @brief Parameters for the 2D Objects
namespace Parameters2D
{

    struct Size;
    struct Vector2;

    enum class OrentationType
    {
        TOP_LEFT,
        TOP_RIGHT,
        BOTTOM_LEFT,
        BOTTOM_RIGHT,
        CENTER,
        TOP_CENTER,
        BOTTOM_CENTER,
        LEFT_CENTER,
        RIGHT_CENTER,
    };

    struct Orentation
    {
        double x_offset, y_offset;
        OrentationType type = OrentationType::TOP_LEFT;
        Orentation();
        Orentation(OrentationType type);

        void CalculateOffset(Size size);
    };


    struct Position
    {
        double x, y;
        Position();
        Position(double x, double y);
        Position(ParametersApp::Position position);

        Position Normalize(ParametersApp::Size size);
        void NormalizeThis(ParametersApp::Size size);
        Position Denormalize(ParametersApp::Size size);
        void DenormalizeThis(ParametersApp::Size size);

        void CalcOrientation(Transform2D* transform);

        Position* operator=(ParametersApp::Position position);
        Position* operator=(Position position);
        Position* operator=(double position);

        Position* operator+=(Position position);
        Position* operator+=(double position);
        Position* operator+=(Vector2 vector);
    private:
        Orentation orentation;
    };

    struct Size
    {
        double width, height;
        Size();
        Size(double width, double height);
        Size(ParametersApp::Size size);

        Size Normalize(ParametersApp::Size size);
        void NormalizeThis(ParametersApp::Size size);
        Size Denormalize(ParametersApp::Size size);
        void DenormalizeThis(ParametersApp::Size size);

        Size* SetWidth(double width);
        Size* SetHeight(double height);

        Size* AddWidth(double width);
        Size* AddHeight(double height);

        Size* operator=(ParametersApp::Size size);
        Size* operator=(Size size);
        Size* operator=(double size);

        Size* operator+=(Size size);
        Size* operator+=(double size);

        double& operator[](int index);

        Event<Size*> OnChange;
    };

    struct Rotation
    {
        double z;
        Rotation();
        Rotation(double z);
    };

    struct Scale
    {
        double x, y;
        Scale();
        Scale(double x, double y);

        Scale* operator=(double scale);
    };

    struct Vector2
    {
        double x, y;
        Vector2();
        Vector2(double x, double y);

        Vector2* operator=(double value);
        Vector2* operator=(Vector2 vector);
        Vector2* operator+=(Vector2 vector);
        Vector2* operator+=(double value);
    };
    
}