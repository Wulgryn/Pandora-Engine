#include "DLL/dll.hpp"
#include "UTILS/parameters.hpp"
#include "components.hpp"
#include "PANDORA/texture.hpp"

namespace pandora
{
    class DLL Image : public Component
    {
    public:
        bool isVisible = true;
        utils::Color color;
        TextureID texture = -1;
        Image();

        void setTexture(TextureID texture);
    };
}
