#include "DLL/dll.hpp"
#include <string>
#include <chrono>

namespace utils
{
    /**
     * @brief A timer namespace for measuring elapsed time.
     */
    namespace timer
    {
        /**
         * @brief Enum class for specifying the precision of the timer clock.
         */
        enum class TimerClockPrecision {
            SECONDS,          ///< Precision in seconds
            MILLISECONDS,     ///< Precision in milliseconds
            MICROSECONDS,     ///< Precision in microseconds
            NANOSECOND        ///< Precision in nanoseconds
        };

        /**
         * @brief Enum class for specifying the display type of the elapsed time.
         */
        enum class TimerDisplayType {
            ONLY,    ///< Display only the elapsed time
            ALL      ///< Display all time units (seconds, milliseconds, microseconds, nanoseconds)
        };

        /**
         * @brief Starts the timer.
         */
        DLL void start();

        /**
         * @brief Stops the timer.
         */
        DLL void stop();

        /**
         * @brief Gets the elapsed time in seconds.
         * @return The elapsed time in seconds.
         */
        DLL int getEllapsedSeconds();

        /**
         * @brief Gets the elapsed time in milliseconds.
         * @return The elapsed time in milliseconds.
         */
        DLL int getEllapsedMilliseconds();

        /**
         * @brief Gets the elapsed time in microseconds.
         * @return The elapsed time in microseconds.
         */
        DLL int getEllapsedMicroseconds();

        /**
         * @brief Gets the elapsed time in nanoseconds.
         * @return The elapsed time in nanoseconds.
         */
        DLL int getEllapsedNanoseconds();

        /**
         * @brief Gets the elapsed time as a string.
         * @param precision The precision of the timer clock (default: TimerClockPrecision::MILLISECONDS).
         * @param displayType The display type of the elapsed time (default: TimerDisplayType::ALL).
         * @return The elapsed time as a string.
         */
        DLL std::string getEllapsedTime(TimerClockPrecision precision = TimerClockPrecision::MILLISECONDS, timer::TimerDisplayType displayType = TimerDisplayType::ALL);
    }
    /**
     * @class Timer
     * @brief A class for measuring elapsed time.
     */
    class DLL Timer
    {
    private:
        /**
         * @brief The start time of the timer.
         */
        std::chrono::high_resolution_clock::time_point startTime;

        /**
         * @brief The end time of the timer. 
         */
        std::chrono::high_resolution_clock::time_point endTime;   
    public:

        /**
         * @brief Construct a new Timer object.
         * @param startOnCreation Whether to start the timer on creation (default: false).
         */
        Timer(bool startOnCreation = false);

        /**
         * @brief The type of the timer.
         */
        std::string timeType = "TIMER";

        /**
         * @brief Whether to log the time when the timer stops.
         */
        bool logTimeOnStop = true;

        /**
         * @brief Start the timer.
         */
        void start();

        /**
         * @brief Stop the timer.
         */
        void stop();

        /**
         * @brief Get the elapsed time in seconds.
         * @return The elapsed time in seconds.
         */
        int getEllapsedSeconds();

        /**
         * @brief Get the elapsed time in milliseconds.
         * @return The elapsed time in milliseconds.
         */
        int getEllapsedMilliseconds();

        /**
         * @brief Get the elapsed time in microseconds.
         * @return The elapsed time in microseconds.
         */
        int getEllapsedMicroseconds();

        /**
         * @brief Get the elapsed time in nanoseconds.
         * @return The elapsed time in nanoseconds.
         */
        int getEllapsedNanoseconds();

        /**
         * @brief Get the elapsed time as a formatted string.
         * @param precision The precision of the timer.
         * @param displayType The display type of the timer.
         * @return The elapsed time as a formatted string.
         */
        std::string getEllapsedTime(timer::TimerClockPrecision precision = timer::TimerClockPrecision::MILLISECONDS, timer::TimerDisplayType displayType = timer::TimerDisplayType::ALL);
    };
}