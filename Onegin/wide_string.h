#ifndef ONEGIN_WIDE_STRING_H
#define ONEGIN_WIDE_STRING_H

#include <cwchar>
#include <cwctype>
#include <malloc.h>
#include <cstring>

typedef int (*wide_filter)(wint_t);
typedef int (*comparator)(const void*, const void*);

enum operation_status {
    SUCCESS,
    MEMORY_ALLOCATION_ERROR,
    WIDE_CONVERTION_ERROR,
    FILE_GET_STAT_ERROR,
    OPEN_FILE_ERROR,
    READ_FILE_ERROR,
    CLOSE_FILE_ERROR,
    WRITE_FILE_ERROR
};

static const char* error_description[] {
    "SUCCESS",
    "MEMORY_ALLOCATION_ERROR",
    "WIDE_CONVERTION_ERROR",
    "FILE_GET_STAT_ERROR",
    "OPEN_FILE_ERROR",
    "READ_FILE_ERROR",
    "CLOSE_FILE_ERROR",
    "WRITE_FILE_ERROR"
};

enum comparison_type {
    FROM_LEFT_TO_RIGHT = 1,
    FROM_RIGHT_TO_LEFT = -1
};

struct wide_string {
    wchar_t* symbols;
    size_t length;
};

//!------------------------------------------------------------
//! \brief Construct struct wide string
//! \param str Pointer on wide string
//! \param buffer Pointer on multibyte string to construct from
//! \param size Size of buffer
//! \return Construction status
//! \note You must call destruct_string to free memory
//!-------------------------------------------------------------
operation_status construct_string(wide_string* str, const char* buffer, size_t size) __nonnull ((1, 2));

//!---------------------------------------------------------
//! \brief Convert all symbols from wide string to lowercase
//! \param str Pointer on wide string to convert
//!---------------------------------------------------------
void to_lower_string(wide_string* str) __nonnull((1));

//!-----------------------------------------------
//! \brief Leave only one space in a row of spaces
//! \param str Pointer on wide string
//! \return Operation status
//!-----------------------------------------------
operation_status one_space_mode_string(wide_string* str) __nonnull((1));

//!-----------------------------------------------
//! \brief Leave only filtered symbols in wide string
//! \param str Pointer on wide string
//! \param filters Pointer on array of filters
//! \param count Size of array of filters
//! \return Operation status
//!-----------------------------------------------
operation_status use_symbols_string(wide_string* str, wide_filter filters[], unsigned count) __nonnull((1,2));

//!-----------------------------------
//! \brief Destruct struct wide string
//! \param str Pointer on wide string
//!-----------------------------------
void destruct_string(wide_string* str) __nonnull ((1));

//!--------------------------------------------------------
//! \brief Give a comparator of wide string of certain type
//! \param type Type of wide string comparison
//! \return Comparator of comparison type
//!--------------------------------------------------------
comparator comparator_string(comparison_type type);

//!----------------------------------------------------------------------------------------
//! \brief Compare two wide strings from rigth to left
//! \param ptr1 Pointer on first string
//! \param ptr2 Pointer on second string
//! \return If first string is less(L), equal(E) or greater(G), number L, E, or G than zero
//!----------------------------------------------------------------------------------------
int FRTL_compare_string(const void* ptr1, const void* ptr2);

//!----------------------------------------------------------------------------------------
//! \brief Compare two wide strings from left to right
//! \param ptr1 Pointer on first string
//! \param ptr2 Pointer on second string
//! \return If first string is less(L), equal(E) or greater(G), number L, E, or G than zero
//!----------------------------------------------------------------------------------------
int FLTR_compare_string(const void* ptr1, const void* ptr2);

#endif //ONEGIN_WIDE_STRING_H
