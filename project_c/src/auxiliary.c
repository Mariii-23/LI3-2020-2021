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
    if (user_data) {
        g_ptr_array_free(value, TRUE);
    }
    free(key);
    free(value);
}

void append_to_value(
    GHashTable* hash_table, gpointer key, gpointer value_to_add) {
    GPtrArray* curr = g_hash_table_lookup(hash_table, key);
    if (!curr) {
        GPtrArray* new_array = g_ptr_array_new();
        g_ptr_array_add(new_array, value_to_add);
        g_hash_table_insert(hash_table, key, new_array);
        return;
    }
    g_ptr_array_add(curr, value_to_add);
}

void* get_last_ptr(GPtrArray* array) {
    int len = array->len;
    return array->pdata[len - 1];
}

gboolean compare_first_letter(gconstpointer key1, gconstpointer key2) {
    return ((char*) key1)[0] == ((char*) key2)[0];
}

guint business_name_hash(gconstpointer word) {
    char first = ((char*) word)[0];
    size_t other_chars = ('Z' % 'A') + 1;
    return first >= 'A' && first <= 'z' ? (first % 'a') % 'A' : other_chars;
}

gpointer strdup_copy(gconstpointer src, gpointer data) {
    return g_strdup(src);
}
