//------------------------------------------------------------------------------
/// \file      curl-mt4.h
/// \author    Serge Aleynikov
/// \copyright (c) 2018, Serge Aleynikov
//------------------------------------------------------------------------------
/// \brief     Defines the API of calling `libcurl` functions from `MT4`
//------------------------------------------------------------------------------
#pragma once

// When building curl-mt4.dll, add BUILDING_MT4CURL pre-processor define
#if (defined(_WIN32)||defined(_WIN64)) && !defined(BUILDING_MT4CURL_STATIC)
  #ifndef WINAPI
  #define WINAPI __stdcall
  #endif

  #ifdef BUILDING_MT4CURL_DLL
    #define APIEXPORT(R) __declspec(dllexport) R WINAPI
  #else
    #define APIEXPORT(R) __declspec(dllimport) R WINAPI
  #endif
#else
  #ifndef APIEXPORT
    #define APIEXPORT(R) R WINAPI
  #endif
  #ifndef WINAPI
    #define WINAPI
  #endif
#endif

extern "C" {

    enum CurlOptions {
        OPT_NONE             = 0, 
        OPT_FOLLOW_REDIRECTS = 1 << 0,
        CURL_OPT_NOBODY      = 1 << 1, // Download no body
        OPT_DEBUG            = 1 << 2,
    };

    enum class CurlMethod : int {
        GET,
        POST,
        POST_JSON,
        POST_FORM,
        DEL,
        PUT,
    };

    using CurlHandle = void*;
    using uint       = unsigned int;

    /// Initialize CURL library
    APIEXPORT(CurlHandle)  CurlInit();
    /// Finalize CURL library
    APIEXPORT(void)        CurlFinalize(CurlHandle handle);

    /// Set URL prior to calling `CurlExecute()`
    APIEXPORT(int)         CurlSetURL     (CurlHandle handle, const char* url);
    /// Set request timeout in seconds
    APIEXPORT(int)         CurlSetTimeout (CurlHandle handle, int timeout_secs);
    /// Add '\n' delimited request headers
    APIEXPORT(void)        CurlAddHeaders (CurlHandle handle, const char* headers);
    /// Add a single request header
    APIEXPORT(void)        CurlAddHeader  (CurlHandle handle, const char* header);
    /// Execute a request on the server
    /// @param code       resulting code (optional if passed nullptr) returned by the server (200 = success)
    /// @param res_length resulting response body length (optional if passed nullptr)
    /// @param opts       request options (OR'd CurlOptions)
    /// @param post_data  request body for POST requests
    APIEXPORT(int)         CurlExecute    (CurlHandle handle, int* code, int* res_length,
                                           CurlMethod method=CurlMethod::GET,
                                           unsigned int opts=uint(OPT_NONE), const char* post_data=nullptr,
                                           int timeout_secs=10);
    /// Return response body length
    APIEXPORT(int)         CurlGetDataSize(CurlHandle handle);
    /// Return response data, where `buf` size must be pre-allocated to `res_length`
    /// returned by `CurlExecute()`
    APIEXPORT(int)         CurlGetData    (CurlHandle handle, char* buf, int size);
    /// Get count of response headers
    APIEXPORT(size_t)      CurlTotRespHeaders(CurlHandle handle);
    /// Get `idx`th response header.
    /// If the header's length is greater than `buflen`, the function doesn't update `buf`.
    /// Return the actual length of the header or -1 if `idx` is invalid.
    APIEXPORT(int)         CurlGetRespHeader(CurlHandle handle, int idx, char* key, size_t buflen);
    /// Get description of the `err` code
    APIEXPORT(int)         CurlLastError  (CurlHandle handle, int err, char* errs, int max_size);
    /// Set debug level
    APIEXPORT(void)        CurlDbgLevel   (CurlHandle handle, int level);
    /// Return size of buffer needed to fetch debug info
    APIEXPORT(int)         CurlDbgInfoSize(CurlHandle handle);
    /// Return debug info where `buf` size must be pre-allocated to length returned by `CurlDbgInfoSize()`
    APIEXPORT(int)         CurlDbgInfo    (CurlHandle handle, char* buf, int size);

#ifndef NO_CURLMT4_UNICODE_API
    /// Set URL prior to calling `CurlExecute()`
    APIEXPORT(int)         CurlSetURLW    (CurlHandle handle, const wchar_t* url);
    /// Add '\n' delimited request headers
    APIEXPORT(void)        CurlAddHeadersW(CurlHandle handle, const wchar_t* headers);
    /// Add a single request header
    APIEXPORT(void)        CurlAddHeaderW (CurlHandle handle, const wchar_t* header);
    /// Get `idx`th response header.
    /// If the header's length is greater than `buflen`, the function doesn't update `buf`.
    /// Return the actual length of the header or -1 if `idx` is invalid.
    APIEXPORT(int)        CurlGetRespHeaderW(CurlHandle handle, int idx, wchar_t* buf, size_t buflen);

    /// Execute a request on the server
    /// @param code       resulting code (optional if passed nullptr) returned by the server (200 = success)
    /// @param res_length resulting response body length (optional if passed nullptr)
    /// @param opts       request options (OR'd CurlOptions)
    /// @param post_data  request body for POST requests
    APIEXPORT(int)         CurlExecuteW   (CurlHandle handle, int* code, int* res_length,
                                                   CurlMethod method = CurlMethod::GET,
                                                   unsigned int opts = 0, const wchar_t* post_data = nullptr,
                                                   int  timeout_secs = 10);
    /// Return response data, where `buf` size must be pre-allocated to `res_length` returned by `CurlExecute()`
    APIEXPORT(int)         CurlGetDataW   (CurlHandle handle, wchar_t* buf, int size);
    /// Get description of the `err` code
    APIEXPORT(int)         CurlLastErrorW (CurlHandle handle, int err, wchar_t* errs, int max_size);
    /// Return debug info where `buf` size must be pre-allocated to length returned by `CurlDbgInfoSize()`
    APIEXPORT(int)         CurlDbgInfoW   (CurlHandle handle, wchar_t* buf, int size);
#endif

} // extern