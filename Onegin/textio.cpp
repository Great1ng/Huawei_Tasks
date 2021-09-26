#include "textio.h"

void print_error(const char* file, const char* func, int line) {
    fprintf(stderr, "Error: %s %s %d: %s", file, func, line, strerror(errno));
}

void read_file(const char* filename, void* buffer, size_t nbytes) {
    if (buffer == NULL) {
        printf("Error on line %d\n", __LINE__);
        return;
    } //memory allocation error

    int fd = open(filename, O_RDONLY, S_IRWXU | S_IRWXG);
    if (fd == -1) {
        PERROR;
        return;
    }

    if (read(fd, buffer, nbytes) == -1) {
        PERROR;
        return;
    }

    if (close(fd) == -1) {
        PERROR;
        return;
    }
}
