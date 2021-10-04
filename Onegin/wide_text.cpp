#include "wide_text.h"

operation_status construct_text(wide_text* text, const char* buffer, size_t size) {
    size_t number_of_lines = 0;
    for (const char* ptr = buffer; ptr < buffer+size; ptr++) {
        while (ptr < buffer+size-1 && (*ptr != '\0' && *ptr != '\n')) {
            ptr++;
        }
        number_of_lines++;
    }

    text->lines = (wide_string*) calloc(number_of_lines, sizeof(wide_string));
    if (!text->lines) {
        destruct_text(text);
        return MEMORY_ALLOCATION_ERROR;
    }

    text->size = 0;
    const char* last_ptr;
    operation_status construct_status;
    for (const char* ptr = buffer; ptr < buffer+size; ptr++) {
        last_ptr = ptr;
        while (ptr < buffer+size && (*ptr != '\0' && *ptr != '\n')) {
            ptr++;
        }

        size_t line_size = (size_t)(ptr - last_ptr);

        construct_status = construct_string(&text->lines[text->size], last_ptr, line_size);
        if (construct_status != SUCCESS) {
            destruct_text(text);
            return construct_status;
        }
        text->size++;
    }

    return SUCCESS;
}

operation_status use_symbols_text(wide_text* text, wide_filter filters[], unsigned count) {
    operation_status operation_status;
    for (size_t i = 0; i < text->size; i++) {
        operation_status = use_symbols_string(&text->lines[i], filters, count);
        if (operation_status != SUCCESS) {
            return operation_status;
        }
    }
    return SUCCESS;
}

operation_status one_space_mode_text(wide_text* text) {
    operation_status operation_status;
    for (size_t i = 0; i < text->size; i++) {
        operation_status = one_space_mode_string(&text->lines[i]);
        if (operation_status != SUCCESS) {
            return operation_status;
        }
    }
    return SUCCESS;
}

void to_lower_text(wide_text* text) {
    for (size_t i = 0; i < text->size; i++) {
        to_lower_string(&text->lines[i]);
    }
}

operation_status fread_text(const char* filename, wide_text* text) {
    struct stat file_statistics = {};
    if (stat(filename, &file_statistics) == -1) {
        return FILE_GET_STAT_ERROR;
    }
    size_t size = (size_t)file_statistics.st_size;

    text->origin = (char*) calloc(size+1, sizeof(char));
    if (!text->origin) {
        return MEMORY_ALLOCATION_ERROR;
    }

    int file_descriptor = open(filename, O_RDONLY, S_IRWXU | S_IRWXG);
    if (file_descriptor == -1) {
        free(text->origin);
        return OPEN_FILE_ERROR;
    }

    if (read(file_descriptor, text->origin, size) == -1) {
        free(text->origin);
        return READ_FILE_ERROR;
    }

    if (close(file_descriptor) == -1) {
        free(text->origin);
        return CLOSE_FILE_ERROR;
    }

    return construct_text(text, text->origin, size);
}

operation_status fwrite_text(FILE* file, wide_text* text) {
    for (size_t i = 0; i < text->size; i++)
        if (fwprintf(file, L"%ls", text->lines[i]) == -1)
            return WRITE_FILE_ERROR;
    return SUCCESS;
}

operation_status fwrite_text_origin(FILE* file, wide_text* text) {
    if (fwprintf(file, L"%s", text->origin) == -1)
        return WRITE_FILE_ERROR;
    return SUCCESS;
}

void destruct_text(wide_text* text) {
    for (size_t i = 0; i < text->size; i++)
        destruct_string(&text->lines[i]);
    free(text->lines);
    free(text->origin);
}