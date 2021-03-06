// curl-mt4.cpp : Defines the entry point for the console application.
//

#define _CRT_SECURE_NO_WARNINGS

#include <string>
#include <string.h>
#include <vector>
#include <iostream>
#include <curl-mt4.h>

std::string StrError(void* curl, int code) {
    char buf[256];
    int n = CurlLastError(curl, code, buf, sizeof(buf));
    return std::string(buf, n);
}

int main(int argc, char* argv[])
{
    auto curl = CurlInit();

    if (!curl) {
        std::cerr << "Error initializing curl (CurlInit)!" << std::endl;
        return 1;
    }

    std::string url, post_data;
    auto method = CurlMethod::GET;
    int  opts   = 0;
    int  dbg    = 0;

    for (auto i = 1; i < argc; ++i) {
        if (!strcmp(argv[i], "-h") || !strcmp(argv[i], "--help")) {
            std::cerr << "Usage: " << argv[0]
                      << " [-h|--help] [-X POST] [-H Header] [-d JsonPostData]"
                         " [-v [N]] [-t TimeoutSecs] URL"
                      << std::endl;
            return 1;
        }
        if (strcmp(argv[i], "-H") == 0 && i < argc-1) {
          /*
            auto found = strchr(argv[++i], '\n');
            if (!found) {
              std::wstring h(argv[i], argv[i] + strlen(argv[i]));
              CurlAddHeaderW(curl, h.c_str());
            } else
              CurlAddHeaders(curl, argv[i]);
          */
            CurlAddHeaders(curl, argv[++i]);
        }
        else if (strcmp(argv[i], "-X") == 0 && i < argc - 1) {
            if (strcmp(argv[++i], "POST") == 0)
                method = CurlMethod::POST_JSON;
            else {
                std::cerr << "Invalid -X argument (method): " << argv[i] << std::endl;
                return 2;
            }
        } else if (strcmp(argv[i], "-d") == 0 && i < argc-1)
            post_data = argv[++i];
        else if (strcmp(argv[i], "-v") == 0) {
            opts |= OPT_DEBUG;
            if (i < argc-1 && argv[i+1][0] != '-') {
                try   { dbg += std::stoi(argv[++i]); }
                catch (...)
                {
                    std::cerr << "Invalid -v argument (verbose): " << argv[i] << std::endl;
                    return 2;
                }
            } else
              dbg++;
        } else if (strcmp(argv[i], "-t") == 0 && i < argc - 1) {
            auto timeout = std::stoi(argv[++i]);
            auto res = CurlSetTimeout(curl, timeout);
            if (res != 0)
                std::cerr << "Error setting timeout: " << res << std::endl;
        } else if (argv[i][0] == '-') {
            std::cerr << "Invalid argument: " << argv[i] << " (i=" << i << ", argc=" << argc << ")" << std::endl;
            return 1;
        } else
            url = argv[i];
    }

    if (method == CurlMethod::POST_JSON && post_data.empty())
        method = CurlMethod::POST;

    CurlDbgLevel(curl, dbg);

    int res;

    if ((res = CurlSetURL(curl, url.c_str())) != 0) {
        std::cerr << "Error in CurlSetURL: " << StrError(curl, res) << std::endl;
        return 2;
    }

    int code, length;

    std::wstring data(post_data.begin(), post_data.end());

    if ((res = CurlExecuteW(curl, &code, &length, method, opts, post_data.empty() ? nullptr : data.c_str())) != 0) {
        std::cerr << "Error in CurlExecute: (" << res << ") " << StrError(curl, res) << std::endl;
        return 2;
    }

    if (OPT_DEBUG & opts) {
        std::string h;
        int n = CurlTotRespHeaders(curl);
        if (n) {
            std::cerr << "===== Resp Headers " << n << " =====" << std::endl;
            for(int i=0; i < n; ++i) {
                std::vector<wchar_t> s;
                s.resize(CurlGetRespHeaderW(curl, i, nullptr, 0)+1);
                CurlGetRespHeaderW(curl, i, &s[0], s.size());
                std::wcerr << L"  | " << std::wstring(s.begin(), s.end()) << std::endl;
            }
            std::cerr.flush();
            std::cerr << "===========================" << std::endl;
        }
        std::string v;
        v.resize(CurlDbgInfoSize(curl));
        CurlDbgInfo(curl, &v[0], v.size());
        std::cerr << "===== Debug Info =====" << std::endl;
        std::cerr.write(&v[0], v.size());
        std::cerr.flush();
        std::cerr << "\n======================" << std::endl;
    }

    if (length > 0) {
        std::vector<wchar_t> s;
        s.resize(length);
        CurlGetDataW(curl, &s[0], s.size());
        std::wcout << std::wstring(s.begin(), s.end()) << std::endl;
        std::wcout.flush();
    }
    else
        std::cout << "Server response: " << code << std::endl;

    return 0;
}
