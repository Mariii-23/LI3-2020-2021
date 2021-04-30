#include "businesses.h"

#include <glib.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "auxiliary.h"
#include "perfect_hash.h"
#include "users.h"

struct business {
  char *business_id;
  char *name;
  char *city;
  char *state;
  GPtrArray *categories;
};

struct business_collection {
  GHashTable *by_id;
  PerfectHash by_letter;
};

/* Business: builder */

Business create_business(char *business_id, char *name, char *city, char *state,
                         GPtrArray *categories) {
  Business new_business = (Business)malloc(sizeof(struct business));
  *new_business = (struct business){
      .business_id = g_strdup(business_id),
      .name = g_strdup(name),
      .city = g_strdup(city),
      .state = g_strdup(state),
      .categories = (categories && categories->len > 0)
                        ? g_ptr_array_copy(categories, strdup_copy, NULL)
                        : NULL};
  return new_business;
}

/* Business: getters and setters */

char *get_business_id(Business self) {
  if (self && self->business_id)
    return g_strdup(self->business_id);
  else
    return NULL;
}

char *get_business_name(Business self) {
  if (self && self->name)
    return g_strdup(self->name);
  else
    return NULL;
}

char *get_business_city(Business self) {
  if (self && self->city)
    return g_strdup(self->city);
  else
    return NULL;
}

char *get_business_state(Business self) {
  if (self && self->state)
    return g_strdup(self->state);
  else
    return NULL;
}

GPtrArray *get_business_categories(Business self) {
  if (self && self->categories && self->categories->len > 0)
    return g_ptr_array_copy(self->categories, strdup_copy, NULL);
  else
    return NULL;
}

static Business clone_business(Business self) {
  if (!self)
    return NULL;

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
    if (self->categories) {
      if (self->categories->len > 1)
        g_ptr_array_set_free_func(self->categories, free);
      g_ptr_array_free(self->categories, TRUE);
    }
    free(self);
  }
}

void g_free_business(gpointer data) { free_business((Business)data); }

/* BusinessCollection: builder */
BusinessCollection create_business_collection() {
  BusinessCollection new_business_collection =
      (BusinessCollection)malloc(sizeof(struct business_collection));
  *new_business_collection = (struct business_collection){
      .by_id = g_hash_table_new(g_str_hash, g_str_equal),
      .by_letter = phf_new()};
  return new_business_collection;
}

void add_business(BusinessCollection collection, Business business) {
  if (!collection || !business)
    return;
  Business clone = clone_business(business);
  if (!clone)
    return;
  g_hash_table_insert(collection->by_id, clone->business_id, clone);
  phf_add(collection->by_letter, clone->name, clone);
}

Business get_businessCollection_business_by_id(BusinessCollection self,
                                               char *id) {
  Business new = NULL;
  if (!self || !id)
    return new;

  Business aux = g_hash_table_lookup(self->by_id, id);
  if (aux)
    new = clone_business(aux);

  return new;
}

GPtrArray *get_businessCollection_business_by_letter(BusinessCollection self,
                                                     char *name) {
  GPtrArray *new = NULL;
  if (!self)
    return new;

  GPtrArray *aux = phf_lookup(self->by_letter, name);
  if (aux)
    new = g_ptr_array_copy(aux, g_business_copy, NULL);

  return new;
}

char *get_state_by_business_id(BusinessCollection business_collection,
                               char *business_id) {
  if (!business_collection || !business_id)
    return NULL;

  Business aux = g_hash_table_lookup(business_collection->by_id, business_id);
  if (!aux)
    return NULL;
  char *state = get_business_state(aux);
  return state;
}

/* BusinessCollection: free */

void free_businessCollection(BusinessCollection self) {
  if (self) {
    g_hash_table_foreach(self->by_id, free_key, NULL);
    g_hash_table_destroy(self->by_id);
    phf_free(self->by_letter);
    free(self);
  }
}
