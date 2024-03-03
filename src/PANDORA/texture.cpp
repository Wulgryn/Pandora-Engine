#include "texture.hpp"

#include "glad/gl.h"
#include "SOIL/SOIL.h"
#include "CONSOLE/fancyLog.hpp"

using namespace pandora;
using namespace std;

Texture::Texture(string name)
{
    id = textures::loadTexture("assets/textures/" + name);
    path = "assets/textures/" + name;
}

Texture::Texture(TextureID id)
{
    this->id = id;
    path = "";
}

TextureID Texture::getID()
{
    return id;
}

// Függvény a PNG fájl beolvasására és gridre bontására
std::vector<Texture*> Texture::split(int x, int y) {
    if(path == "")
    {
        logError("Texture::split() called on texture with no path");
        return std::vector<Texture*>();
    }
    int width, height;
    unsigned char* image = SOIL_load_image(path.c_str(), &width, &height, 0, SOIL_LOAD_RGBA);

    if (!image) {
        logError("Hiba a kép betöltésekor: " + std::string(SOIL_last_result()));
        exit(EXIT_FAILURE);
    }

    std::vector<Texture*> textures;

    int tileWidth = width / x;
    int tileHeight = height / y;

    for (int y_ = 0; y_ < y; ++y_) {
        for (int x_ = 0; x_ < x; ++x_) {
            GLuint textureID;
            glGenTextures(1, &textureID);
            glBindTexture(GL_TEXTURE_2D, textureID);

            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, tileWidth, tileHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE,
                         image + (y_ * tileHeight * width + x_ * tileWidth) * 4);

            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

            textures.push_back(new Texture(textureID));
        }
    }

    SOIL_free_image_data(image);

    return textures;
}


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