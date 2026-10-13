#include "lab01/str_ops.hpp"

#include <iostream>

std::size_t str_len(const char* s) {
    if (s == nullptr) {
        return 0;
    }
    std::size_t length{};

    while (s[length] != '\0') {
        ++length;
    }
    return length;
}

void str_copy(char* dst, const char* src) {
    if (dst == nullptr || src == nullptr) {
        return;
    }
    std::size_t i{};

    while (src[i] != '\0') {
        dst[i] = src[i];
        ++i;
    }

    dst[i] = '\0';
}

char* str_alloc(const char* src) {
    if (src == nullptr) {
        return nullptr;
    }
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

std::size_t str_count_words(const char* s) {
    if (s == nullptr) {
        return 0;
    }
    std::size_t count{};
    std::size_t i{};
    bool in_word = false;

    while (s[i] != '\0') {
        if (s[i] == ' ') {
            in_word = false;
        } else if (in_word == false) {
            in_word = true;
            ++count;
        }

        ++i;
    }
    return count;
}

bool str_find_substr(const char* s, const char* sub, int& out_pos) {
    if (s == nullptr || sub == nullptr) {
        return false;
    }
    std::size_t i{};
    std::size_t j{};
    if (sub[0] == '\0') {
        out_pos = 0;
        return true;
    }
    while (s[i] != '\0') {
        j = 0;
        while (sub[j] != '\0' && s[i + j] != '\0' && s[i + j] == sub[j]) {
            ++j;
        }
        if (sub[j] == '\0') {
            out_pos = static_cast<int>(i);
            return true;
        }

        ++i;
    }

    return false;
}
