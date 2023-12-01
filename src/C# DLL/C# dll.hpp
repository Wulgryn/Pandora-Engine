/**
 * Macro definition for exporting functions from a DLL.
 * 
 * This macro is used to declare functions as externally visible and export them from a DLL.
 * It is typically used in the header file of a DLL to indicate which functions should be accessible from outside the DLL.
 * The functions declared with this macro will be decorated with the appropriate export attributes.
 */
#define CSDLL extern "C" __declspec(dllexport)
#define EXTERN_C extern "C"
#define DLL_EXPORT __declspec(dllexport)