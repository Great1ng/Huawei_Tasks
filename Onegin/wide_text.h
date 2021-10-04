#ifndef ONEGIN_WIDE_TEXT_H
#define ONEGIN_WIDE_TEXT_H

#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#include "wide_string.h"

#define array_size(array) sizeof(array) / sizeof(array[0])

struct wide_text {
    wide_string* lines;
    size_t size;
    char* origin;
};

//!------------------------------------------------
//! \brief Leave only filtered symbols in wide text
//! \param text Pointer on wide text
//! \param filters Pointer on array of filters
//! \param count Size of array of filters
//! \return Operation status
//!------------------------------------------------
operation_status use_symbols_text(wide_text* text, wide_filter filters[], unsigned count) __nonnull((1,2));

//!-----------------------------------------------
//! \brief Leave only one space in a row of spaces
//! \param text Pointer on wide text
//! \return Operation status
//!-----------------------------------------------
operation_status one_space_mode_text(wide_text* text) __nonnull((1));

//!-------------------------------------------------------
//! \brief Convert all symbols from wide text to lowercase
//! \param text Pointer on wide text
//!-------------------------------------------------------
void to_lower_text(wide_text* text) __nonnull((1));

//!---------------------------------------------------------
//! \brief Read all bytes from file and convert them to text
//! \param filename Name of file
//! \param text Pointer on wide text
//! \return Operation status
//! \note You must call destruct_text to free memory
//!---------------------------------------------------------
operation_status fread_text(const char* filename, wide_text* text) __nonnull((1,2));

//!-----------------------------------------
//! \brief Write all text by strings in file
//! \param file Pointer on opened file
//! \param text Pointer on wide text
//! \return Operation status
//!-----------------------------------------
operation_status fwrite_text(FILE* file, wide_text* text) __nonnull((1,2));

//!-----------------------------------
//! \brief Write text origin to file
//! \param file Pointer on opened file
//! \param text Pointer on wide text
//! \return Operation status
//!-----------------------------------
operation_status fwrite_text_origin(FILE* file, wide_text* text) __nonnull((1, 2));

//!------------------------------------------------------------
//! \brief Construct struct wide text
//! \param text Pointer on wide text
//! \param buffer Pointer on multibyte string to construct from
//! \param size Size of buffer
//! \return Construction status
//! \note You must call destruct_text to free memory
//!------------------------------------------------------------
operation_status construct_text(wide_text* text, const char* buffer, size_t size) __nonnull ((1,2));

//!---------------------------------
//! \brief Destruct struct wide text
//! \param text Pointer on wide text
//!---------------------------------
void destruct_text(wide_text* text) __nonnull ((1));

#endif //ONEGIN_WIDE_TEXT_H
