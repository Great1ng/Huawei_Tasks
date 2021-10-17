#include "utils.h"

bool IsBadReadPtr(const void* ptr, size_t size)
{
    int fd = open(".", O_TMPFILE | O_WRONLY | O_EXCL, S_IRGRP);
    bool status = (write(fd, ptr, size) < 0 && errno == EFAULT);
    close(fd);
    return status;
}