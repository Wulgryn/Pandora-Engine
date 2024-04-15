#include "Texture.hpp"

#include "../../Debug/Console.hpp"

#include "glad/gl.h"
#include "SOIL/SOIL.h"

Texture::Texture(std::string path, bool absolutePath)
{
    
    this->path = path;
    if (!absolutePath)
        this->path = "assets/textures/" + path;

    glGenTextures(1, &textureID);
    
    int width, height, nrChannels;
    unsigned char* data = SOIL_load_image(this->path.c_str(), &width, &height, &nrChannels, SOIL_LOAD_RGBA);
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
        DebugConsole::WriteLine("[%d]Loaded texture at path: %s", textureID,this->path.c_str());
    }
    else
    {
        DebugConsole::WriteLine("Failed to load texture: %s\n%s", this->path.c_str(), SOIL_last_result());
        SOIL_free_image_data(data);
    }
}

std::vector<Texture*> Texture::split(int width, int height)
{
    int imageWidth, imageHeight;
    unsigned char* image = SOIL_load_image(path.c_str(), &imageWidth, &imageHeight, 0, SOIL_LOAD_RGBA);

    if (!image) {
        DebugConsole::WriteLine("[ERROR] Failed to load image: %s\n%s", path, SOIL_last_result());
        return std::vector<Texture*>();
    }

    std::vector<Texture*> textures;

    int tileWidth = imageWidth / width;
    int tileHeight = imageHeight / height;

    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            GLuint textureID;
            glGenTextures(1, &textureID);
            glBindTexture(GL_TEXTURE_2D, textureID);

            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, tileWidth, tileHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE,
                         image + (y * tileHeight * imageWidth + x * tileWidth) * 4);

            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

            textures.push_back(new Texture(textureID, path));
        }
    }

    SOIL_free_image_data(image);

    return textures;
}