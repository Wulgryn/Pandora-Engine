#include "DLL/dll.hpp"
#include "ui_elements.hpp"
#include "UTILS/parameters.hpp"
#include <vector>

namespace pandora
{
    class DLL Scrollbar : public UIElement
    {
    private:
        Object foreground;
        
        std::vector<Object*> binded_objects;

        double percentage = 0.0;
        double value = 0;
        bool isSelected = false;
        double prev_value = 0;
    public:
        double maximum = 100;
        double step = 1;
        double scroll_speed = 1;
        bool isEnable = true;

        Scrollbar();

        void setValue(double value);
        double getValue();

        void setPercentage(double percentage);
        double getPercentage();

        void setScrollY(double y);
        double getScrollY();

        void bindObject(Object* object);

        void init(Components* components) override;
    };
    typedef Scrollbar *ScrollbarObject;
} // namespace pandora