#pragma once

#ifdef BUILDING_MT4CURL
    #define MT4EXPORT __declspec(dllexport)
#else
    #define MT4EXPORT __declspec(dllimport)
#endif

extern "C" {

    enum CurlOptions {
        OPT_NONE             = 0, 
        OPT_FOLLOW_REDIRECTS = 1 << 0,
        OPT_DEBUG            = 1 << 1,
    };

    enum CurlMethod : int {
        GET,
        POST_JSON,
        POST_FORM,
        DEL,
        PUT,
    };

    MT4EXPORT void* __stdcall CurlInit();
    MT4EXPORT void  __stdcall CurlFinalize(void* handle);

    MT4EXPORT int   __stdcall CurlSetURL     (void* handle, const char* url);
    MT4EXPORT int   __stdcall CurlSetTimeout (void* handle, int timeout_secs);
    MT4EXPORT void  __stdcall CurlAddHeaders (void* handle, const char* headers);
    MT4EXPORT void  __stdcall CurlAddHeader  (void* handle, const char* header);
    MT4EXPORT int   __stdcall CurlExecute    (void* handle, int* code, int* res_length, CurlMethod method=CurlMethod::GET,
                                              unsigned int opts=0, const char* post_data=nullptr);
    MT4EXPORT int   __stdcall CurlGetDataSize(void* handle);
    MT4EXPORT int   __stdcall CurlGetData    (void* handle, char* buf, int size);
    MT4EXPORT int   __stdcall CurlLastError  (void* handle, int err, char* errs, int max_size);

    MT4EXPORT void  __stdcall CurlDbgLevel   (void* handle, int level);
    MT4EXPORT int   __stdcall CurlDbgInfoSize(void* handle);
    MT4EXPORT int   __stdcall CurlDbgInfo    (void* handle, char* buf, int size);

#ifndef NO_CURLMT4_UNICODE_API
    MT4EXPORT int   __stdcall CurlSetURLW    (void* handle, const wchar_t* url);
    MT4EXPORT void  __stdcall CurlAddHeadersW(void* handle, const wchar_t* headers);
    MT4EXPORT void  __stdcall CurlAddHeaderW (void* handle, const wchar_t* header);
    MT4EXPORT int   __stdcall CurlExecuteW   (void* handle, int* code, int* res_length, CurlMethod method = CurlMethod::GET,
                                              unsigned int opts = 0, const wchar_t* post_data = nullptr);
    MT4EXPORT int   __stdcall CurlGetDataW   (void* handle, wchar_t* buf, int size);
    MT4EXPORT int   __stdcall CurlLastErrorW (void* handle, int err, wchar_t* errs, int max_size);
    MT4EXPORT int   __stdcall CurlDbgInfoW   (void* handle, wchar_t* buf, int size);
#endif

} // extern