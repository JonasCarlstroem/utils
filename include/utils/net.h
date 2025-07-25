#pragma once
#include <string>

#ifndef _WINSOCK_INCLUDED_
#define _WINSOCK_INCLUDED_
#include <WinSock2.h>
#include <WS2tcpip.h>

#pragma comment(lib, "Ws2_32.lib")
#endif

#define DEFAULT_IP "0.0.0.0"
#define DEFAULT_PORT 8080

using string = std::string;

namespace net {

struct socket_error {
    int error_code;
    string message;

    operator string() { return message; }

    operator int() { return error_code; }
};

socket_error get_socket_error() {
    int code = WSAGetLastError();
    char* s  = NULL;
    FormatMessageA(
        FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM |
            FORMAT_MESSAGE_IGNORE_INSERTS,
        NULL, code, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPSTR)&s, 0,
        NULL
    );

    string ret(s);
    LocalFree(s);

    return {code, ret};
}

string url_decode(const string& encoded) {
    std::ostringstream decoded;
    for (size_t i = 0; i < encoded.length(); ++i) {
        if (encoded[i] == '%') {
            if (i + 2 < encoded.length()) {
                string hex = encoded.substr(i + 1, 2);
                char ch    = static_cast<char>(std::stoi(hex, nullptr, 16));
                decoded << ch;
                i += 2;
            }
        } else if (encoded[i] == '+') {
            decoded << ' ';
        } else {
            decoded << encoded[i];
        }
    }
    return decoded.str();
}

} // namespace net