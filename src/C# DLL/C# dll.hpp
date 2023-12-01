#define EXTERN_C extern "C"

#ifdef _WIN32
    #define CSDLL extern "C" __declspec(dllexport)
    #define DLL_EXPORT __declspec(dllexport)
#elif __linux__
    #define CSDLL extern "C" __attribute__((visibility("default")))
    #define DLL_EXPORT __attribute__((visibility("default")))
#else
    #define CSDLL
    #define DLL_EXPORT
#endif
