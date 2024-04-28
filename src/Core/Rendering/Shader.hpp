#pragma once
#include "../ClassObject.hpp"
#include "../Types.hpp"
#include "../Event.hpp"
#include "PrimitiveShapes2D.hpp"

#include <map>
#include <vector>
#include <string>
class Shader;
namespace Shaders
{
    extern ID currentShaderID;

    const char* DefaultVertexShader2D();
    const char* DefaultFragmentShader2D();
    const char* DefaultVertexTextureShader2D();
    const char* DefaultFragmentTextureShader2D();

    Shader* createNew();

    enum class UniformType
    {
        POSITION,
        COLOR,
        TEXTURE,
        ANGLE,
        ROTATION_CENTER,
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

    ID PositionID;
    ID ColorID;
    ID TextureID;
    ID AngleID;
    ID RotationCenterID;

    ID ShaderID;
    //if its a real shader or just imitating one by the id
    bool isLink = false;
    bool isCreated = false;

    void createShader(const char* vertexShaderCode, const char* fragmentShaderCode);
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

    void CreateNew();

    /// @brief Use the shader.
    void Use();

    /**
     * @brief Set the vertices of the shader.
     * @param std::vector<double> The vertices to set.
     * @exception No built-in.
     * @details <b>Examples</b><p/>
     * Basic Example:
     * @code{.cpp}
     * std::vector<double> vertices = {
     *      // Position    Texture coordinate
     *      -0.5, -0.5,     0.0, 0.0,     // bottom left
     *       0.5, -0.5,     1.0, 0.0,     // bottom right
     *       0.5,  0.5,     1.0, 1.0,     // top right
     *      -0.5,  0.5,     0.0, 1.0      // top left
     * };
     * shader->SetVertices(vertices);
     * @endcode
     */
    void SetVertices(std::vector<double> vertices);

    void SetPrimitiveVertices(Primiteve2DShapes primitive_shape,std::vector<double> primitive_vertices);

    ID GetShaderProgram() const { return shaderProgram; }

    void BindUniform(std::string name);
    void BindUniform(Shaders::UniformType type);

    ID GetUniform(std::string name);
    ID GetUniform(Shaders::UniformType type);

    ID GetID() const { return ShaderID; }

    /// @brief Invoked every time before the shader is used.
    /// @param Shader* The shader that is being used.
    Event<Shader*> OnUse;

    /// @brief Invoked every time after the shader is used.
    /// @param Shader* The shader that is being used.
    Event<Shader*> OnUsed;

    /// @brief Invoked every time before the shader is set uniforms.
    /// @param Shader* The shader that is being used.
    Event<Shader*> OnSetUniforms;

    /// @brief Invoked every time the shader attempts to draw.
    /// @param Shader* The shader that is being used.
    Method<void,Shader*> Draw;

};
