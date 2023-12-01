#ifdef _WIN32
    #define DLL __declspec(dllexport)
#elif __linux__
    #define DLL __attribute__((visibility("default")))
#else
    #define DLL
#endif