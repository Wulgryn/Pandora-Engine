#include "DLL/dll.hpp"
#include "ui_elements.hpp"
#include "UTILS/parameters.hpp"

namespace pandora
{

    class DLL ProgressBar : public UIElement
    {
    private:
        double percentage = 0.0;
        double last_value = 0.0;
        Object background;

        void (*onProgressChange)() = nullptr;

    public:
        double minimum = 0.0;
        double maximum = 100.0;
        double value = 0.0;
        double step = 1.0;

        ProgressBar();

        double getPercentage();
        void setPercentage(double percentage);

        void stepUp();
        void stepDown();

        void setBackgroundColor(utils::Color color);

        void setOnProgressChange(void (*onProgressChange)());

        void init(Components *components) override;
    };
    typedef ProgressBar *ProgressBarObject;
} // namespace pandora