#ifndef ONEGIN_TEXTIO_H
#define ONEGIN_TEXTIO_H

#include <stdio.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <wctype.h>
#include <locale.h>
#include "sorting.h"

#define PERROR print_error(__FILE__, __FUNCTION__, __LINE__)

void print_error(const char* file, const char* func, int line);

void read_file(const char* filename, void* buffer, size_t nbytes);

ssize_t get_file_size(const char* filename);

#endif //ONEGIN_TEXTIO_H
