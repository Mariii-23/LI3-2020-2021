#ifndef AUXILIARY_H
#define AUXILIARY_H

#include <glib.h>
#include <stdio.h>

#include "model/reviews.h"
void* assert_return(void* ptr);
void free_key(gpointer key, gpointer value, gpointer user_data);
void free_key_value(gpointer key, gpointer value, gpointer user_data);
void append_to_value(GHashTable* hash_table, gpointer key, gpointer review);
void* get_last_ptr(GPtrArray* array);
guint business_name_hash(gconstpointer word);
gboolean compare_first_letter(gconstpointer key1, gconstpointer key2);
gpointer strdup_copy(gconstpointer src, gpointer data);
GPtrArray* build_ptr_array(char* fields[], int N);
void fprint_str_array(FILE* stream, GPtrArray* arr, char* delim);
void free_ptr_array_deep(GPtrArray* arr);
#endif

