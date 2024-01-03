#include "PANDORA/COMPONENTS/shader.hpp"
#include "CONSOLE/fancyLog.hpp"

#include <glad/gl.h>
#include "PANDORA/COMPONENTS/transform.hpp"
#include "PANDORA/COMPONENTS/image.hpp"
#include "UTILS/parameters.hpp"
#include "PANDORA/mainWindow.hpp"

using namespace pandora;
using namespace std;
using namespace utils;

ID currentShader = -1;
ID currentVAO = -1;

vector<Shader *> &getShadersList()
{
    static vector<Shader *> shaders_list;
    return shaders_list;
}

string shaders::defaultVertexShader2D()
{
    return R"(
        #version 330 core
        layout (location = 0) in vec3 aPos;

        uniform vec3 position;

        void main()
        {
           gl_Position = vec4(aPos.x + position.x, aPos.y + position.y, aPos.z + position.z, 1.0);
        }
    )";
}

string shaders::defaultFragmentShader2D()
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

string shaders::textureVertexShader2D()
{
    return R"(
        #version 330 core
        layout (location = 0) in vec3 aPos;
        layout (location = 1) in vec2 aTexCoord;

        uniform vec2 position;

        out vec2 TexCoord;

        void main()
        {
           gl_Position = vec4(aPos.x + position.x, aPos.y + position.y, aPos.z + position.z, 1.0);
           TexCoord = vec2(aTexCoord.x, 1.0 - aTexCoord.y);
        }
    )";
}

string shaders::textureFragmentShader2D()
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

void compileShaderDebug(ID shader, string source, string type)
{
    const char *src = source.c_str();
    glShaderSource(shader, 1, &src, NULL);
    glCompileShader(shader);

    int success;
    char infoLog[512];
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(shader, 512, NULL, infoLog);
        logType(type);
        logError("SHADER::COMPILATION_FAILED\n" + string(infoLog));
        logType();
    }
}

Shader::Shader()
{
    shaderProgram = glCreateProgram();
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

    compileShaderDebug(vertexShader, shaders::defaultVertexShader2D(), "VERTEX");
    compileShaderDebug(fragmentShader, shaders::defaultFragmentShader2D(), "FRAGMENT");

    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);

    glLinkProgram(shaderProgram);
    glUseProgram(shaderProgram);

    float vertices[] = {
        -0.5f, -0.5f, 0.0f, // bottom left
         0.5f, -0.5f, 0.0f, // bottom right
         0.5f,  0.5f, 0.0f, // top right
        -0.5f,  0.5f, 0.0f  // top left
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
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_DYNAMIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    bindUniform("position");
    bindUniform("color");

   //int pos = glGetUniformLocation(shaderProgram, "position");

   //glUniform2f(pos, 0.0f, 0.4f);

}

Shader::Shader(string vertexShaderSource, string fragmentShaderSource)
{
    shaderProgram = glCreateProgram();
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

    compileShaderDebug(vertexShader, vertexShaderSource, "VERTEX");
    compileShaderDebug(fragmentShader, fragmentShaderSource, "FRAGMENT");

    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);

    glLinkProgram(shaderProgram);
    glUseProgram(shaderProgram);

    float vertices[] = {
        // Pozíció              Textúra koordináta
        -0.5f, -0.5f, 0.0f,     0.0f, 0.0f,     // bottom left
         0.5f, -0.5f, 0.0f,     1.0f, 0.0f,     // bottom right
         0.5f,  0.5f, 0.0f,     1.0f, 1.0f,     // top right
        -0.5f,  0.5f, 0.0f,     0.0f, 1.0f      // top left
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
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_DYNAMIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    bindUniform("position");
    bindUniform("color");
    bindUniform("Texture");
}

void Shader::copy(Shader shader)
{
    shaderProgram = shader.shaderProgram;
    vertexShader = shader.vertexShader;
    fragmentShader = shader.fragmentShader;
    VAO = shader.VAO;
    VBO = shader.VBO;
    EBO = shader.EBO;
    uniforms = shader.uniforms;
    settingsFunction = shader.settingsFunction;
}


