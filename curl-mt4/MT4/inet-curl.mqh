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
  int   CurlInit();
  void  CurlFinalize   (int handle);

  int   CurlSetURLW    (int handle, string url);
  int   CurlSetTimeout (int handle, int timeout_secs);
  void  CurlAddHeaderW (int handle, string header);
  void  CurlAddHeadersW(int handle, string headers); // '\n' delimited headers
  int   CurlExecuteW   (int handle, int& code, int& res_length, CURL_METHOD method=CURL_GET,
                        unsigned int opts=0, string post_data=NULL);
  int   CurlGetDataSize(int handle);
  int   CurlGetData    (int handle, char& buf[], int size);
  int   CurlGetDataW   (int handle, string& buf, int size);
  int   CurlLastErrorW (int handle, int err, string& errs, int max_size);

  void  CurlDbgLevel   (int handle, int level);
  int   CurlDbgInfoSize(int handle);
  void  CurlDbgInfoW   (int handle, string& buf, int size);
#import
//+------------------------------------------------------------------+

#endif // __INET_CURL_MQH__