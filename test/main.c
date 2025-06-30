#include "rc.h"
#include <stdio.h>
#include <stdlib.h>

#define NUM 10

int main(void) {
    int* arr_raw = (int*)malloc(sizeof(int) * NUM);
    for (int i = 0; i < NUM; i++) {
        arr_raw[i] = i * 2;
    }

    rc_t* arr = rc_new((void*)arr_raw, free);
    rc_t* arr_clone = rc_clone(arr);

    for (int i = 0; i < NUM; i++) {
        printf("arr[i] = %d, arr_clone[i] = %d\n", ((const int*)rc_data(arr))[i], ((const int*)rc_data(arr_clone))[i]);
    }
    printf("\n");

    rc_free(&arr);

    printf("\nAfter free of original:\n");
    for (int i = 0; i < NUM; i++) {
        printf("arr_clone[i] = %d\n", ((const int*)rc_data(arr_clone))[i]);
    }

    rc_free(&arr_clone);

    return 0;
}