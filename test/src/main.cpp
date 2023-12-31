#include "DLL/init.hpp"
#include "PANDORA/pandora.hpp"
#include "IO/window.hpp"
#include "IO/mouse.hpp"
#include "CONSOLE/fancyLog.hpp"
#include "UTILS/parameters.hpp"
using namespace io;

ButtonObject btn;

int setup()
{
    return 0;
}

int start(Window& window)
{
    window.setBackgroundColor(utils::Color(0.2f, 0.2f, 0.2f, 1.0f));
    return 0;
}

int update(int fps, Window& window)
{
    return 0;
}


int main(int argc, char const *argv[])
{
    PandoraEngine::init();
    Window window(800, 600, "Pandora");
    //window.setBackgroundColor(utils::Color(0.2f, 0.2f, 0.2f, 1.0f));
    window.setSetupFunction(setup);
    window.setStartFunction(start);
    window.setUpdateFunction(update);

    window.start();
    return 0;
}
