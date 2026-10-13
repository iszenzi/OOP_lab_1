#pragma once

#include <cstddef>

std::size_t str_len(const char* s);
void str_copy(char* dst, const char* src);
char* str_alloc(const char* src);
void str_delete(char*& s);
void str_print(const char* s);

std::size_t str_count_words(const char* s);
bool str_find_substr(const char* s, const char* sub, int& out_pos);
