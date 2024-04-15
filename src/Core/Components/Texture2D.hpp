#include "BaseComponent.hpp"
#include "../Rendering/Texture.hpp"
#include "../Rendering/Color.hpp"

class Texture2D : public BaseComponent
{
    Texture* texture = nullptr;
    Color* color = new Color(Colors::WHITE);
public:
    Texture2D() = default;

    void SetTexture(Texture* texture);
    void SetColor(Color* color);

    Texture* GetTexture();
    Color* GetColor();

    bool HasTexture();
    
};