#include "texture.hpp"

#include "glad/gl.h"
#include "SOIL/SOIL.h"
#include "CONSOLE/fancyLog.hpp"

using namespace pandora;
using namespace std;

TextureID textures::loadTexture(string path)
{
    unsigned int textureID;
    glGenTextures(1, &textureID);

    int width, height, nrChannels;
    unsigned char* data = SOIL_load_image(path.c_str(), &width, &height, &nrChannels, SOIL_LOAD_RGBA);

    if (data)
    {
        glBindTexture(GL_TEXTURE_2D, textureID);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);

        // Beállítja a textúra paramétereit
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        SOIL_free_image_data(data);
        logSuccess("Loaded texture at path: " + path);
    }
    else
    {
        logError("Failed to load texture at path: " + path);
        SOIL_free_image_data(data);
        return -1;
    }

    return textureID;
}