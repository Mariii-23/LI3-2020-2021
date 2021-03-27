#include "businesses.h"
#include <glib.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct business {
  char *business_id;
  char *name;
  char *city;
  char *state;

  GPtrArray *categories;
};

struct business_collection {
  GArray *businesses;
  GHashTable *by_id;
  GHashTable *by_city; // char* -> tree de negócios

  GTree *by_name;
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
    return self->business_id;
  else
    return NULL;
}

void set_business_id(Business self, char *business_id) {
  if (self)
    self->business_id = g_strdup(business_id);
}

char *get_name(Business self) {
  if (self)
    return self->name;
  else
    return NULL;
}

void set_name(Business self, char *name) {
  if (self)
    self->name = g_strdup(name);
}

char *get_city(Business self) {
  if (self)
    return self->city;
  else
    return NULL;
}

void set_city(Business self, char *city) {
  if (self)
    self->city = g_strdup(city);
}

char *get_state(Business self) {
  if (self)
    return self->state;
  else
    return NULL;
}

void set_state(Business self, char *state) {
  if (self)
    self->state = g_strdup(state);
}

GPtrArray *get_categories(Business self) {
  if (self)
    return self->categories;
  else
    return NULL;
}

void set_categories(Business self, GPtrArray *categories) {
  if (self) {
    // ver melhor
    if (g_ptr_array_free(self->categories, TRUE) != NULL) {
      g_free(self->categories);
    }
    self->categories = categories;
  }
}

/* Business: free */

void free_business(Business self) {
  if (self) {
    free(self->business_id);
    free(self->name);
    free(self->city);
    free(self->state);
    g_ptr_array_free(self->categories, TRUE);
    // ??
    free(self);
  }
}

/* BusinessCollection: builder */
BusinessCollection create_business_collection(GArray *businesses,
                                              GHashTable *by_id,
                                              GHashTable *by_city,
                                              GTree *by_name) {
  BusinessCollection new_business_collection =
      (BusinessCollection)malloc(sizeof(struct business_collection));
  *new_business_collection =
      (struct business_collection){.businesses = businesses,
                                   .by_id = by_id,
                                   .by_city = by_city,
                                   .by_name = by_name};
  return new_business_collection;
}

/* business_collection: getters and setters */

GArray *get_businesses(BusinessCollection self) {
  if (self)
    return self->businesses;
  else
    return NULL;
}

void set_businesses(BusinessCollection self, GArray *businesses) {
  if (self) {
    if (g_array_get_element_size(self->businesses) > 0) {
      g_array_free(self->businesses, TRUE);
    }
    self->businesses = businesses;
  }
}

void add_business(BusinessCollection self, Business elem) {
  // adicionar no fim devido as Hashs nas reviews
  // ???
  if (self)
    g_array_prepend_val(self->businesses, elem);
}

GHashTable *get_by_id(BusinessCollection self) {
  if (self)
    return self->by_id;
  else
    return NULL;
}

void set_by_id(BusinessCollection self, GHashTable *by_id) {
  // libertar memoria ou nao
  if (self)
    self->by_id = by_id;
}

void add_by_id(BusinessCollection self, gpointer elem) {
  if (self)
    g_hash_table_add(self->by_id, elem);
}

GHashTable *get_by_city(BusinessCollection self) {
  if (self)
    return self->by_city;
  else
    return NULL;
}

void set_by_city(BusinessCollection self, GHashTable *by_city) {
  // libertar memoria ou nao
  if (self)
    self->by_city = by_city;
}

void add_by_city(BusinessCollection self, gpointer elem) {
  if (self)
    g_hash_table_add(self->by_city, elem);
}

GTree *get_by_name(BusinessCollection self) {
  if (self)
    return self->by_name;
  else
    return NULL;
}

void set_by_name(BusinessCollection self, GTree *by_name) {
  if (self) {
    self->by_name = by_name;
  }
}

void add_by_name(BusinessCollection self, gpointer key, gpointer value) {
  if (self)
    g_tree_insert(self->by_name, key, value);
}

/* BusinessCollection: free */

void free_business_collection(BusinessCollection self) {
  if (self) {
    g_array_free(self->businesses, TRUE);
    g_hash_table_destroy(self->by_id);
    g_hash_table_destroy(self->by_city);
    g_tree_destroy(self->by_name);
    // ???
    free(self);
  }
}
