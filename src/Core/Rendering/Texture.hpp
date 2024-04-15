#include "../Types.hpp"
#include "../ClassObject.hpp"

#include <string>
#include <vector>

class Texture : public ClassObject
{
private:
    ID textureID;
    std::string path;

    Texture(ID textureID, std::string virtualPath) : textureID(textureID), path(virtualPath) {}
public:
    /// @brief Constructor of the Texture class.
    /// @param path The path to the texture in "assets/textures".
    /// @param absolutePath If true then the path is absolute and not relative in "assets/textures".
    Texture(std::string path, bool absolutePath = false);

    ID GetID() const { return textureID; }
    const char* GetPath() const { return path.c_str(); }

    /// @brief Splits the texture into multiple textures by width and height.
    /// @param width The width of the new textures.
    /// @param height The height of the new textures.
    std::vector<Texture*> split(int width, int height);
};