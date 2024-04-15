#pragma once
#include "Method.hpp"
namespace Application
{
    extern bool exitOnLastWindowClosed;


    /** 
    *  @brief The main entry point for the application.
    *  @param stopOnExit If true, the application will wait for and extra input after stopping.
    *  @note This function starts the main thread.
    *  
    *  @return The exit code of the application.
    */
    int Start(bool stopOnExit = true);

    /**
     * @brief Same as Start() but with a step-by-step approach.
     * 
     * @return The exit code of the application or 0 by default.
     * 
     * @note If you have windows open, you MUST call this from the main thread. 
     */
    int Step(bool pollEvents = true);

    void Exit(int exitCode = 0);

    int GetMainThreadID();

    void SetUpdateFunction(void (*updateFunction)());

    void EnqueueInvoke(Method<void> method);

    class ExitCodes
    {
    
    };
}