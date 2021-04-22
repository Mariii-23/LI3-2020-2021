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

GPtrArray* build_ptr_array(char* ptr_array[], int N) {
    GPtrArray* new_array = g_ptr_array_sized_new(N);
    for (size_t i = 0; i < N; i++) {
        g_ptr_array_add(new_array, ptr_array[i]);
    }
    return new_array;
}

void fprint_str_array(
    FILE* stream, GPtrArray* arr, size_t n_fields, char* delim) {
    for (int i = 0; i < arr->len; i++) {
        char p_new_line[4] = "";
        if (i > 0 && ((i + 1) % n_fields) == 0) strcpy(p_new_line, " |\n");
        fprintf(stream, "%s%s%s", delim, (char*) arr->pdata[i], p_new_line);
    }
}
void free_ptr_array_deep(GPtrArray* arr) {
    g_ptr_array_set_free_func(arr, free);
    g_ptr_array_free(arr, TRUE);
}

