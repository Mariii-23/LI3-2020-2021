#ifndef AUXILIARY_H
#define AUXILIARY_H

#include <glib.h>
#include <stdio.h>

#include "reviews.h"
void *assert_return(void *ptr);
void free_key(gpointer key, gpointer value, gpointer user_data);
void free_key_value(gpointer key, gpointer value, gpointer user_data);
void append_to_value(GHashTable *hash_table, gpointer key,
                     gpointer value_to_add);
void *get_last_ptr(GPtrArray *array);
guint business_name_hash(gconstpointer word);
gboolean compare_first_letter(gconstpointer key1, gconstpointer key2);
gpointer strdup_copy(gconstpointer src, gpointer data);
GPtrArray *build_ptr_array(char *fields[], int N);
void fprint_str_array(FILE *stream, GPtrArray *arr, size_t n_fields,
                      char *delim);

void free_ptr_array_deep(GPtrArray *arr);
char *my_strsep(char **str, const char *delim);
bool is_number(char *value);
int my_atoi(char *str);
float my_atof(char *str);
#endif
