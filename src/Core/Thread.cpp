#include "Thread.hpp"
#include <thread>
namespace Thread
{
    int GetCurrentThreadID()
    {
        return std::hash<std::thread::id>{}(std::this_thread::get_id());
    }
}