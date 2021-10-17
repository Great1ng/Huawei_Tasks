#ifndef PROTECTED_STACK_UTILS_H
#define PROTECTED_STACK_UTILS_H

#include <cerrno>

#ifdef __linux__
#include <unistd.h>
#include <fcntl.h>

bool IsBadReadPtr(const void* ptr, size_t size);

#elif defined _WIN32
#include <winbase.h>

#endif //__linux__
#endif //PROTECTED_STACK_UTILS_H
