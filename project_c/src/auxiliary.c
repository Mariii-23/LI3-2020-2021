#include <assert.h>
#include <glib.h>
#include <stdio.h>
#include <stdlib.h>

#include "model/reviews.h"

void* assert_return(void* ptr) {
    assert(ptr);
    return ptr;
}

void free_key(gpointer key, gpointer value, gpointer user_data) {
    free(key);
}

void free_key_value(gpointer key, gpointer value, gpointer user_data) {
    free(key);
    free(value);
}
void add_to_hash_arr(
    GHashTable* hash_table, gpointer key, gpointer value_to_add) {
    GPtrArray* curr = g_hash_table_lookup(hash_table, key);
    g_ptr_array_add(curr, value_to_add);
}

