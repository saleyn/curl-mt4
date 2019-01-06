//+------------------------------------------------------------------+
//|                                                    inet-curl.mqh |
//|                              Copyright (c) 2018, Serge Aleynikov |
//|                                           https://www.mqtllc.com |
//+------------------------------------------------------------------+
#property copyright "Copyright (c) 2018, Serge Aleynikov"
#property link      "https://www.mqtllc.com"
#property strict

#ifndef __INET_CURL_MQH__
#define __INET_CURL_MQH__

//+------------------------------------------------------------------+
//| defines                                                          |
//+------------------------------------------------------------------+
enum CURL_OPTIONS {
  CURL_OPT_NONE             = 0, 
  CURL_OPT_FOLLOW_REDIRECTS = 1 << 0,
  CURL_OPT_DEBUG            = 1 << 1,
};

enum CURL_METHOD {
  CURL_GET,
  CURL_POST_JSON,
  CURL_POST_FORM,
  CURL_DEL,
  CURL_PUT,
};

//+------------------------------------------------------------------+
//| DLL imports                                                      |
//+------------------------------------------------------------------+
#import "curl-mt4.dll"
  int   CurlInit();                     ///< Initialize CURL library
  void  CurlFinalize   (int handle);    ///< Finalize CURL library

  /// Set URL prior to calling `CurlExecute()`
  int   CurlSetURLW    (int handle, string url);
  
  /// Set request timeout in seconds
  int   CurlSetTimeout (int handle, int timeout_secs);

  /// Add a single request header
  void  CurlAddHeaderW (int handle, string header);

  /// Add '\n' delimited request headers
  void  CurlAddHeadersW(int handle, string headers);

  /// Execute a request on the server
  /// @param code       resulting code (optional if passed nullptr) returned by the server (200 = success)
  /// @param res_length resulting response body length (optional if passed nullptr)
  /// @param opts       request options (OR'd CurlOptions)
  /// @param post_data  request body for POST requests
  int   CurlExecuteW   (int handle, int& code, int& res_length, CURL_METHOD method=CURL_GET,
                        unsigned int opts=0, string post_data=NULL);

  /// Return response body length
  int   CurlGetDataSize(int handle);

  /// Return response data, where `buf` size must be pre-allocated to `res_length`
  /// returned by `CurlExecute()`. Note that `CurlGetData()` function doesn't create an
  /// extra copy of data compared to `CurlGetDataW()`.
  int   CurlGetData    (int handle, char& buf[], int size);
  int   CurlGetDataW   (int handle, string& buf, int size);

  /// Get description of the `err` code
  int   CurlLastErrorW (int handle, int err, string& errs, int max_size);

  void  CurlDbgLevel   (int handle, int level);  //< Set debug level

  /// Return size of buffer needed to fetch debug info
  int   CurlDbgInfoSize(int handle);

  /// Return debug info where `buf` size must be pre-allocated to length
  /// returned by `CurlDbgInfoSize()`
  void  CurlDbgInfoW   (int handle, string& buf, int size);

#import
//+------------------------------------------------------------------+

#endif // __INET_CURL_MQH__