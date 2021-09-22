#ifndef ONEGIN_SORTING_H
#define ONEGIN_SORTING_H

#include <stdlib.h>
#include "utils.h"

void bubblesort(void* base, size_t count, size_t type, int (*comp)(const void*, const void*));

void mergesort(void* base, size_t count, size_t type, int (*comp)(const void*, const void*));

void merge_arr(void* lbase, size_t lcnt, void* rbase, size_t rcnt, size_t type, int (*comp)(const void*, const void*));

#endif //ONEGIN_SORTING_H
