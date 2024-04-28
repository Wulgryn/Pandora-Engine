#include "BaseComponent.hpp"
#include "../Rendering/Texture.hpp"
#include "../Rendering/Color.hpp"

enum class DrawType
{
    NONE,
    OUTLINE,
    FILL
};

class Texture2D : public BaseComponent
{
    Texture* texture = nullptr;
    Color* color = new Color(Colors::WHITE);
public:
    /// @brief If true, the color will be forced to be drawed even if the texture is set.
    bool isForceColorEnabled = false;
    DrawType drawType = DrawType::FILL;

    Texture2D() = default;

    void SetTexture(Texture* texture);
    void SetColor(Color* color);

    Texture* GetTexture();
    Color* GetColor();

    bool HasTexture();
    
};