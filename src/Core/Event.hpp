#pragma once
#include "Method.hpp"
#include <vector>

template <typename... Args>
class Event
{
private:
    std::vector<Method<void,Args...>> methods;
public:

    /**
    @brief Adds a method to the event.
    @param method The method to be added.
    @return Event* The event itself.
    @exception No built-in.
    @see Method
    @details 
    <strong>Examples<strong/><p/>
    - Basic useage:
    @code{.cpp}
    #include <iostream>

    void test()
    {
        std::cout << "Called test()." << std::endl;
    }

    int main()
    {
        Event event;
        event += test;
        Method method = test;
        event += method;
        event.Invoke();
        return 0;
    }
    @endcode
    Output:
    <br/>`Called test().`
    <br/>`Called test().`<p/>

    - Using lambda:
    @code{.cpp}
    #include <iostream>

    int main()
    {
        Event event;
        event += +[](){std::cout << "Called lambda." << std::endl;};
        Method method = +[](){std::cout << "Called lambda2." << std::endl;};
        event += method;
        event.Invoke();
        return 0;
    }
    @endcode
    Output:
    <br/>`Called lambda().`
    <br/>`Called lambda2().`<p/>

    - With arguments:
    @code{.cpp}
    #include <iostream>

    void test(int a)
    {
        std::cout << "Called test("<< a << ")." << std::endl;
    }

    int main()
    {
        Event<int> event;
        event += test;
        event += +[](int a){std::cout << "Called lambda("<< a + 1 << ")." << std::endl;};
        Method method = +[](int a){std::cout << "Called lambda("<< a << ")." << std::endl;};
        event.Invoke(2024);
        return 0;
    }
    @endcode
    Output:
    <br/>`Called test(2024).`
    <br/>`Called lambda(2025).`
    <br/>`Called lambda(2024).`<p/>
    */
    Event* operator+=(Method<void,Args...> method)
    {
        methods.push_back(method);
        return this;
    }

    Event* operator=(Method<void,Args...> method)
    {
        methods.clear();
        methods.push_back(method);
        return this;
    }

    // HACK CAUTION: Comment finis.
    /**
     *^  *=======================================================================
     *^  * DESCRIPTION: Finish de comment example
     *^  *=======================================================================
    **/
   
    /**
     * @brief Invokes all methods in the event.
     * @param ...args The arguments to be passed to the methods.
     * @exception No built-in.
     * @details <b>Examples</b><p/>
     * - Basic Example:
     * @code{.cpp}
     * 
     * @endcode
     */
    void Invoke(Args... args)
    {
        for (int i = 0; i < methods.size(); i++)
        {
            methods[i].Invoke(args...);
        }
    }

};