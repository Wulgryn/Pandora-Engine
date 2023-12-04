#include "timer.hpp"

#include "CONSOLE/fancyLog.hpp"

using namespace std;
using namespace chrono;

using namespace utils;

high_resolution_clock::time_point start_time;
high_resolution_clock::time_point end_time;

void timer::start() {
    start_time = std::chrono::high_resolution_clock::now();
}

void timer::stop() {
    end_time = std::chrono::high_resolution_clock::now();
}

int timer::getEllapsedSeconds() {
    return duration_cast<seconds>(end_time - start_time).count();
}

int timer::getEllapsedMilliseconds() {
    return duration_cast<milliseconds>(end_time - start_time).count();
}

int timer::getEllapsedMicroseconds() {
    return duration_cast<microseconds>(end_time - start_time).count();
}

int timer::getEllapsedNanoseconds() {
    return duration_cast<nanoseconds>(end_time - start_time).count();
}

string timer::getEllapsedTime(timer::TimerClockPrecision precision, timer::TimerDisplayType displayType) {
    string seconds = to_string(timer::getEllapsedSeconds());
    string milliseconds = to_string(timer::getEllapsedMilliseconds() % 1000);
    string microseconds = to_string(timer::getEllapsedMicroseconds() % 1000);
    string nanoseconds = to_string(timer::getEllapsedNanoseconds() % 1000);
    switch (precision)
    {
    case TimerClockPrecision::SECONDS:
        return seconds + "s";
    case TimerClockPrecision::MILLISECONDS:
        if(displayType == TimerDisplayType::ONLY)return milliseconds + "ms";
            return (seconds == "0" ? "" : seconds + "s.")
                 + milliseconds + "ms";
    case TimerClockPrecision::MICROSECONDS:
        if(displayType == TimerDisplayType::ONLY)return microseconds + "us";
            return (seconds == "0" ? "" : seconds + "s.")
                 + (milliseconds == "0" ? "" : milliseconds + "ms.")
                 + microseconds + "us";
        return to_string(timer::getEllapsedSeconds()) + "s."
             + to_string(timer::getEllapsedMilliseconds() % 1000) + "ms."
             + to_string(timer::getEllapsedMicroseconds() % 1000) + "us";
    case TimerClockPrecision::NANOSECOND:
        if(displayType == TimerDisplayType::ONLY)return nanoseconds + "ns";
            return (seconds == "0" ? "" : seconds + "s.")
                 + (milliseconds == "0" ? "" : milliseconds + "ms.")
                 + (microseconds == "0" ? "" : microseconds + "us.")
                 + nanoseconds + "ns";
    default:
        return "";
    }
}

Timer::Timer(bool startOnCreation) {
    if(startOnCreation) {
        this->start();
    }
}

void Timer::start() {
    this->startTime = high_resolution_clock::now();
}

void Timer::stop() {
    this->endTime = high_resolution_clock::now();
    if(this->logTimeOnStop) {
        logType(this->timeType);
        logInfo(this->getEllapsedTime(timer::TimerClockPrecision::NANOSECOND));
        logType();
    }
}

int Timer::getEllapsedSeconds() {
    return duration_cast<seconds>(endTime - startTime).count();
}

int Timer::getEllapsedMilliseconds() {
    return duration_cast<milliseconds>(endTime - startTime).count();
}

int Timer::getEllapsedMicroseconds() {
    return duration_cast<microseconds>(endTime - startTime).count();
}

int Timer::getEllapsedNanoseconds() {
    return duration_cast<nanoseconds>(endTime - startTime).count();
}

string Timer::getEllapsedTime(timer::TimerClockPrecision precision, timer::TimerDisplayType displayType) {
    string seconds = to_string(this->getEllapsedSeconds());
    string milliseconds = to_string(this->getEllapsedMilliseconds() % 1000);
    string microseconds = to_string(this->getEllapsedMicroseconds() % 1000);
    string nanoseconds = to_string(this->getEllapsedNanoseconds() % 1000);
    switch (precision)
    {
    case timer::TimerClockPrecision::SECONDS:
        return seconds + "s";
    case timer::TimerClockPrecision::MILLISECONDS:
        if(displayType == timer::TimerDisplayType::ONLY)return milliseconds + "ms";
            return (seconds == "0" ? "" : seconds + "s.")
                 + milliseconds + "ms";
    case timer::TimerClockPrecision::MICROSECONDS:
        if(displayType == timer::TimerDisplayType::ONLY)return microseconds + "us";
            return (seconds == "0" ? "" : seconds + "s.")
                 + (milliseconds == "0" ? "" : milliseconds + "ms.")
                 + microseconds + "us";
        return to_string(this->getEllapsedSeconds()) + "s."
             + to_string(this->getEllapsedMilliseconds() % 1000) + "ms."
             + to_string(this->getEllapsedMicroseconds() % 1000) + "us";
    case timer::TimerClockPrecision::NANOSECOND:
        if(displayType == timer::TimerDisplayType::ONLY)return nanoseconds + "ns";
            return (seconds == "0" ? "" : seconds + "s.")
                 + (milliseconds == "0" ? "" : milliseconds + "ms.")
                 + (microseconds == "0" ? "" : microseconds + "us.")
                 + nanoseconds + "ns";
    default:
        return "";
    }
}