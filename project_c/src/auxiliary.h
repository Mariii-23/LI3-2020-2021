#ifndef AUXILIARY_H
#define AUXILIARY_H

#include <glib.h>

#include "model/reviews.h"
void* assert_return(void* ptr);
void free_key(gpointer key, gpointer value, gpointer user_data);
void free_key_value(gpointer key, gpointer value, gpointer user_data);
void append_to_value(GHashTable* hash_table, gpointer key, gpointer review);
guint business_name_hash(gconstpointer word);
gboolean compare_first_letter(gconstpointer key1, gconstpointer key2);
#endif

