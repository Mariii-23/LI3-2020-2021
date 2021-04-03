#ifndef AUXILIARY_H
#define AUXILIARY_H

#include <glib.h>

#include "model/reviews.h"
void* assert_return(void* ptr);
void free_key(gpointer key, gpointer value, gpointer user_data);
void free_key_value(gpointer key, gpointer value, gpointer user_data);
void add_to_hash_arr(GHashTable* hash_table, gpointer key, gpointer review);
#endif

