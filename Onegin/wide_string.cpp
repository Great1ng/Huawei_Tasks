#include "wide_string.h"

const wchar_t* string_end = L"\n\0";
const size_t end_size = 2;

operation_status construct_string(wide_string* str, const char* buffer, size_t size) {
    char* resized_buf = (char*) calloc(size + 1, sizeof(char));
    if (!resized_buf) return MEMORY_ALLOCATION_ERROR;
    strncpy(resized_buf, buffer, size);
    resized_buf[size] = '\0';

    const char* constant_buffer = (const char*)resized_buf;

    size_t converted_size = mbsrtowcs(nullptr, &constant_buffer, 0, nullptr);
    if (converted_size == -1ul) {
        free(resized_buf);
        return WIDE_CONVERTION_ERROR;
    }

    str->symbols = (wchar_t*) calloc(converted_size + end_size, sizeof(wchar_t));
    if (!str->symbols) {
        free(resized_buf);
        return MEMORY_ALLOCATION_ERROR;
    }

    if (mbsrtowcs(str->symbols, &constant_buffer, converted_size, nullptr) == -1ul) {
        destruct_string(str);
        free(resized_buf);
        return WIDE_CONVERTION_ERROR;
    }

    free(resized_buf);

    for (size_t i = 0; i < end_size; i++) {
        str->symbols[converted_size+i] = string_end[i];
    }

    str->length = converted_size + end_size - 1;

    return SUCCESS;
}

void to_lower_string(wide_string* str) {
    for (size_t i = 0; i < str->length; i++) {
        wint_t symbol_code = (wint_t)str->symbols[i];
        str->symbols[i] = (wchar_t) towlower(symbol_code);
    }
}

operation_status one_space_mode_string(wide_string* str) {
    size_t current = 0;
    wint_t last = 0;
    for (size_t i = 0; i < str->length; i++) {
        wint_t symbol_code = (wint_t) str->symbols[i];
        if (iswspace(last) && iswspace(symbol_code)) {
            continue;
        }
        str->symbols[current] = (wchar_t)symbol_code;
        last = symbol_code;
        current++;
    }

    str->symbols = (wchar_t*)realloc(str->symbols, (current+1)*sizeof(wchar_t));
    if (!str->symbols) {
        return MEMORY_ALLOCATION_ERROR;
    }
    str->symbols[current] = L'\0';
    str->length = current;

    return SUCCESS;
}

operation_status use_symbols_string(wide_string* str, wide_filter filters[], unsigned count) {
    size_t current = 0;
    for (size_t i = 0; i < str->length; i++) {
        wint_t symbol_code = (wint_t)str->symbols[i];
        for (unsigned j = 0; j < count; j++) {
            if (filters[j](symbol_code)) {
                str->symbols[current] = str->symbols[i];
                current++;
                break;
            }
        }
    }

    str->symbols = (wchar_t*)realloc(str->symbols, (current+1)*sizeof(wchar_t));
    if (!str->symbols) {
        return MEMORY_ALLOCATION_ERROR;
    }
    str->symbols[current] = L'\0';
    str->length = current;

    return SUCCESS;
}

void destruct_string(wide_string* str) {
    free(str->symbols);
}

comparator comparator_string(comparison_type type) {
    switch(type) {
        case FROM_RIGHT_TO_LEFT:
            return FRTL_compare_string;
        case FROM_LEFT_TO_RIGHT:
            return FLTR_compare_string;
        default:
            return nullptr;
    }
}

int FRTL_compare_string(const void* ptr1, const void* ptr2) {
    const wide_string* str1 = (const wide_string*) ptr1;
    const wide_string* str2 = (const wide_string*) ptr2;

    wchar_t difference;
    long last1 = (long)str1->length-1;
    long last2 = (long)str2->length-1;

    while (last1 >= 0) {
        if (last2 < 0)
            return 1;
        difference = str1->symbols[last1--] - str2->symbols[last2--];
        if (difference != 0)
            return difference;
    }

    return -(last2 >= 0);
}

int FLTR_compare_string(const void* ptr1, const void* ptr2) {
    const wide_string* str1 = (const wide_string*) ptr1;
    const wide_string* str2 = (const wide_string*) ptr2;

    wchar_t difference;
    for (size_t i = 0; i <= str1->length; i++) {
        difference = str1->symbols[i] - str2->symbols[i];
        if (i == str2->length)
            return difference;
        if (difference != 0)
            return difference;
    }

    return 0;
}
