#pragma once

#ifdef BUILDING_MT4CURL
    #define MT4EXPORT __declspec(dllexport)
#else
    #define MT4EXPORT __declspec(dllimport)
#endif

extern "C" {

    MT4EXPORT void* _stdcall CurlInit();
    MT4EXPORT void  _stdcall CurlFinalize(void* handle);

    MT4EXPORT int   _stdcall CurlSetURL     (void* handle, const char* url);
    MT4EXPORT void  _stdcall CurlSetHeaders (void* handle, const char* header);
    MT4EXPORT int   _stdcall CurlExecute    (void* handle, const char* method, int& code);
    MT4EXPORT int   _stdcall CurlGetDataSize(void* handle);
    MT4EXPORT int   _stdcall CurlGetData    (void* handle, char* buf, int size);
    MT4EXPORT int   _stdcall CurlError      (int err, char* errs, int max_size);

} // extern