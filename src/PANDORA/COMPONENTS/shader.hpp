#pragma once
#include "DLL/dll.hpp"
#include "components.hpp"
#include <string>
#include <map>
namespace pandora
{   
    enum class ShaderUniformType
    {
        POSITION,
        COLOR
    };


    typedef unsigned int ID;

    class DLL Shader : public Component
    {
    private:
        ID shaderProgram;
        ID vertexShader;
        ID fragmentShader;

        ID VAO;
        ID VBO;
        ID EBO;

        std::map<std::string, ID> uniforms;

        bool isLoaded = false;

        void (*settingsFunction)(Shader *shader) = nullptr;
    public:
        Shader();

        void init(Components *components) override;

        void bindUniform(std::string name);
        void bindUniform(ShaderUniformType type);

        void setUniform(ShaderUniformType type, float f1, float f2 = 0.0f, float f3 = 0.0f, float f4 = 0.0f);

        void setUniform1f(std::string name, float f1);
        void setUniform2f(std::string name, float f1, float f2);
        void setUniform3f(std::string name, float f1, float f2, float f3);
        void setUniform4f(std::string name, float f1, float f2, float f3, float f4);

        void setSettings(void (*settingsFunction)(Shader *shader) = nullptr);
    };

    namespace shaders
    {
        std::string defaultVertexShader();
        std::string defaultFragmentShader();

    } // namespace shaders
}