#include "DLL/dll.hpp"
#include "ui_elements.hpp"


namespace pandora
{
    class DLL Switch : public UIElement
    {
    private:
        Object foreground;
        bool isSelected = false;
    public:
        bool isOn = false;
        

        Switch();

        Object* getForeground();
        Object* getBackground();

        void init(Components* components) override;
    };
    typedef Switch *SwitchObject;
} // namespace pandora