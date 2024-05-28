#ifndef KEYAUTH_HOOKS_H
#define KEYAUTH_HOOKS_H

#include <winsock2.h>
#include <windows.h>
#include <cstdint>
#include <string>
#include <iostream>

typedef INT (WSAAPI* connect_t)(SOCKET s, const sockaddr *name, int namelen);
typedef INT (WSAAPI* recv_t)(SOCKET s, char *buf, int len, int flags);
typedef INT (WSAAPI* send_t)(SOCKET s, const char *buf, int len, int flags);
typedef INT (WSAAPI* getaddrinfo_t)(PCSTR pNodeName, PCSTR pServiceName, const ADDRINFOA* pHints, PADDRINFOA* ppResult);
typedef INT (WSAAPI* GetAddrInfoW_t)(PCWSTR pNodeName, PCWSTR pServiceName, const ADDRINFOW* pHints, PADDRINFOW* ppResult);

namespace hooks {
    inline connect_t connect_og = nullptr;
    INT WSAAPI connect_detour(SOCKET s, const sockaddr *name, int namelen) {
        const auto* addr = reinterpret_cast<sockaddr_in*>(const_cast<sockaddr*>(name));
        const auto ip = inet_ntoa(addr->sin_addr);
        const auto port = ntohs(addr->sin_port);
        SetConsoleTitleA((std::string(ip) + ":" + std::to_string(port)).c_str());
        return connect_og(s, name, namelen);
    }

    inline recv_t recv_og = nullptr;
    INT WSAAPI recv_hook(SOCKET s, char *buf, int len, int flags) {
        return recv_og(s, buf, len, flags);
    }

    inline send_t send_og = nullptr;
    INT WSAAPI send_hook(SOCKET s, const char *buf, int len, int flags) {
        return send_og(s, buf, len, flags);
    }

    inline getaddrinfo_t getaddrinfo_og = nullptr;
    INT WSAAPI getaddrinfo_detour(PCSTR pNodeName, PCSTR pServiceName, const ADDRINFOA* pHints, PADDRINFOA* ppResult) {
        pNodeName = "localhost";
        return getaddrinfo_og(pNodeName, pServiceName, pHints, ppResult);
    }

    inline GetAddrInfoW_t GetAddrInfoW_og = nullptr;
    INT WSAAPI GetAddrInfoW_detour(PCWSTR pNodeName, PCWSTR pServiceName, const ADDRINFOW* pHints, PADDRINFOW* ppResult) {
        pNodeName = L"localhost";
        return GetAddrInfoW_og(pNodeName, pServiceName, pHints, ppResult);
    }
}

#endif
