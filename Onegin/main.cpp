#include <locale.h>
#include <stdlib.h>

#include "utf_text.h"
#include "textio.h"

void run_work_cycle();

int main() {
    setlocale(LC_CTYPE, "ru_RU.UTF-8");

    run_work_cycle();

    return 0;
}

void run_work_cycle() {
    const char* input_filename = "../Onegin.in";
    const char* output_filename = "../Onegin.out";

    struct stat input_filedata = {};

    if (stat(input_filename, &input_filedata) == -1) {
        PERROR;
        return;
    }

    size_t nbytes = (size_t) input_filedata.st_size;

    char* input = (char*) calloc(nbytes+1, sizeof(char));
    if (input == NULL) {
        PERROR;
    }
    read_file(input_filename, input, nbytes);
    input[nbytes] = '\0';

    int error = 0;
    ong::text text;
    ong::construct_text(input, &text, nbytes, &error);

    int fd = open(output_filename, O_CREAT | O_WRONLY | O_TRUNC, S_IRWXU | S_IRWXG);
    if (fd == -1) {
        PERROR;
        return;
    }

    qsort(text.lines, text.size, sizeof(ong::string), ong::compare_strings(ong::FROM_LEFT_TO_RIGHT));
    for (size_t i = 0; i < text.size; i++) {
        if (write(fd, text.lines[i].bytes, text.lines[i].byte_size - 1) == -1) {
            PERROR;
            return;
        }
    }
    write(fd, "\n", 1);

    mergesort(text.lines, text.size, sizeof(ong::string), ong::compare_strings(ong::FROM_RIGHT_TO_LEFT));
    for (size_t i = 0; i < text.size; i++) {
        if (write(fd, text.lines[i].bytes, text.lines[i].byte_size - 1) == -1) {
            PERROR;
            return;
        }
    }
    write(fd, "\n", 1);

    if (write(fd, input, nbytes) == -1) {
        PERROR;
        return;
    }

    if (close(fd) == -1) {
        PERROR;
        return;
    }

    destruct_text(&text);
    free(input);
}