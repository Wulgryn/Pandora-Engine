#ifndef MACROS_H
#define MACROS_H

#define SAFE_DELETE(p) { if(p) { delete (p); (p) = nullptr; } }
#define SAFE_DELETE_ARRAY(p) { if(p) { delete[] (p); (p) = nullptr; } }

#define SAFE_RELEASE(p) { if(p) { (p)->Release(); (p) = nullptr; } }


#ifdef PANDORA_ENGINE

#ifdef _WIN32
#define DLL __declspec(dllexport)
#else
#define DLL __attribute__((visibility("default")))
#endif

#else

#ifdef _WIN32
#define DLL __declspec(dllimport)
#else
#define DLL __attribute__((visibility("default")))
#endif

#endif

#ifdef _WIN32
#define NOINLINE __declspec(noinline)
#else
#define NOINLINE __attribute__((noinline))
#endif

#endif // MACROS_H