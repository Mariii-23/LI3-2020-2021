#include <assert.h>
#include <glib.h>
#include <stdio.h>
#include <stdlib.h>

void* assert_return(void* ptr) {
    assert(ptr);
    return ptr;
}

void map_free(gpointer key, gpointer value, gpointer user_data) {
    free(key);
    free(value);
}
