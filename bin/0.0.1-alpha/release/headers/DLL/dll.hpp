#ifdef _WIN32
    #ifdef BUILD_DLL
        #define DLL __declspec(dllexport)
    #else
        #define DLL __declspec(dllimport)
    #endif
#elif __linux__
    #define DLL __attribute__((visibility("default")))
#else
    #define DLL
#endif