#include "DLL/init.hpp"
#include "IO/window.hpp"
#include "CONSOLE/fancyLog.hpp"
#include "UTILS/parameters.hpp"

using namespace io;
#include <thread>
#include <iostream>

#include "UTILS/parameters.hpp"
#include "UTILS/timer.hpp"

using namespace utils;
using namespace utils::_2D_;

int setup() {
    logInfo("Setup");
    glfwSwapInterval(0);
    return 0;
}
int start(Window &window) {
    logInfo("Start");
    window.properties.waitForUpdate = false;
    window.log.logTPS = true;
    window.log.logFPS = true;
    window.log.logMainThreadTime = true;
    window.parameters.setLocation(Location(100,100));

    return 0;   
}


int update(int frame, Window &window) {

    //logInfo("Frame: " + std::to_string(frame));
    std::this_thread::sleep_for(std::chrono::milliseconds(10000));
    return 0;
}

int main() {
    timer::start();
    glfwWindowHint(GLFW_DOUBLEBUFFER, GLFW_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE);
    timer::stop();

    logInfo("Ellapsed time: " + timer::getEllapsedTime(timer::TimerClockPrecision::NANOSECOND,timer::TimerDisplayType::ALL));
    // Location loc(0, 0);
    // loc = loc + Location(1, 1);
    // std::cout << loc.ix << " " << loc.iy << std::endl;
    //logInfo("Hello World! %d %d", 100, 200);
    
    PandoraEngine::init();
    Window window(1400, 750, "PandoraEngine");
    // std::thread t1([&window]() {
    //     logType("FPS");
    //     while (true)
    //     {
    //         logInfo("%d", window.getCurrentFPS());
    //     }
    //     logType();
    // });
    window.setUpdateFunction(update);
    window.setStartFunction(start);
    window.setSetupFunction(setup);
    window.setTargetFPS(120);
    window.setTargetTPS(60);
    window.properties.setDecorated(false);
    window.start();
    //t1.join();
    return 0;
}