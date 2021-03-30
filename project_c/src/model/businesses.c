#include "businesses.h"

#include <glib.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "auxiliary.h"
#include "users.h"

struct business {
    char* business_id;
    char* name;
    char* city;
    char* state;
    GPtrArray* categories;
};

struct business_collection {
    GPtrArray* businesses;
    GHashTable* by_id;
    GHashTable* by_city;
    GHashTable* by_name;  // char*(nome do business) -> tree de negócios
};

/* Business: builder */

Business create_business(
    char* business_id,
    char* name,
    char* city,
    char* state,
    GPtrArray* categories) {
    Business new_business = (Business) malloc(sizeof(struct business));
    *new_business = (struct business){
        .business_id = g_strdup(business_id),
        .name = g_strdup(name),
        .city = g_strdup(city),
        .state = g_strdup(state),
        .categories = categories};
    return new_business;
}

/* Business: getters and setters */

char* get_business_id(Business self) {
    if (self)
        return self->business_id;
    else
        return NULL;
}

void set_business_id(Business self, char* business_id) {
    if (self) self->business_id = g_strdup(business_id);
}

char* get_business_name(Business self) {
    if (self)
        return self->name;
    else
        return NULL;
}

void set_business_name(Business self, char* name) {
    if (self) self->name = g_strdup(name);
}

char* get_business_city(Business self) {
    if (self)
        return self->city;
    else
        return NULL;
}

void set_business_city(Business self, char* city) {
    if (self) self->city = g_strdup(city);
}

char* get_business_state(Business self) {
    if (self)
        return self->state;
    else
        return NULL;
}

void set_business_state(Business self, char* state) {
    if (self) self->state = g_strdup(state);
}

GPtrArray* get_business_categories(Business self) {
    if (self)
        return self->categories;
    else
        return NULL;
}

void set_busines_categories(Business self, GPtrArray* categories) {
    if (self) {
        // ver melhor
        if (self->categories) {
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
        free(self);
    }
}

/* BusinessCollection: builder */
BusinessCollection create_business_collection(
    GPtrArray* businesses,
    GHashTable* by_id,
    GHashTable* by_city,
    GHashTable* by_name) {
    BusinessCollection new_business_collection =
        (BusinessCollection) malloc(sizeof(struct business_collection));
    *new_business_collection = (struct business_collection){
        .businesses = businesses,
        .by_id = by_id,
        .by_city = by_city,
        .by_name = by_name};
    return new_business_collection;
}

/* business_collection: getters and setters */

GPtrArray* get_businesses(BusinessCollection self) {
    if (self)
        return self->businesses;
    else
        return NULL;
}

void set_businesses(BusinessCollection self, GPtrArray* businesses) {
    if (self) {
        self->businesses = businesses;
    }
}

void add_business(BusinessCollection self, Business elem) {
    if (self) g_ptr_array_add(self->businesses, elem);
}

GHashTable* get_businessCollection_by_id(BusinessCollection self) {
    if (self)
        return self->by_id;
    else
        return NULL;
}

User get_businessCollection_user_by_id(BusinessCollection self, int* user_id) {
    if (self)
        return g_hash_table_lookup(self->by_id, user_id);
    else
        return NULL;
}

void set_businessCollection_by_id(BusinessCollection self, GHashTable* by_id) {
    // libertar memoria ou nao
    if (self) self->by_id = by_id;
}

void add_businessCollection_by_id(BusinessCollection self, gpointer elem) {
    if (self) g_hash_table_add(self->by_id, elem);
}

GHashTable* get_businessCollection_business_by_city(
    BusinessCollection self, char* id) {
    if (self)
        return g_hash_table_lookup(self->by_id, id);
    else
        return NULL;
}

GHashTable* get_businessCollection_by_city(BusinessCollection self) {
    if (self)
        return self->by_city;
    else
        return NULL;
}

void set_businessCollection_by_city(
    BusinessCollection self, GHashTable* by_city) {
    if (!self) return;
    if (self->by_city) {
        free(self->by_city);
    }
    self->by_city = by_city;
}

void add_businessCollection_by_city(BusinessCollection self, gpointer elem) {
    if (self) g_hash_table_add(self->by_city, elem);
}

GHashTable* get_businessCollection_by_name(BusinessCollection self) {
    if (self)
        return self->by_name;
    else
        return NULL;
}

User get_businessCollection_user_by_name(BusinessCollection self, char* name) {
    if (self)
        return g_hash_table_lookup(self->by_name, name);
    else
        return NULL;
}

void set_businessCollection_by_name(
    BusinessCollection self, GHashTable* by_name) {
    if (self) {
        self->by_name = by_name;
    }
}

void add_businessCollection_by_name(
    BusinessCollection self, gpointer key, gpointer value) {
    if (self) g_hash_table_insert(self->by_name, key, value);
}

/* BusinessCollection: free */

void free_businessCollection(BusinessCollection self) {
    if (self) {
        g_ptr_array_free(self->businesses, TRUE);
        g_hash_table_foreach(self->by_id, map_free, NULL);
        g_hash_table_foreach(self->by_city, map_free, NULL);
        g_hash_table_foreach(self->by_name, map_free, NULL);
        g_hash_table_destroy(self->by_id);
        g_hash_table_destroy(self->by_city);
        g_hash_table_destroy(self->by_name);
        free(self);
    }
}
