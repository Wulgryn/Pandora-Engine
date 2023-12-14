#include "shader.hpp"
#include "CONSOLE/fancyLog.hpp"

#include <glad/gl.h>
#include "transform.hpp"
#include "image.hpp"
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

string shaders::defaultVertexShader()
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

string shaders::defaultFragmentShader()
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

void compileShaderDebug(ID shader, string source)
{
    const char *src = source.c_str();
    glShaderSource(shader, 1, &src, NULL);
    glCompileShader(shader);

    int success;
    char infoLog[512];
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(shader, 512, NULL, infoLog);
        logError("SHADER::COMPILATION_FAILED\n" + string(infoLog));
    }
}

Shader::Shader()
{
    shaderProgram = glCreateProgram();
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

    compileShaderDebug(vertexShader, shaders::defaultVertexShader());
    compileShaderDebug(fragmentShader, shaders::defaultFragmentShader());

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
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

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

static void defaultSettings(Shader *shader, Components *components)
{
    ;
    if (Transform *transform = components->get<Transform>()) 
    {
        Position pos = transform->position.toWindowRate(pandora::mainWindow::get()->parameters.getSize());
        shader->setUniform(ShaderUniformType::POSITION, transform->position.x, transform->position.y);
    }
    if(Image *image = components->get<Image>()) shader->setUniform(ShaderUniformType::COLOR, image->color.getRedF(), image->color.getGreenF(), image->color.getBlueF());
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
    }
}

void Shader::setUniform(ShaderUniformType type, float f1, float f2, float f3, float f4)
{
    switch (type) {
    case ShaderUniformType::POSITION:
        setUniform2f("position", f1, f2);
        break;
    case ShaderUniformType::COLOR:
        setUniform3f("color", f1, f2, f3);
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

void Shader::setSettings(void (*settingsFunction)(Shader *shader))
{
    this->settingsFunction = settingsFunction;
}