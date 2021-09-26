#include "utf_text.h"

namespace ong {

    void construct_text(char* buffer, text* text, size_t size, int* error) {
        string str;
        construct_string(buffer, &str, size, error);

        filter_string(&str, iswpunct, error);

        text->lines = (string*) calloc(text->size, sizeof(string));
        if (text->lines == nullptr) {
            if (error) *error = -3;
        }

        size_t current = 0;
        for (size_t i = 0; i < str.byte_size; i++) {
            if (str.bytes[i] == '\0') break;
            size_t line_size = 0;
            char* start = str.bytes+i;
            while (str.bytes[i] != '\n') {
                line_size++;
                i++;
            }
            construct_string(start, &text->lines[current], line_size, error);
            current++;
        }

        text->size = current;

        destruct_string(&str);
    }

    void destruct_text(text* text) {
        for (size_t i = 0; i < text->size; i++)
            destruct_string(&text->lines[i]);
        free(text->lines);
    }

}