#pragma once
#include "BaseComponent.hpp"
#include "../Rendering/Shader.hpp"
#include "../Rendering/PrimitiveShapes2D.hpp"

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

    Shader* GetShader() { return shader; }

    virtual void Initialize() override;
    virtual void Render();
};