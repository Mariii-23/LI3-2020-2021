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

/* Business: getters and setters */

char const *getBusinessId(Business self) {
  if (self)
    return self->business_id;
  else
    return NULL;
}

void *setBusinessId(Business self, char *business_id) {
  if (self)
    strcpy(self->business_id, business_id);
}

char const *getName(Business self) {
  if (self)
    return self->name;
  else
    return NULL;
}

void *setName(Business self, char *name) {
  if (self)
    strcpy(self->name, name);
}

char const *getCity(Business self) {
  if (self)
    return self->city;
  else
    return NULL;
}

void *setCity(Business self, char *city) {
  if (self)
    strcpy(self->city, city);
}

char const *getState(Business self) {
  if (self)
    return self->state;
  else
    NULL;
}

void *setState(Business self, char *state) {
  if (self)
    strcpy(self->state, state);
}

GPtrArray const *getCategories(Business self) {
  if (self)
    return self->categories;
  else
    NULL;
}

void *setCategories(Business self, GPtrArray *categories) {
  if (self) {
    // ver melhor
    if (g_ptr_array_free(self->categories, TRUE) != NULL) {
      g_free(self->categories);
    }
    self->categories = categories;
  }
}

/* business_collection: getters and setters */

GArray const *getBusinesses(BusinessCollection self) {
  if (self)
    return self->businesses;
  else
    NULL;
}

void *setBusinesses(BusinessCollection self, GArray *businesses) {
  if (self) {
    if (g_array_get_element_size(self->businesses) > 0) {
      g_array_free(self->businesses, TRUE);
    }
    self->businesses = businesses;
  }
}

void *addBusiness(BusinessCollection self, Business elem) {
  // adicionar no fim devido as Hashs nas reviews
  // ???
  if (self)
    g_array_prepend_val(self->businesses, elem);
}

GHashTable const *getBy_id(BusinessCollection self) {
  if (self)
    return self->by_id;
  else
    NULL;
}

void *setBy_id(BusinessCollection self, GHashTable *by_id) {
  // libertar memoria ou nao
  if (self)
    self->by_id = by_id;
}

void *addBy_id(BusinessCollection self, gpointer elem) {
  if (self)
    g_hash_table_add(self->by_id, elem);
}

GHashTable const *getBy_city(BusinessCollection self) {
  if (self)
    return self->by_city;
  else
    return NULL;
}

void *setBy_city(BusinessCollection self, GHashTable *by_city) {
  // libertar memoria ou nao
  if (self)
    self->by_city = by_city;
}

void *addBy_city(BusinessCollection self, gpointer elem) {
  if (self)
    g_hash_table_add(self->by_city, elem);
}

GTree const *getBy_name(BusinessCollection self) {
  if (self)
    return self->by_name;
}

void *setBy_name(BusinessCollection self, GTree *by_name) {
  if (self) {
    self->by_name = by_name;
  }
}

void *addBy_name(BusinessCollection self, gpointer key, gpointer value) {
  if (self)
    g_tree_insert(self->by_name, key, value);
}
