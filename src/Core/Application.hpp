
namespace Application
{
    extern bool exitOnLastWindowClosed;


    /** 
    *  @brief The main entry point for the application.
    * 
    *  @note This function starts the main thread.
    * 
    *  @return The exit code of the application.
    */
    int Start();

    /**
     * @brief Same as Start() but with a step-by-step approach.
     * 
     * @return The exit code of the application or 0 by default. 
     */
    int Step(bool pollEvents = true);

    void Exit(int exitCode = 0);

    int GetMainThreadID();

    void SetUpdateFunction(void (*updateFunction)());

    class ExitCodes
    {
    
    };
}