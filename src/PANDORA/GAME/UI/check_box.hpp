#include "DLL/dll.hpp"
#include "ui_elements.hpp"


namespace pandora
{
    class DLL CheckBox : public UIElement
    {
    private:
        Object foreground;
        bool isSelected = false;
    public:
        bool isChecked = false;
        

        CheckBox();

        Object* getForeground();
        Object* getBackground();

        void init(Components* components) override;
    };
    typedef CheckBox *CheckBoxObject;
} // namespace pandora