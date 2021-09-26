#ifndef _SORTING_H_
#define _SORTING_H_

#include <string.h>
#include <malloc.h>

namespace ong {

    typedef int (*comparator)(const void *, const void *);

    void mergesort(void *base, size_t count, size_t type, comparator comp);

    void merge_arrays(void *lbase, size_t lcnt, void *rbase, size_t rcnt, size_t type, comparator comp);

}
#endif //_SORTING_H_
