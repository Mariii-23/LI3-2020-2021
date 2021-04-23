#include "businesses.h"

#include <glib.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "auxiliary.h"
#include "perfect_hash.h"
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
    PerfectHash by_letter;
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
        return g_strdup(self->business_id);
    else
        return NULL;
}

char* get_business_name(Business self) {
    if (self)
        return g_strdup(self->name);
    else
        return NULL;
}

char* get_business_city(Business self) {
    if (self)
        return g_strdup(self->city);
    else
        return NULL;
}

char* get_business_state(Business self) {
    if (self)
        return g_strdup(self->state);
    else
        return NULL;
}

// Encapsulamento ver
GPtrArray* get_business_categories(Business self) {
    if (self)
        return self->categories;
    else
        return NULL;
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
        (BusinessCollection) malloc(sizeof(struct business_collection));
    *new_business_collection = (struct business_collection){
        .businesses = g_ptr_array_new(),
        .by_id = g_hash_table_new(g_str_hash, g_str_equal),
        .by_letter = phf_new()};
    return new_business_collection;
}

void add_business(BusinessCollection collection, Business business) {
    g_ptr_array_add(collection->businesses, business);
    g_hash_table_insert(collection->by_id, get_business_id(business), business);
    phf_add(collection->by_letter, get_business_name(business), business);
}

Business get_businessCollection_business_by_id(
    BusinessCollection self, char* id) {
    if (self && id)
        return g_hash_table_lookup(self->by_id, id);
    else
        return NULL;
}

void add_businessCollection_by_id(BusinessCollection self, gpointer elem) {
    if (self && elem) g_hash_table_add(self->by_id, elem);
}

GPtrArray* get_businessCollection_business_by_letter(
    BusinessCollection self, char* name) {
    if (self)
        return phf_lookup(self->by_letter, name);
    else
        return NULL;
}

void add_businessCollection_by_letter(
    BusinessCollection self, Business business) {
    if (self) {
        phf_add(self->by_letter, get_business_name(business), business);
    }
}

/* BusinessCollection: free */

void free_businessCollection(BusinessCollection self) {
    if (self) {
        g_ptr_array_set_free_func(self->businesses, (void*) free_business);
        g_ptr_array_free(self->businesses, TRUE);
        g_hash_table_foreach(self->by_id, free_key, NULL);
        phf_free(self->by_letter);
        g_hash_table_destroy(self->by_id);
        free(self);
    }
}
