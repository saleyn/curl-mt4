// curl-mt4.cpp : Defines the entry point for the console application.
//

#define _CRT_SECURE_NO_WARNINGS

//#include "stdafx.h"

#include <stdio.h>
#include <curl/curl.h>
#include <string>

static size_t write_data(void *ptr, size_t size, size_t nmemb, void *stream)
{
    size_t written = fwrite(ptr, size, nmemb, (FILE*)stream);
    return written;
}

int main(int argc, char *argv[])
{
    static auto pagefilename = "page.out";

    if (argc < 2 || argc >= 2 && argv[1] == std::string("-h")) {
        printf("Usage: %s <URL>\n", argv[0]);
        return 1;
    }

    curl_global_init(CURL_GLOBAL_ALL);

    /* init the curl session */
    auto curl_handle = curl_easy_init();

    curl_easy_setopt(curl_handle, CURLOPT_URL,  argv[1]); // Set URL to get here
    curl_easy_setopt(curl_handle, CURLOPT_VERBOSE,   1L); // Switch on full protocol/debug output while testing
    curl_easy_setopt(curl_handle, CURLOPT_NOPROGRESS,1L); // disable progress meter

    /* send all data to this function  */
    curl_easy_setopt(curl_handle, CURLOPT_WRITEFUNCTION, write_data);

    /* open the file */
    auto pagefile = fopen(pagefilename, "wb");

    if (pagefile) {
        /* write the page body to this file handle */
        curl_easy_setopt(curl_handle, CURLOPT_WRITEDATA, pagefile);

        /* get it! */
        curl_easy_perform(curl_handle);

        /* close the header file */
        fclose(pagefile);
    }

    curl_easy_cleanup(curl_handle); // cleanup curl stuff
    curl_global_cleanup();

    return 0;
}
