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
        Texture* texture = nullptr;
        Image();

        void setTexture(Texture* texture);
    };
}
