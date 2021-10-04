#include "sorting.h"

void mergesort(void *base, size_t count, size_t type, comparator comp) {
    if (count == 1) return;

    char *bt_base = (char *) base;

    size_t lcount = count / 2;
    size_t rcount = count - lcount;

    mergesort(bt_base, lcount, type, comp);
    mergesort(bt_base + lcount * type, rcount, type, comp);

    merge_arrays(base, lcount, bt_base + lcount * type, rcount, type, comp);
}

void merge_arrays(void *lbase, size_t lcnt, void *rbase, size_t rcnt, size_t type, comparator comp) {
    char *tmp = (char *) calloc(lcnt + rcnt, type);

    char *bt_lbase = (char *) lbase;
    char *bt_rbase = (char *) rbase;

    char *lptr = bt_lbase;
    char *rptr = bt_rbase;
    size_t sorted_cnt = 0;

    while (lptr < bt_lbase + lcnt * type) {
        while (rptr < bt_rbase + rcnt * type && comp(rptr, lptr) < 0) {
            memcpy(tmp + sorted_cnt * type, rptr, type);
            rptr += type;
            sorted_cnt++;
        }

        memcpy(tmp + sorted_cnt * type, lptr, type);
        lptr += type;
        sorted_cnt++;
    }

    while (rptr < bt_rbase + rcnt * type) {
        memcpy(tmp + sorted_cnt * type, rptr, type);
        rptr += type;
        sorted_cnt++;
    }

    memcpy(bt_lbase, tmp, (lcnt + rcnt) * type);

    free(tmp);
}
