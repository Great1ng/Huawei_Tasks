#ifndef _UTF_STRING_H_
#define _UTF_STRING_H_

#include <wchar.h>
#include <wctype.h>
#include <string.h>

#include "sorting.h"

namespace ong {

    enum direction {
        FROM_RIGHT_TO_LEFT = -1,
        FROM_LEFT_TO_RIGHT = 1
    };

    struct string {
        wchar_t* wbytes;
        size_t wbyte_size;

        char* bytes;
        size_t byte_size;
    };

    void construct_string(char* buffer, string* str, size_t size, int* error = nullptr);

    void filter_string(string* str, int (*filter)(wint_t), int* error = nullptr);

    comparator compare_strings(direction dir);

    int fltr_comparison(const void *ptr_1, const void *ptr_2);

    int frtl_comparison(const void *ptr_1, const void *ptr_2);

    void destruct_string(string* str);

}

#endif //_UTF_STRING_H_
