#include "DLL/dll.hpp"
#include "UTILS/parameters.hpp"
#include "components.hpp"

namespace pandora
{
    class DLL Image : public Component
    {
    public:
        utils::Color color;

        Image();
    };
}
