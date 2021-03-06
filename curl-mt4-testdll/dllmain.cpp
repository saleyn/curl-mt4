// dllmain.cpp : Defines the entry point for the DLL application.

#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers
// Windows Header Files:
#include <windows.h>

#ifdef BUILDING_CURL_STATIC
    #define MT4EXPORT
#else
    #ifdef BUILDING_MT4CURL
        #define MT4EXPORT __declspec(dllexport)
    #else
        #define MT4EXPORT __declspec(dllimport)
    #endif
#endif

#include <curl/curl.h>

extern "C"
{
    BOOL APIENTRY DllMain(HMODULE hModule, DWORD  ul_reason_for_call, LPVOID lpReserved)
    {
        switch (ul_reason_for_call)
        {
            case DLL_PROCESS_ATTACH:
            case DLL_THREAD_ATTACH:
            case DLL_THREAD_DETACH:
            case DLL_PROCESS_DETACH:
                break;
        }
        return TRUE;
    }

    MT4EXPORT int  APIENTRY LibInit()     { return reinterpret_cast<long>(curl_easy_init()); }
    MT4EXPORT void APIENTRY LibFin(int h) { curl_easy_cleanup(reinterpret_cast<CURL*>(h));   }
}
