#pragma once
#include "../ClassObject.hpp"
#include "../Types.hpp"
#include "../Event.hpp"

#include <map>
#include <vector>
class Shader;
namespace Shaders
{
    const char* DefaultVertexShader2D();
    const char* DefaultFragmentShader2D();
    const char* DefaultVertexTextureShader2D();
    const char* DefaultFragmentTextureShader2D();

    enum class UniformType
    {
        POSITION,
        COLOR
    };

    bool CompileShader(ID shaderID, const char* shaderCode, const char* shaderType = "SHADER");

    namespace Container
    {
        void AddShader(Shader* shader);
        void RemoveShader(Shader* shader);
        Shader* GetShader(ID id);
    }
} // namespace Shaders

class Shader : public ClassObject
{
private:
    ID shaderProgram;
    ID vertexShader;
    ID fragmentShader;

    ID VAO;
    ID VBO;
    ID EBO;

    std::map<const char*, ID> uniforms;

    ID PositionID;
    ID ColorID;

    ID id;
public:
    /// @brief Default constructor for Shader.
    /// Have default unifrom binds: `position` -> `[Vec2]` and `color` -> `[Vec3]`.
    Shader(ID id = -1);
    // HACK IMPORTANT: Add more constructors for other shader types
    /**
     * *=======================================================================
     * * DESCRIPTION: Do the belove constructors for other shader types
     * *=======================================================================
    **/
    //XXX REMOVED: Shader constructors
    ////Shader(const char* vertexShaderCode, const char* fragmentShaderCode);
    ////=======================================================================
    //// CAUSE: Don't need right now
    //// WHY LEFT IN: To do it later
    ////=======================================================================
    ////Shader(const char* vertexPath, const char* fragmentPath);
    ////Shader(const char* vertexPath, const char* fragmentPath, const char* geometryPath);
    ////Shader(const char* vertexPath, const char* fragmentPath, const char* tessControlPath, const char* tessEvalPath);
    ////Shader(const char* vertexPath, const char* fragmentPath, const char* tessControlPath, const char* tessEvalPath, const char* geometryPath);
    ////Shader(const char* vertexPath, const char* fragmentPath, const char* tessControlPath, const char* tessEvalPath, const char* geometryPath, const char* computePath);

    void Use();

    void SetVertices(std::vector<double> vertices);

    ID GetShaderProgram() const { return shaderProgram; }

    void BindUniform(const char* name);
    void BindUniform(Shaders::UniformType type);

    ID GetUniform(const char* name);
    ID GetUniform(Shaders::UniformType type);

    ID GetID() const { return id; }

    /// @brief Invoked every time before the shader is used.
    /// @param Shader* The shader that is being used.
    Event<Shader*> OnUse;

    /// @brief Invoked every time after the shader is used.
    /// @param Shader* The shader that is being used.
    Event<Shader*> OnUsed;

    /// @brief Invoked every time before the shader is set uniforms.
    /// @param Shader* The shader that is being used.
    Event<Shader*> OnSetUniforms;

};
