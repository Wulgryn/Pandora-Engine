#include "Shader.hpp"

#include "../../Debug/Console.hpp"

#include "glad/gl.h"

using namespace std;

/**=======================================================================================================================*
 **                                                  REGION SHADERS
 *========================================================================================================================*/
#pragma region SHADERS

namespace Shaders
{
    const char* DefaultVertexShader2D()
    {
        return R"(
            #version 330 core
            layout (location = 0) in vec3 aPos;

            uniform vec2 position;

            void main()
            {
                gl_Position = vec4(aPos.x + position.x, aPos.y + position.y, aPos.z, 1.0);
            }
        )";
    }

    const char* DefaultFragmentShader2D()
    {
        return R"(
            #version 330 core
            out vec4 FragColor;

            uniform vec3 color;

            void main()
            {
                FragColor = vec4(color, 1.0);
            }
        )";
    }

    const char* DefaultVertexTextureShader2D()
    {
        return R"(
            #version 330 core
            layout (location = 0) in vec3 aPos;
            layout (location = 1) in vec2 aTexCoord;

            out vec2 TexCoord;

            uniform vec2 position;

            void main()
            {
                gl_Position = vec4(aPos.x + position.x, aPos.y + position.y, aPos.z, 1.0);
                TexCoord = vec2(aTexCoord.x, 1.0 - aTexCoord.y);
            }
        )";
    }

    const char* DefaultFragmentTextureShader2D()
    {
        return R"(
            #version 330 core
            out vec4 FragColor;

            in vec2 TexCoord;

            uniform sampler2D Texture;

            void main()
            {
               FragColor = texture(Texture, TexCoord);
            }
        )";
    }

    bool CompileShader(ID shaderID, const char* shaderCode, const char* shaderType)
    {
        glShaderSource(shaderID, 1, &shaderCode, NULL);
        glCompileShader(shaderID);

        int success;
        char infoLog[512];
        glGetShaderiv(shaderID, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(shaderID, 512, NULL, infoLog);
            DebugConsole::WriteLine("<%s>[COMPILE_SHADER_FAILED] %s", shaderType, infoLog);
            return false;
        }

        return true;
    }

    namespace Container
    {
        vector<Shader*>& shadersList()
        {
            static vector<Shader*> shaders;
            return shaders;
        }

        void AddShader(Shader* shader)
        {
            shadersList().push_back(shader);
        }

        void RemoveShader(Shader* shader)
        {
            for (size_t i = 0; i < shadersList().size(); i++)
            {
                if(shadersList()[i] == shader)
                {
                    shadersList().erase(shadersList().begin() + i);
                    return;
                }
            }
        }

        Shader* GetShader(ID id)
        {
            for (size_t i = 0; i < shadersList().size(); i++)
            {
                if(shadersList()[i]->GetID() == id) return shadersList()[i];
            }
            return nullptr;
        }
        
    }

}

/**=======================================================================================================================*
 **                                           END OF REGION SHADERS
 *========================================================================================================================*/
#pragma endregion SHADERS

ID currentShader = -1;
ID shaderCount = 0;

Shader::Shader(ID id)
{
    if(id == -1) 
    {
        this->id = shaderCount++;
        Shaders::Container::AddShader(this);
    }
    else 
    {
        this->id = id;
        Shader* shader = Shaders::Container::GetShader(id);
        PositionID = shader->PositionID;
        ColorID = shader->ColorID;
        return;
    }
    shaderProgram = glCreateProgram();
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

    if (!Shaders::CompileShader(vertexShader, Shaders::DefaultVertexShader2D(), "VERTEX_SHADER") || 
        !Shaders::CompileShader(fragmentShader, Shaders::DefaultFragmentShader2D(), "FRAGMENT_SHADER"))
    {
        DebugConsole::WriteLine("[SHADER_ERROR] Failed to compile shader");
        return;
    }

    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);

    glLinkProgram(shaderProgram);
    glUseProgram(shaderProgram);

    double vertices[] = {
        -0.5, -0.5, // bottom left
         0.5, -0.5, // bottom right
         0.5,  0.5, // top right
        -0.5,  0.5  // top left
    };

    unsigned int indices[] = {
        0, 1, 2,
        2, 3, 0
    };

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices) *sizeof(double), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 2, GL_DOUBLE, GL_FALSE, 2 * sizeof(double), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 2, GL_DOUBLE, GL_FALSE, 2 * sizeof(double), (void*)(2 * sizeof(double)));
    glEnableVertexAttribArray(1);

    BindUniform(Shaders::UniformType::POSITION);
    BindUniform(Shaders::UniformType::COLOR);

    OnSetUniforms += +[](Shader* shader)
    {
        glUniform2f(shader->GetUniform(Shaders::UniformType::POSITION), 0.5f, 0.0f);
        glUniform3f(shader->GetUniform(Shaders::UniformType::COLOR), 1.0f, 0.0f, 0.0f);
    };

}

void Shader::Use()
{
    if(currentShader != id)
    {
        currentShader = id;
        glUseProgram(Shaders::Container::GetShader(id)->shaderProgram);
        glBindVertexArray(Shaders::Container::GetShader(id)->VAO);
    }
    OnUse.Invoke(this);

    OnSetUniforms.Invoke(this);

    glDrawElements(GL_TRIANGLE_STRIP, 6, GL_UNSIGNED_INT, 0);
    OnUsed.Invoke(this);
}

void Shader::SetVertices(std::vector<double> vertices)
{
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(double), vertices.data(), GL_STATIC_DRAW);
}


void Shader::BindUniform(const char* name)
{
    if(uniforms.find(name) == uniforms.end())
    {
        uniforms[name] = glGetUniformLocation(shaderProgram, name);
    }
}

void Shader::BindUniform(Shaders::UniformType type)
{
    switch (type)
    {
    case Shaders::UniformType::COLOR:
        ColorID = glGetUniformLocation(shaderProgram, "color");
        break;
    case Shaders::UniformType::POSITION:
        PositionID = glGetUniformLocation(shaderProgram, "position");
        break;
    default:
        break;
    }
}

ID Shader::GetUniform(const char* name)
{
    return uniforms[name];
}

ID Shader::GetUniform(Shaders::UniformType type)
{
    switch (type)
    {
    case Shaders::UniformType::COLOR:
        return ColorID;
    case Shaders::UniformType::POSITION:
        return PositionID;
    default:
        return -1;
    }
}