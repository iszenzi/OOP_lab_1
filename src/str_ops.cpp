#include "lab01/str_ops.hpp"

#include <iostream>

std::size_t str_len(const char* s) {
    std::size_t length{};

    while (s[length] != '\0') {
        ++length;
    }
    return length;
}

void str_copy(char* dst, const char* src) {
    std::size_t i{};

    while (src[i] != '\0') {
        dst[i] = src[i];
        ++i;
    }

    dst[i] = '\0';
}

char* str_alloc(const char* src) {
    const std::size_t length = str_len(src);
    char* copy = new char[length + 1];
    str_copy(copy, src);
    return copy;
}

void str_delete(char*& s) {
    delete[] s;
    s = nullptr;
}

void str_print(const char* s) {
    if (s == nullptr) {
        return;
    }

    std::cout << s;
}
