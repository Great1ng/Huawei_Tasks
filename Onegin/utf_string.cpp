#include "utf_string.h"

namespace ong {

    void construct_string(char* buffer, string* str, size_t size, int* error) {
        char* geted = (char*) calloc(size+1, sizeof(char));
        strncpy(geted, buffer, size);
        geted[size] = '\0';
        const char* sized = geted;

        size_t wbyte_size = mbsrtowcs(nullptr, &sized, 0, nullptr);
        if (wbyte_size == -1ul) {
            if (error) {*error = -1; wprintf(L"%d\n", __LINE__);}
        }

        str->byte_size = size;
        str->wbyte_size = wbyte_size;

        str->bytes = (char*) calloc(str->byte_size + 2, sizeof(char));
        if (str->bytes == nullptr) {
            if (error) *error = -3;
        }
        memcpy(str->bytes, buffer, str->byte_size);
        str->bytes[str->byte_size] = '\n';
        str->bytes[str->byte_size+1] = '\0';
        str->byte_size+=2;

        str->wbytes = (wchar_t*) calloc(str->wbyte_size + 2, sizeof(wchar_t));
        if (str->bytes == nullptr) {
            if (error) *error = -3;
        }
        if (mbsrtowcs(str->wbytes, &sized, str->wbyte_size, nullptr) == -1) {
            if (error) {*error = -1; wprintf(L"%d\n", __LINE__);}
        }
        str->wbytes[str->wbyte_size] = L'\n';
        str->wbytes[str->wbyte_size+1] = L'\0';
        str->wbyte_size+=2;

        free(geted);
    }

    void filter_string(string* str, int (*filter)(wint_t), int* error) {
        size_t passed = 0;

        for (size_t i = 0; i < str->wbyte_size; i++) {
            wint_t letter = (wint_t) str->wbytes[i];

            if (!filter(letter)) {
                str->wbytes[passed] = str->wbytes[i];
                passed++;
            }
        }
        str->wbyte_size = passed;
        str->wbytes = (wchar_t*) realloc(str->wbytes, passed*sizeof(wchar_t));
        if (str->wbytes == nullptr) {
            if (error) *error = -3;
        }

        const wchar_t* wbuffer = str->wbytes;
        size_t byte_size = wcsrtombs(nullptr, &wbuffer, 0, nullptr);
        if (byte_size == -1ul) {
            if (error) {*error = -1; wprintf(L"%d\n", __LINE__);}
        }

        wcsrtombs(str->bytes, &wbuffer, byte_size, nullptr);
        str->byte_size = byte_size;
        str->bytes[str->byte_size] = '\0';
        str->byte_size++;

        str->bytes = (char*) realloc(str->bytes, str->byte_size*sizeof(char));
        if (str->wbytes == nullptr) {
            if (error) *error = -3;
        }
    }

    comparator compare_strings(direction dir) {
        switch (dir) {
            case FROM_LEFT_TO_RIGHT:
                return fltr_comparison;
            case FROM_RIGHT_TO_LEFT:
                return frtl_comparison;
            default:
                return nullptr;
        }
    }

    int fltr_comparison(const void *ptr_1, const void *ptr_2) {
        const string* str_1 = (const string*) ptr_1;
        const string* str_2 = (const string*) ptr_2;

        return wcscmp(str_1->wbytes, str_2->wbytes);
    }

    int frtl_comparison(const void *ptr_1, const void *ptr_2) {
        const string* str_1 = (const string*) ptr_1;
        const string* str_2 = (const string*) ptr_2;

        int i = str_1->wbyte_size-1;
        int j = str_2->wbyte_size-1;

        //wprintf(L"%ls %ls\n", str_1->wbytes, str_2->wbytes);

        while (i >= 0) {
            if (j < 0) return 1;
            if (str_1->wbytes[i] < str_2->wbytes[j]) return -1;
            if (str_1->wbytes[i] > str_2->wbytes[j]) return 1;

            i--; j--;
        }

        return 0;
    }

    void destruct_string(string* str) {
        free(str->bytes);
        free(str->wbytes);
    }

}