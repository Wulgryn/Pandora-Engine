#include "ShaderComponent2D.hpp"
#include "Debug/Console.hpp"
#include "Transform2D.hpp"
#include "../Elements/BaseObject.hpp"
#include "../Parameters.hpp"
#include "Texture2D.hpp"
#include "Core/Application.hpp"

#include "glad/gl.h"

ID primitiveID = -1;

void ShaderComponent2D::SetUniforms(Shader* shader)
{
    if(Transform2D* transform = componenetHandler->GetComponent<Transform2D>())
    {
        ParametersApp::Size size = componenetHandler->GetParentObject()->GetParentWindow()->GetSize();
        Parameters2D::Position norm_pos = transform->Position()->Normalize(size);
        glUniform2f(shader->GetUniform(Shaders::UniformType::POSITION), norm_pos.x, norm_pos.y);
        glUniform1f(shader->GetUniform(Shaders::UniformType::ANGLE), transform->Rotation()->z);
        glUniform2f(shader->GetUniform(Shaders::UniformType::ROTATION_CENTER), (float)norm_pos.x, (float)norm_pos.y);
        glUniform1f(shader->GetUniform("aspectRatio"), size.f_width / size.f_height);
    }
    if(Texture2D* texture2D = componenetHandler->GetComponent<Texture2D>()) 
    {
        if(texture2D->drawType == DrawType::NONE) return;
        if(texture2D->HasTexture() && !texture2D->isForceColorEnabled)
        {
            Texture* texture = texture2D->GetTexture();
            glUniform1i(shader->GetUniform("hasTexture"), true);
            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, texture->GetID());
        }
        else
        {
            glUniform1i(shader->GetUniform("hasTexture"), false);
            
            Color* color = texture2D->GetColor();
            // ^ CAUTION: maybe the NORMALIZE is not working and breaks the color IDK why
            color->Normalize();
            //color->Denormalize();
            glUniform4f(shader->GetUniform(Shaders::UniformType::COLOR),color->Fr,color->Fg,color->Fb, color->Fa);
        }
    }
    else 
    {
        glUniform1i(shader->GetUniform("hasTexture"), false);
        glUniform4f(shader->GetUniform(Shaders::UniformType::COLOR),1.0f,1.0f,1.0f, 1.0f);
    }
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
    if(Transform2D* transform = componenetHandler->GetComponent<Transform2D>())
    {
        Parameters2D::Size norm_size = transform->Size()->Normalize(componenetHandler->GetParentObject()->GetParentWindow()->GetSize());
        shader->SetPrimitiveVertices(Primiteve2DShapes::RECTANGLE,{
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
        shader->SetPrimitiveVertices(Primiteve2DShapes::RECTANGLE,{
            -norm_size.width / 2,-norm_size.height / 2,
            norm_size.width / 2,-norm_size.height / 2,
            norm_size.width / 2,norm_size.height / 2,
            -norm_size.width / 2,norm_size.height / 2
        });
        Parameters2D::Position norm_pos = Parameters2D::Position(0,0).Normalize(componenetHandler->GetParentObject()->GetParentWindow()->GetSize());
        glUniform2f(shader->GetUniform(Shaders::UniformType::POSITION),norm_pos.x, norm_pos.y);
    }


    shader->OnSetUniforms = Method(SetUniforms,this);

    componenetHandler->GetParentObject()->GetParentWindow()->OnResize += Method<void,BaseWindow*,ParametersApp::Size>([=](BaseWindow* window, ParametersApp::Size size){
        if(Transform2D* transform = componenetHandler->GetComponent<Transform2D>())
        {
            Parameters2D::Size norm_size = transform->Size()->Normalize(size);
            shader->SetPrimitiveVertices(Primiteve2DShapes::RECTANGLE,{
                -norm_size.width / 2,-norm_size.height / 2,
                norm_size.width / 2,-norm_size.height / 2,
                norm_size.width / 2,norm_size.height / 2,
                -norm_size.width / 2,norm_size.height / 2
            });
        }
    });


    if(Transform2D* transform = componenetHandler->GetComponent<Transform2D>())
    {
        transform->Size()->OnChange += Method<void, Parameters2D::Size*>([=](Parameters2D::Size* size)
        {
            Parameters2D::Size norm_size = size->Normalize(componenetHandler->GetParentObject()->GetParentWindow()->GetSize());
            // FIXME: EnqueueInvoke
            /**
             *& *===============================FIXIT===================================
             *& * DESCRIPTION: Make it automaticly invoke the method on the main thread. if it needs it.
             *& * HINT: Make in a method in the Event that needs a bool that if that method at invoke needs to be in main thread.
             *& *=======================================================================
            **/
            Application::EnqueueInvoke(Method<void>([=](){
                shader->SetPrimitiveVertices(Primiteve2DShapes::RECTANGLE,{
                    -norm_size.width / 2,-norm_size.height / 2,
                    norm_size.width / 2,-norm_size.height / 2,
                    norm_size.width / 2,norm_size.height / 2,
                    -norm_size.width / 2,norm_size.height / 2
                });
            }));
        });
    }

    if(Texture2D* texture2D = componenetHandler->GetComponent<Texture2D>())
    {
        shader->Draw = Method<void,Shader*>([=](Shader* shader){
            switch (texture2D->drawType)
            {
            case DrawType::FILL:
                glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
                break;
            case DrawType::OUTLINE:
                glDrawElements(GL_LINE_LOOP, 6, GL_UNSIGNED_INT, 0);
                break;
            default:
                glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
                break;
            }
        });
    }
}


void ShaderComponent2D::Render()
{
    shader->Use();
}