#include "rc.h"
#include <stdio.h>
#include <stdlib.h>

#define NUM 10

void int_arr_drop(void* arr_raw) {
    free(arr_raw);
}

int main(void) {
    int* arr_raw = (int*)malloc(sizeof(int) * NUM);
    for (int i = 0; i < NUM; i++) {
        arr_raw[i] = i * 2;
    }

    rc_t arr = rc_new((void*)arr_raw, int_arr_drop);
    rc_t arr2 = rc_clone(arr);

    for (int i = 0; i < NUM; i++) {
        printf("arr[i] = %d, arr2[i] = %d\n", ((const int*)rc_data(arr))[i], ((const int*)rc_data(arr2))[i]);
    }

    rc_free(&arr);

    printf("After free(arr):\n");
    for (int i = 0; i < NUM; i++) {
        printf("arr2[i] = %d\n", ((const int*)rc_data(arr2))[i]);
    }

    rc_free(&arr2);

    return 0;
}