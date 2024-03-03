#include "DLL/dll.hpp"
#include <string>
#include <vector>

namespace pandora
{
    typedef unsigned int TextureID;

    class DLL Texture
    {
    private:
        TextureID id;
        std::string path;
    public:
        Texture(std::string name);
        Texture(TextureID id);

        TextureID getID();

        std::vector<Texture*> split(int x, int y);
    };

    namespace textures
    {
        DLL TextureID loadTexture(std::string path);
    }
}