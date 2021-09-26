#ifndef _TEXTIO_H_
#define _TEXTIO_H_

#include <stdio.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

#define PERROR print_error(__FILE__, __FUNCTION__, __LINE__)

void print_error(const char* file, const char* func, int line);

void read_file(const char* filename, void* buffer, size_t nbytes);

#endif //_TEXTIO_H_
