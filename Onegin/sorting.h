#ifndef ONEGIN_SORTING_H
#define ONEGIN_SORTING_H

#include <cstring>
#include <malloc.h>

typedef int (*comparator)(const void *, const void *);

//!-----------------------------------------------------
//! \brief Sorts array with merge sort algoritm
//! \param base Pointer on start of array
//! \param count Number of elements in array
//! \param type Type of elements in array
//! \param comp Function that compares elements of array
//!-----------------------------------------------------
void mergesort(void *base, size_t count, size_t type, comparator comp);

//!------------------------------------------------------
//! \brief Merge two sorted arrays
//! \param lbase Pointer on first array
//! \param lcnt Number of elements in first array
//! \param rbase Pointer on second array
//! \param rcnt Number of elements in second array
//! \param type Type of elements in arrays
//! \param comp Function that compares elements of arrays
//!------------------------------------------------------
void merge_arrays(void *lbase, size_t lcnt, void *rbase, size_t rcnt, size_t type, comparator comp);

#endif //ONEGIN_SORTING_H
