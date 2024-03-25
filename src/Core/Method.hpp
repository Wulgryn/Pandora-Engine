#pragma once

/// @brief A class to store a function and invoke it later or use as variable.
/// @tparam ReturnValue The return value of the function.
/// @tparam ...Args The paramteres of the function.
template <typename ReturnValue = void, typename... Args>
class Method
{
private:
    ReturnValue (*function)(Args... args);
public:
    /// @brief The constructor of the class.
    /// @param function The function to store.
    Method(ReturnValue (*function)(Args... args))
    {
        this->function = function;
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
};