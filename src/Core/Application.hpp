
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

    void Exit(int exitCode = 0);

    int GetMainThreadID();

    class ExitCodes
    {
    
    };
}