#include "UIElement.hpp"
#include "../Color.hpp"
#include "../../Parameters.hpp"

#include <string>

struct GLTtext;

class Text2D : public UIElement
{
    std::string text;

    GLTtext* gltText = nullptr;
public:
    Color color = Colors::WHITE;
    Parameters2D::Position position = {0, 0};
    Parameters2D::Scale scale = {1, 1};

    Text2D();

    void Render() override;

    void SetText(std::string text);
    std::string GetText() { return text;}
};