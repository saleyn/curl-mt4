# CURL interface API for MT4 #

This library is used as the intermediate marshaling layer between
MetaTrader (MT4) and libcurl.dll.

It's intended for 32-bit builds by Visual Studio C++ IDE.

## Prerequisites ##

1. Obtain and build the `libcurl.dll` using Visual Studio.
2. Update project library to include directories of the
   libcurl's `include` and `library` paths.
3. Make sure you have redistributable Visual Studio
   [runtime](https://support.microsoft.com/en-us/help/2977003/the-latest-supported-visual-c-downloads)
   installed on computers running libcurl.

## Installation ##

1. Place `libcurl.dll` and `curl-mt4.dll` files in the `Libraries` directory
   of your MT4 instance.
2. Place `inet-curl.mqh` in the `Include` directory of your MT4 instance.
3. Add `#include <inet-curl.mqh>` in the source code of your scripts/indicators/EAs
   that you intend to call `curl-mt4`'s functions.

## AUTHOR ##

Serge Aleynikov &lt;saleyn at gmail dot com&gt;

## LICENSE ##

The project is released under APACHE 2.0 license.
