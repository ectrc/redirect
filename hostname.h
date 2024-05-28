#ifndef HOSTNAME_H
#define HOSTNAME_H

#include <array>
#include <cstddef>

#define HOSTNAME "localhost"

constexpr char redirect_hostname[] = HOSTNAME;
constexpr size_t strlen_c(const char* str) {
    size_t len = 0;
    while (str[len] != '\0') {
        ++len;
    }
    return len;
}
constexpr size_t hostname_length = strlen_c(redirect_hostname);
constexpr std::array<wchar_t, hostname_length + 1> widen(const char* str) {
    std::array<wchar_t, hostname_length + 1> result = {};
    for (size_t i = 0; i < hostname_length; ++i) {
        result[i] = static_cast<wchar_t>(str[i]);
    }
    result[hostname_length] = L'\0';
    return result;
}
constexpr auto wide_hostname = widen(redirect_hostname);
constexpr const wchar_t* const wide_redirect_hostname = wide_hostname.data();

#endif
