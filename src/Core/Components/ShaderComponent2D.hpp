#pragma once
#include "BaseComponent.hpp"
#include "../Rendering/Shader.hpp"

enum class Primiteve2DShapes
{
    RECTANGLE
    // TODO https://docs.unity3d.com/Manual/2DPrimitiveObjects.html
};

class ShaderComponent2D : public BaseComponent
{
private:
    Shader* shader;
    void SetUniforms(Shader* shader);
    bool isPrimitive = false;
    Primiteve2DShapes shape;
public:
    ShaderComponent2D();
    ShaderComponent2D(Shader* shader);
    ShaderComponent2D(Primiteve2DShapes shape);

    virtual void Initialize() override;
    virtual void Render();
};