#include "sorting.h"

void mergesort(void* base, size_t count, size_t type, int (*comp)(const void*, const void*)) {
    if (count == 1) return;

    byte* bt_base = (byte*)base;

    size_t lcount = count / 2;
    size_t rcount = count - lcount;

    mergesort(bt_base, lcount, type, comp);
    mergesort(bt_base + lcount*type, rcount, type, comp);

    merge_arr(base, lcount, bt_base + lcount*type, rcount, type, comp);
}

void merge_arr(void* lbase, size_t lcnt, void* rbase, size_t rcnt, size_t type, int (*comp)(const void*, const void*)) {
    byte* tmp = (byte*)calloc(lcnt+rcnt, type);

    byte* bt_lbase = (byte*)lbase;
    byte* bt_rbase = (byte*)rbase;

    byte* lptr = bt_lbase;
    byte* rptr = bt_rbase;
    size_t sorted_cnt = 0;

    while (lptr < bt_lbase+lcnt*type) {
        while (rptr < bt_rbase+rcnt*type && comp(rptr, lptr) < 0) {
            copy_bytes(rptr, tmp+sorted_cnt*type, type);
            rptr += type;
            sorted_cnt++;
        }

        copy_bytes(lptr, tmp+sorted_cnt*type, type);
        lptr += type;
        sorted_cnt++;
    }

    while (rptr < bt_rbase+rcnt*type) {
        copy_bytes(rptr, tmp+sorted_cnt*type, type);
        rptr += type;
        sorted_cnt++;
    }

    copy_bytes(tmp, bt_lbase, (lcnt+rcnt)*type);

    free(tmp);
}



void bubblesort(void* base, size_t count, size_t type, int (*comp)(const void*, const void*)) {
    byte* bt_base = (byte*)base;

    for (size_t i = 0; i < count; i++) {
        for (size_t j = 1; j < count; j++) {
            if (comp(bt_base+j*type, bt_base+(j-1)*type) < 0)
                swap(bt_base+j*type, bt_base+(j-1)*type, type);
        }
    }
}

