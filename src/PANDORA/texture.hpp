#include "DLL/dll.hpp"
#include <string>

namespace pandora
{
    typedef unsigned int TextureID;
    namespace textures
    {
        DLL TextureID loadTexture(std::string path);
    }
}