#include "utils.h"

void copy_bytes(const byte* src, byte* dest, const size_t count) {
    for (size_t bt = 0; bt < count; bt++) {
        dest[bt] = src[bt];
    }
}

void swap(byte* a, byte* b, const size_t typesize) {
    byte* tmp = (byte*)calloc(typesize, sizeof(byte));

    copy_bytes(a, tmp, typesize);
    copy_bytes(b, a, typesize);
    copy_bytes(tmp, b, typesize);

    free(tmp);
}

int linecmp(const void* __line1, const void* __line2) {
    const line* line1 = (const line*)__line1;
    const line* line2 = (const line*)__line2;

    return wcscmp(line1->text, line2->text);
}

int linecmp_inv(const void* __line1, const void* __line2) {
    const line* line1 = (const line*)__line1;
    const line* line2 = (const line*)__line2;

    wchar_t* text1 = (wchar_t*)calloc(line1->size, sizeof(wchar_t));
    wchar_t* text2 = (wchar_t*)calloc(line2->size, sizeof(wchar_t));

    for (size_t bt = 0; bt < line1->size; bt++) {
        text1[bt] = line1->text[line1->size-bt-1];
    }
    for (size_t bt = 0; bt < line2->size; bt++) {
        text2[bt] = line2->text[line2->size-bt-1];
    }

    return wcscmp(text1, text2);
}

size_t wcsnrplc(wchar_t* str, const wchar_t src, const wchar_t dest, size_t size) {
    size_t replaced = 0;

    for (size_t i = 0; i < size; i++) {
        if (str[i] == src) {
            str[i] = dest;
            replaced++;
        }
    }

    return replaced;
}