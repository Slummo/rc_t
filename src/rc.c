#include "rc.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

struct rc {
    void* data;      // Data itself
    uint32_t count;  // Counter of references
    free_fn drop;    // Destructor function pointer
};

rc_t rc_new(void* data, free_fn drop) {
    if (!data || !drop) {
        return NULL;
    }

    rc_t rc = (rc_t)malloc(sizeof(_rc));
    if (!rc) {
        return NULL;
    }

    rc->data = data;
    rc->count = 1;
    rc->drop = drop;

    return rc;
}

rc_t rc_clone(rc_t rc) {
    if (!rc) {
        return NULL;
    }

    rc->count++;
    return rc;
}

const void* rc_data(rc_t rc) {
    return rc ? rc->data : NULL;
}

void* rc_data_mut(rc_t rc) {
    return rc ? rc->data : NULL;
}

void rc_free(rc_t* rc_ptr) {
    if (!rc_ptr || !*rc_ptr) {
        return;
    }

    if ((*rc_ptr)->count == 1) {
        (*rc_ptr)->drop((*rc_ptr)->data);
        free(*rc_ptr);
    } else {
        (*rc_ptr)->count--;
    }
    *rc_ptr = NULL;
}