static void defaultSettings(Shader *shader, Components *components)
{
    if (Transform *transform = components->get<Transform>()) 
    {
        Size winSize = pandora::mainWindow::get()->parameters.getSize();
        Position pos = transform->position;
        Size size = transform->size;
        Position actualPos = Position(pos.x + size.Width / 2, pos.y + size.Height / 2);
        actualPos = actualPos.toWindowRate(winSize);
        shader->setUniform(ShaderUniformType::POSITION, actualPos.x, actualPos.y);
        size = size.toWindowRate(winSize);
        std::vector<float> vertices = {
            // positions                                // texture coords
            static_cast<float>(-size.Width), static_cast<float>(-size.Height), 0.0f, 0.0f, 0.0f, // bottom left
            static_cast<float>(size.Width), static_cast<float>(-size.Height), 0.0f, 1.0f, 0.0f,  // bottom right
            static_cast<float>(size.Width), static_cast<float>(size.Height), 0.0f, 1.0f, 1.0f,   // top right
            static_cast<float>(-size.Width), static_cast<float>(size.Height), 0.0f, 0.0f, 1.0f   // top left
        };
        components->get<Shader>()->setVerticies(vertices);
        //logInfo("Position: " + to_string(actualPos.x) + ", " + to_string(actualPos.y));
    }
    Image *image = components->get<Image>();
    if(!image->isVisible) return;
    if(image) shader->setUniform(ShaderUniformType::COLOR, image->color.getRedF(), image->color.getGreenF(), image->color.getBlueF());
    if(image && image->texture != -1)
    {
        glEnable(GL_DEPTH_TEST);
        glEnable(GL_BLEND);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, image->texture);
        glDisable(GL_BLEND);
        glDisable(GL_DEPTH_TEST);
    }
}

void Shader::init(Components *components)
{
    isLoaded = true;
    if(currentShader != shaderProgram)
    {
        currentShader = shaderProgram;
        glUseProgram(shaderProgram);
    }
    if(currentVAO != VAO)
    {
        currentVAO = VAO;
        glBindVertexArray(VAO);
    }
    if(settingsFunction) settingsFunction(this);
    else defaultSettings(this, components);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    

    isLoaded = false;
}

void Shader::bindUniform(std::string name)
{
    if (uniforms.find(name) == uniforms.end()) {
        uniforms[name] = glGetUniformLocation(shaderProgram, name.c_str());
    }
}

void Shader::bindUniform(ShaderUniformType type)
{
    switch (type) {
    case ShaderUniformType::POSITION:
        bindUniform("position");
        break;
    case ShaderUniformType::COLOR:
        bindUniform("color");
        break;
    case ShaderUniformType::TEXTURE:
        bindUniform("Texture");
        break;
    }
}

void Shader::setUniform(ShaderUniformType type, float f1, float f2, float f3, float f4)
{
    switch (type) {
    case ShaderUniformType::POSITION:
        setUniform3f("position", f1, f2, f3);
        break;
    case ShaderUniformType::COLOR:
        setUniform3f("color", f1, f2, f3);
        break;
    case ShaderUniformType::TEXTURE:
        setUniform1i("Texture", (int)f1);
        break;
    }
}

void Shader::setUniform1f(std::string name, float f1)
{
    //if(!isLoaded) glUseProgram(shaderProgram);
    glUniform1f(uniforms[name], f1);
}

void Shader::setUniform2f(std::string name, float f1, float f2)
{
    //if(!isLoaded) glUseProgram(shaderProgram);
    glUniform2f(uniforms[name], f1, f2);
}

void Shader::setUniform3f(std::string name, float f1, float f2, float f3)
{
    //if(!isLoaded) glUseProgram(shaderProgram);
    glUniform3f(uniforms[name], f1, f2, f3);
}

void Shader::setUniform4f(std::string name, float f1, float f2, float f3, float f4)
{
    //if(!isLoaded) glUseProgram(shaderProgram);
    glUniform4f(uniforms[name], f1, f2, f3, f4);
}

void Shader::setUniform1i(std::string name, int i1)
{
    //if(!isLoaded) glUseProgram(shaderProgram);
    glUniform1i(uniforms[name], i1);
}

void Shader::setUniform2i(std::string name, int i1, int i2)
{
    //if(!isLoaded) glUseProgram(shaderProgram);
    glUniform2i(uniforms[name], i1, i2);
}

void Shader::setUniform3i(std::string name, int i1, int i2, int i3)
{
    //if(!isLoaded) glUseProgram(shaderProgram);
    glUniform3i(uniforms[name], i1, i2, i3);
}

void Shader::setUniform4i(std::string name, int i1, int i2, int i3, int i4)
{
    //if(!isLoaded) glUseProgram(shaderProgram);
    glUniform4i(uniforms[name], i1, i2, i3, i4);
}

void Shader::setSettings(void (*settingsFunction)(Shader *shader))
{
    this->settingsFunction = settingsFunction;
}

void Shader::setVerticies(std::vector<float> vertices)
{
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * vertices.size(), vertices.data() ,GL_DYNAMIC_DRAW);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, (vertices.size()/4) * sizeof(float), (void *)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, (vertices.size()/4) * sizeof(float), (void *)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
}