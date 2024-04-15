#include "Text2D.hpp"

#include "Core/Rendering/Shader.hpp"
#include "Debug/Console.hpp"

#include "glad/gl.h"

#define GLT_IMPLEMENTATION
#include "Core/External/gltext.h"

Text2D::Text2D()
{
    if(!gltInitialized && !gltInit())
    {
        DebugConsole::WriteLine("Failed to initialize GLT");
    }
    text = "UNDEFINED";
    gltText = gltCreateText();
    gltSetText(gltText, text.c_str());
}

void Text2D::Render()
{
    Shaders::currentShaderID = -1;
    gltBeginDraw();

    gltColor(color.r, color.g, color.b, color.a);
    gltDrawText2D(gltText, position.x, position.y, (scale.x + scale.y) / 2);

    gltEndDraw();
}

void Text2D::SetText(std::string text)
{
    this->text = text;
    gltSetText(gltText, text.c_str());
}