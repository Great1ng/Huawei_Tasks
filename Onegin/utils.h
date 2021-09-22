#ifndef ONEGIN_UTILS_H
#define ONEGIN_UTILS_H

#include <cstddef>
#include <malloc.h>
#include <wchar.h>

struct line {
    const wchar_t* text;
    size_t size;
};

typedef unsigned char byte;

void copy_bytes(const byte* src, byte* dest, const size_t count);

void swap(byte* a, byte* b, const size_t typesize);

int linecmp(const void* __line1, const void* __line2);
int linecmp_inv(const void* __line1, const void* __line2);

size_t wcsnrplc(wchar_t* str, const wchar_t src, const wchar_t dest, size_t size);

#endif //ONEGIN_UTILS_H
