#ifndef _UTF_TEXT_H_
#define _UTF_TEXT_H_

#include "utf_string.h"

namespace ong {

    struct text {
        string* lines;
        size_t size;
    };

    void construct_text(char* buffer, text* text, size_t size, int* error = nullptr);

    void destruct_text(text* text);

}

#endif //_UTF_TEXT_H_
