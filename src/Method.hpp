#ifndef METHOD_HPP
#define METHOD_HPP

#include "Core/Macros.h"
#include <tuple>

namespace PandoraEngine
{
    template <typename Function, typename... Args>
    class DLL Method
    {
    private:
        Function && _function;
        std::tuple<Args...> _args;
    public:
        Method(Function && function, Args... args) : _function(std::forward<Function>(function)), _args(std::forward<Args>(args)...) {}

        auto operator()()
        {
            return std::apply(_function, _args);
        }

        template <typename... Args_>
        auto operator()(Args_... args)
        {
            return _function(std::forward<Args_>(args)...);
        }

        auto invoke()
        {
            return std::apply(_function, _args);
        }

        template <typename... Args_>
        auto invoke(Args_... args)
        {
            return _function(std::forward<Args_>(args)...);
        }
    };
} // namespace PandoraEngine


#endif // METHOD_HPP