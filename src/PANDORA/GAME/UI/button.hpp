#include "ui_elements.hpp"
#include "PANDORA/COMPONENTS/components.hpp"

namespace pandora
{
    class DLL Button : public UIElement
    {
    private:
       void (*onClick)() = nullptr;
       void (*onMouseDown)() = nullptr;
       void (*onHover)() = nullptr;
       void (*onHoverExit)() = nullptr;

       bool isOnHover = false;
    public:
        Button();

        void setOnClick(void (*onClick)());
        void setOnMouseDown(void (*onMouseDown)());
        void setOnHover(void (*onHover)());
        void setOnHoverExit(void (*onHoverExit)());
        
        void init(Components* components) override;
    };
    typedef Button* ButtonObject;


} // namespace pandora
