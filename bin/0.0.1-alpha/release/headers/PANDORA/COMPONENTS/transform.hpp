#include "DLL/dll.hpp"
#include "components.hpp"
#include "UTILS/parameters.hpp"
namespace pandora
{
    class DLL Transform : public Component
    {
    public:
        utils::Position position;
        utils::Rotation rotation;
        utils::Size size;

        Transform();
    };
}