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
    ID currentShaderID = -1;

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
            uniform vec4 color;
            uniform bool hasTexture;

            void main()
            {
                FragColor = color;
                if(hasTexture) 
                {
                    vec4 texColor = texture(Texture, TexCoord);
                    FragColor = vec4(texColor.rgb, texColor.a);
                }
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

ID shaderCount = 0;

void Shader::createShader(const char* vertexShaderCode, const char* fragmentShaderCode)
{
    isCreated = false;
    shaderProgram = glCreateProgram();
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

    if (!Shaders::CompileShader(vertexShader, vertexShaderCode, "VERTEX_SHADER") || 
        !Shaders::CompileShader(fragmentShader, fragmentShaderCode, "FRAGMENT_SHADER"))
    {
        DebugConsole::WriteLine("[SHADER_ERROR] Failed to compile shader");
        return;
    }

    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);

    glLinkProgram(shaderProgram);
    glUseProgram(shaderProgram);

    double vertices[] = {
        -0.5, -0.5,     1.0, 1.0, // bottom left
         0.5, -0.5,     1.0, 0.0, // bottom right
         0.5,  0.5,     0.0, 0.0, // top right
        -0.5,  0.5,     0.0, 1.0 // top left
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

    glVertexAttribPointer(0, 2, GL_DOUBLE, GL_FALSE, 4 * sizeof(double), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 2, GL_DOUBLE, GL_FALSE, 4 * sizeof(double), (void*)(2 * sizeof(double)));
    glEnableVertexAttribArray(1);

    BindUniform(Shaders::UniformType::POSITION);
    BindUniform(Shaders::UniformType::COLOR);
    BindUniform(Shaders::UniformType::TEXTURE);
    BindUniform("hasTexture");
    glUniform1i(GetUniform("hasTexture"), false);
    glUniform1i(GetUniform(Shaders::UniformType::TEXTURE), 0);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    OnSetUniforms += +[](Shader* shader)
    {
        glUniform2f(shader->GetUniform(Shaders::UniformType::POSITION), 0.0f, 0.0f);
        glUniform4f(shader->GetUniform(Shaders::UniformType::COLOR), 1.0f, 0.0f, 0.0f, 1.0f);
    };
    isCreated = true;
}

Shader::Shader(ID id)
{
    if(id == -1) 
    {
        this->ShaderID = shaderCount++;
        isLink = false;
        Shaders::Container::AddShader(this);
        createShader(Shaders::DefaultVertexTextureShader2D(), Shaders::DefaultFragmentTextureShader2D());
    }
    else 
    {
        this->ShaderID = id;
        Shader* shader = Shaders::Container::GetShader(id);
        PositionID = shader->PositionID;
        ColorID = shader->ColorID;
        TextureID = shader->TextureID;
        isLink = true;
        isCreated = true;
        // TODO Make the shader copy by reference
        return;
    }
    
}

void Shader::CreateNew()
{
    if(!isLink) return;
    isCreated = false;
    this->ShaderID = shaderCount++;
    isLink = false;
    Shaders::Container::AddShader(this);
    createShader(Shaders::DefaultVertexTextureShader2D(), Shaders::DefaultFragmentTextureShader2D());
}

void Shader::Use()
{
    if(!isCreated) return;
    if(Shaders::currentShaderID != ShaderID)
    {
        Shaders::currentShaderID = ShaderID;
        glUseProgram(Shaders::Container::GetShader(ShaderID)->shaderProgram);
        glBindVertexArray(Shaders::Container::GetShader(ShaderID)->VAO);
    }
    OnUse.Invoke(this);
    // FIXME: Invoke!!! WRONG
    /**
     *& *===============================FIXIT===================================
     *& * DESCRIPTION: The Uniforms only need to be set once or on change, not every Render.
     *& * HINT: Make other methods in like Transform2D -> for example: OnChange, OnSizeChange and set the uniform on that event
     *& *=======================================================================
    **/
    OnSetUniforms.Invoke(this);
    
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    //glDisable(GL_BLEND);
    OnUsed.Invoke(this);
}

void Shader::SetVertices(std::vector<double> vertices)
{
    glBindBuffer(GL_ARRAY_BUFFER, Shaders::Container::GetShader(ShaderID)->VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(double), vertices.data(), GL_STATIC_DRAW);
}

void Shader::SetPrimitiveVertices(Primiteve2DShapes primitive_shape, std::vector<double> primitive_vertices)
{
    vector<double> vertices;
    switch (primitive_shape)
    {
    case Primiteve2DShapes::RECTANGLE:
        vertices = {
            primitive_vertices[0], primitive_vertices[1],     0.0, 0.0,     // bottom left
            primitive_vertices[2], primitive_vertices[3],     1.0, 0.0,     // bottom right
            primitive_vertices[4], primitive_vertices[5],     1.0, 1.0,     // top right
            primitive_vertices[6], primitive_vertices[7],     0.0, 1.0      // top left
        };
        glBindBuffer(GL_ARRAY_BUFFER, Shaders::Container::GetShader(ShaderID)->VBO);
        glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(double), vertices.data(), GL_STATIC_DRAW);
        break;
    default:
        break;
    }
}

void Shader::BindUniform(string name)
{
    ID id = glGetUniformLocation(Shaders::Container::GetShader(ShaderID)->shaderProgram, name.c_str());
    DebugConsole::WriteLine("[SHADER] Bound uniform: %s with id: %d", name.c_str(), id);
}

void Shader::BindUniform(Shaders::UniformType type)
{
    switch (type)
    {
    case Shaders::UniformType::COLOR:
        // FIXME: Shaders::Container::GetShader(ShaderID) is too slow
        /**
         *& *===============================FIXIT===================================
         *& * DESCRIPTION: Always searching in the list for the shader is slow.
         *& * HINT: make a copy by reference int the constructor, REPLACE ALL THE Shaders::Container::GetShader(ShaderID) with the the right thing.
         *& *=======================================================================
        **/
        ColorID = glGetUniformLocation(Shaders::Container::GetShader(ShaderID)->shaderProgram, "color");
        DebugConsole::WriteLine("[SHADER] Bound uniform: %s with id: %d", "color", ColorID);
        break;
    case Shaders::UniformType::POSITION:
        PositionID = glGetUniformLocation(Shaders::Container::GetShader(ShaderID)->shaderProgram, "position");
        DebugConsole::WriteLine("[SHADER] Bound uniform: %s with id: %d", "position", PositionID);
        break;
    case Shaders::UniformType::TEXTURE:
        TextureID = glGetUniformLocation(Shaders::Container::GetShader(ShaderID)->shaderProgram, "Texture");
        DebugConsole::WriteLine("[SHADER] Bound uniform: %s with id: %d", "Texture", TextureID);
        break;
    default:
        break;
    }
}

ID Shader::GetUniform(string name)
{
    return glGetUniformLocation(Shaders::Container::GetShader(ShaderID)->shaderProgram, name.c_str());;
}

ID Shader::GetUniform(Shaders::UniformType type)
{
    switch (type)
    {
    case Shaders::UniformType::COLOR:
        return ColorID;
    case Shaders::UniformType::POSITION:
        return PositionID;
    case Shaders::UniformType::TEXTURE:
        return TextureID;
    default:
        return -1;
    }
}