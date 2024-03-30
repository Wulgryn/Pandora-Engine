#pragma once

#include <functional>

/// @brief A class to store a function and invoke it later or use as variable.
/// @tparam ReturnValue The return value of the function.
/// @tparam ...Args The paramteres of the function.
template <typename ReturnValue = void, typename... Args>
class Method
{
private:
   ////ReturnValue (*function)(Args... args);
   std::function<ReturnValue(Args...)> function;
public:
    Method() = default;

    /// @brief The constructor of the class.
    /// @param function The function to store.
    Method(ReturnValue (*function)(Args... args))
    {
        this->function = function;
    };

    Method(std::function<ReturnValue(Args...)> func)
    {
        this->function = func;
    }

    /// @brief The constructor of the class.
    /// @param function The function to store.
    /// @param instance The instance of the class.
    template <typename ClassType>
    Method(ReturnValue (ClassType::*function)(Args... args), ClassType* instance)
    {
        this->function = [=](Args... args) -> ReturnValue
        {
            return (instance->*function)(args...);
        };
    };

    /// @brief Invoke the stored function.
    /// @param ...args The arguments to pass to the function.
    /// @return The return value of the function.
    ReturnValue Invoke(Args... args)
    {
        return function(args...);
    };

    /// @brief Invoke the stored function.
    /// @param ...args The arguments to pass to the function.
    /// @return The return value of the function.
    ReturnValue operator()(Args... args)
    {
        return function(args...);
    };

    /// @brief The assignment operator to store a function.
    /// @param function The function to store.
    /// @return The pointer to the class.
    Method* operator=(ReturnValue (*function)(Args... args))
    {
        this->function = function;
        return this;
    }

    Method operator=(std::function<ReturnValue(Args...)> func)
    {
        this->function = func;
        return this;
    }

    // FIXME: Lambda kifejezések kezelése
    /**
     *& *===============================FIXIT===================================
     *& * DESCRIPTION: Kezelje a lambda kifejezéseket és az osztály függvényeket is.
     *& * HINT: [=](){}; [&](){}; [&parameter](){} és &Class::Function; a funtion típust visszacsinálni sajátra
     *& *=======================================================================
    **/
};