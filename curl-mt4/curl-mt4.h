//------------------------------------------------------------------------------
/// \file      curl-mt4.h
/// \author    Serge Aleynikov
/// \copyright (c) 2018, Serge Aleynikov
//------------------------------------------------------------------------------
/// \brief     Defines the API of calling `libcurl` functions from `MT4`
//------------------------------------------------------------------------------
#pragma once

// When building curl-mt4.dll, add BUILDING_MT4CURL pre-processor define
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

    using CurlHandle = void*;
    using uint       = unsigned int;

    /// Initialize CURL library
    MT4EXPORT CurlHandle __stdcall CurlInit();
    /// Finalize CURL library
    MT4EXPORT void       __stdcall CurlFinalize(CurlHandle handle);

    /// Set URL prior to calling `CurlExecute()`
    MT4EXPORT int        __stdcall CurlSetURL     (CurlHandle handle, const char* url);
    /// Set request timeout in seconds
    MT4EXPORT int        __stdcall CurlSetTimeout (CurlHandle handle, int timeout_secs);
    /// Add '\n' delimited request headers
    MT4EXPORT void       __stdcall CurlAddHeaders (CurlHandle handle, const char* headers);
    /// Add a single request header
    MT4EXPORT void       __stdcall CurlAddHeader  (CurlHandle handle, const char* header);
    /// Execute a request on the server
    /// @param code       resulting code (optional if passed nullptr) returned by the server (200 = success)
    /// @param res_length resulting response body length (optional if passed nullptr)
    /// @param opts       request options (OR'd CurlOptions)
    /// @param post_data  request body for POST requests
    MT4EXPORT int        __stdcall CurlExecute    (CurlHandle handle, int* code, int* res_length,
                                                   CurlMethod method=GET,
                                                   uint opts=uint(OPT_NONE), const char* post_data=nullptr);
    /// Return response body length
    MT4EXPORT int        __stdcall CurlGetDataSize(CurlHandle handle);
    /// Return response data, where `buf` size must be pre-allocated to `res_length`
    /// returned by `CurlExecute()`
    MT4EXPORT int        __stdcall CurlGetData    (CurlHandle handle, char* buf, int size);
    /// Get description of the `err` code
    MT4EXPORT int        __stdcall CurlLastError  (CurlHandle handle, int err, char* errs, int max_size);
    /// Set debug level
    MT4EXPORT void       __stdcall CurlDbgLevel   (CurlHandle handle, int level);
    /// Return size of buffer needed to fetch debug info
    MT4EXPORT int        __stdcall CurlDbgInfoSize(CurlHandle handle);
    /// Return debug info where `buf` size must be pre-allocated to length returned by `CurlDbgInfoSize()`
    MT4EXPORT int        __stdcall CurlDbgInfo    (CurlHandle handle, char* buf, int size);

#ifndef NO_CURLMT4_UNICODE_API
    /// Set URL prior to calling `CurlExecute()`
    MT4EXPORT int        __stdcall CurlSetURLW    (CurlHandle handle, const wchar_t* url);
    /// Add '\n' delimited request headers
    MT4EXPORT void       __stdcall CurlAddHeadersW(CurlHandle handle, const wchar_t* headers);
    /// Add a single request header
    MT4EXPORT void       __stdcall CurlAddHeaderW (CurlHandle handle, const wchar_t* header);
    /// Execute a request on the server
    /// @param code       resulting code (optional if passed nullptr) returned by the server (200 = success)
    /// @param res_length resulting response body length (optional if passed nullptr)
    /// @param opts       request options (OR'd CurlOptions)
    /// @param post_data  request body for POST requests
    MT4EXPORT int        __stdcall CurlExecuteW   (CurlHandle handle, int* code, int* res_length,
                                                   CurlMethod method = GET,
                                                   unsigned int opts = 0, const wchar_t* post_data = nullptr);
    /// Return response data, where `buf` size must be pre-allocated to `res_length` returned by `CurlExecute()`
    MT4EXPORT int        __stdcall CurlGetDataW   (CurlHandle handle, wchar_t* buf, int size);
    /// Get description of the `err` code
    MT4EXPORT int        __stdcall CurlLastErrorW (CurlHandle handle, int err, wchar_t* errs, int max_size);
    /// Return debug info where `buf` size must be pre-allocated to length returned by `CurlDbgInfoSize()`
    MT4EXPORT int        __stdcall CurlDbgInfoW   (CurlHandle handle, wchar_t* buf, int size);
#endif

} // extern