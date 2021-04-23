#include "businesses.h"

#include <glib.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../auxiliary.h"
#include "../perfect_hash.h"
#include "users.h"

struct business {
  char *business_id;
  char *name;
  char *city;
  char *state;
  GPtrArray *categories;
};

struct business_collection {
  GPtrArray *businesses; // é mesmo necessario, tendo o by_id?
  GHashTable *by_id;
  PerfectHash by_letter;
};

/* Business: builder */
Business create_business(char *business_id, char *name, char *city, char *state,
                         GPtrArray *categories) {
  Business new_business = (Business)malloc(sizeof(struct business));
  *new_business = (struct business){.business_id = g_strdup(business_id),
                                    .name = g_strdup(name),
                                    .city = g_strdup(city),
                                    .state = g_strdup(state),
                                    .categories = categories};
  return new_business;
}

/* Business: getters and setters */

char *get_business_id(Business self) {
  if (self)
    return g_strdup(self->business_id);
  else
    return NULL;
}

char *get_business_name(Business self) {
  if (self)
    return g_strdup(self->name);
  else
    return NULL;
}

char *get_business_city(Business self) {
  if (self)
    return g_strdup(self->city);
  else
    return NULL;
}

char *get_business_state(Business self) {
  if (self)
    return g_strdup(self->state);
  else
    return NULL;
}

GPtrArray *get_business_categories(Business self) {
  if (self)
    return g_ptr_array_copy(self->categories, strdup_copy, NULL);
  else
    return NULL;
}

static Business clone_business(Business self) {

  Business new_business = (Business)malloc(sizeof(struct business));
  *new_business =
      (struct business){.business_id = get_business_id(self),
                        .name = get_business_name(self),
                        .city = get_business_city(self),
                        .state = get_business_state(self),
                        .categories = get_business_categories(self)};
  return new_business;
}

static gpointer g_business_copy(gconstpointer src, gpointer data) {
  return clone_business((Business)src);
}

/* Business: free */

void free_business(Business self) {
  if (self) {
    free(self->business_id);
    free(self->name);
    free(self->city);
    free(self->state);
    g_ptr_array_free(self->categories, TRUE);
    free(self);
  }
}

/* BusinessCollection: builder */
BusinessCollection create_business_collection() {
  BusinessCollection new_business_collection =
      (BusinessCollection)malloc(sizeof(struct business_collection));
  *new_business_collection = (struct business_collection){
      .businesses = g_ptr_array_new(),
      .by_id = g_hash_table_new(g_str_hash, g_str_equal),
      .by_letter = phf_new()};
  return new_business_collection;
}

void add_business(BusinessCollection collection, Business business) {
  Business clone = clone_business(business);
  g_ptr_array_add(collection->businesses, clone);
  g_hash_table_insert(collection->by_id, business->business_id, clone);
  phf_add(collection->by_letter, business->name, clone);
}

Business get_businessCollection_business_by_id(BusinessCollection self,
                                               char *id) {
  if (self && id)
    return clone_business(g_hash_table_lookup(self->by_id, id));
  else
    return NULL;
}

GPtrArray *get_businessCollection_business_by_letter(BusinessCollection self,
                                                     char *name) {
  if (self)
    return g_ptr_array_copy(phf_lookup(self->by_letter, name), g_business_copy,
                            NULL);
  else
    return NULL;
}

/* BusinessCollection: free */

void free_businessCollection(BusinessCollection self) {
  if (self) {
    g_ptr_array_set_free_func(self->businesses, (void *)free_business);
    g_ptr_array_free(self->businesses, TRUE);
    g_hash_table_foreach(self->by_id, free_key, NULL);
    phf_free(self->by_letter);
    g_hash_table_destroy(self->by_id);
    free(self);
  }
}
