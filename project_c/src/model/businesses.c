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
    GHashTable* by_letter;  //
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
    if (self && business_id) self->business_id = g_strdup(business_id);
}

char* get_business_name(Business self) {
    if (self)
        return self->name;
    else
        return NULL;
}

void set_business_name(Business self, char* name) {
    if (self && name) self->name = g_strdup(name);
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
    if (self && state) self->state = g_strdup(state);
}

GPtrArray* get_business_categories(Business self) {
    if (self)
        return self->categories;
    else
        return NULL;
}

void set_busines_categories(Business self, GPtrArray* categories) {
    if (self && categories) {
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
    GHashTable* by_letter) {
    BusinessCollection new_business_collection =
        (BusinessCollection) malloc(sizeof(struct business_collection));
    *new_business_collection = (struct business_collection){
        .businesses = businesses,
        .by_id = by_id,
        .by_city = by_city,
        .by_letter = by_letter};
    return new_business_collection;
}

void set_businesses(BusinessCollection self, GPtrArray* businesses) {
    if (self && businesses) {
        self->businesses = businesses;
    }
}

void add_business(BusinessCollection self, Business elem) {
    if (self && elem) g_ptr_array_add(self->businesses, elem);
}

Business get_businessCollection_business_by_id(
    BusinessCollection self, int* user_id) {
    if (self && user_id)
        return g_hash_table_lookup(self->by_id, user_id);
    else
        return NULL;
}

void set_businessCollection_by_id(BusinessCollection self, GHashTable* by_id) {
    if (self && by_id) self->by_id = by_id;
}

void add_businessCollection_by_id(BusinessCollection self, gpointer elem) {
    if (self && elem) g_hash_table_add(self->by_id, elem);
}

Business* get_businessCollection_business_by_city(
    BusinessCollection self, char* city) {
    if (self && city)
        return g_hash_table_lookup(self->by_city, city);
    else
        return NULL;
}

void set_businessCollection_by_city(
    BusinessCollection self, GHashTable* by_city) {
    if (self && by_city) self->by_city = by_city;
}

void add_businessCollection_by_city(BusinessCollection self, gpointer elem) {
    if (self && elem) g_hash_table_add(self->by_city, elem);
}

Business get_businessCollection_business_by_letter(
    BusinessCollection self, char* name) {
    if (self)
        return g_hash_table_lookup(self->by_letter, name);
    else
        return NULL;
}

void set_businessCollection_by_letter(
    BusinessCollection self, GHashTable* by_letter) {
    if (self) {
        self->by_letter = by_letter;
    }
}

void add_businessCollection_by_letter(
    BusinessCollection self, Business business) {
    if (self) g_hash_table_add(self->by_letter, get_business_name(business));
}

/* BusinessCollection: free */

void free_businessCollection(BusinessCollection self) {
    if (self) {
        g_ptr_array_set_free_func(self->businesses, (void*) free_business);
        g_ptr_array_free(self->businesses, TRUE);
        g_hash_table_foreach(self->by_id, free_key, NULL);
        g_hash_table_foreach(self->by_city, free_key_value, "");
        g_hash_table_foreach(
            self->by_letter,
            free_key_value,
            "");  // also frees array but not its content
        g_hash_table_destroy(self->by_id);
        g_hash_table_destroy(self->by_city);
        g_hash_table_destroy(self->by_letter);
        free(self);
    }
}
