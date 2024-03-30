#include "ShaderComponent2D.hpp"
#include "Debug/Console.hpp"
#include "Transform2D.hpp"
#include "../Rendering/BaseObject.hpp"
#include "../Parameters.hpp"

#include "glad/gl.h"

ID primitiveID = -1;

void ShaderComponent2D::SetUniforms(Shader* shader)
{
    if(Transform2D* transform = componenetHandler->GetComponenet<Transform2D>())
    {
        Parameters2D::Position norm_pos = transform->Position()->Normalize(componenetHandler->GetParentObject()->GetParentWindow()->GetSize());
        glUniform2f(shader->GetUniform(Shaders::UniformType::POSITION),norm_pos.x, norm_pos.y);
    }
    glUniform3f(shader->GetUniform(Shaders::UniformType::COLOR),1.0f,1.0f,1.0f);
}

ShaderComponent2D::ShaderComponent2D() : ShaderComponent2D(Primiteve2DShapes::RECTANGLE)
{
}

ShaderComponent2D::ShaderComponent2D(Shader* shader)
{
    this->shader = shader;
}

ShaderComponent2D::ShaderComponent2D(Primiteve2DShapes shape)
{
    isPrimitive = true;
    shader = new Shader(primitiveID);
    primitiveID = shader->GetID();
    switch (shape)
    {
    case Primiteve2DShapes::RECTANGLE:
        
        break;
    
    default:
        break;
    }
}

void ShaderComponent2D::Initialize()
{
    if(Transform2D* transform = componenetHandler->GetComponenet<Transform2D>())
    {
        Parameters2D::Size norm_size = transform->Size()->Normalize(componenetHandler->GetParentObject()->GetParentWindow()->GetSize());
        shader->SetVertices({
            -norm_size.width / 2,-norm_size.height / 2,
            norm_size.width / 2,-norm_size.height / 2,
            norm_size.width / 2,norm_size.height / 2,
            -norm_size.width / 2,norm_size.height / 2
        });
        Parameters2D::Position norm_pos = transform->Position()->Normalize(componenetHandler->GetParentObject()->GetParentWindow()->GetSize());
        glUniform2f(shader->GetUniform(Shaders::UniformType::POSITION),norm_pos.x, norm_pos.y);
    }
    else
    {
        Parameters2D::Size norm_size = Parameters2D::Size(100,100).Normalize(componenetHandler->GetParentObject()->GetParentWindow()->GetSize());
        shader->SetVertices({
            -norm_size.width / 2,-norm_size.height / 2,
            norm_size.width / 2,-norm_size.height / 2,
            norm_size.width / 2,norm_size.height / 2,
            -norm_size.width / 2,norm_size.height / 2
        });
        Parameters2D::Position norm_pos = Parameters2D::Position(100,100).Normalize(componenetHandler->GetParentObject()->GetParentWindow()->GetSize());
        glUniform2f(shader->GetUniform(Shaders::UniformType::POSITION),norm_pos.x, norm_pos.y);
    }
    shader->OnSetUniforms = Method(SetUniforms,this);
    componenetHandler->GetParentObject()->GetParentWindow()->OnResize += Method<void,BaseWindow*,ParametersApp::Size>([=](BaseWindow* window, ParametersApp::Size size){
        if(Transform2D* transform = componenetHandler->GetComponenet<Transform2D>())
        {
            Parameters2D::Size norm_size = transform->Size()->Normalize(size);
            shader->SetVertices({
                -norm_size.width / 2,-norm_size.height / 2,
                norm_size.width / 2,-norm_size.height / 2,
                norm_size.width / 2,norm_size.height / 2,
                -norm_size.width / 2,norm_size.height / 2
            });
        }
    });
}


void ShaderComponent2D::Render()
{
    shader->Use();
}