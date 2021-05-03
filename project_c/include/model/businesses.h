#ifndef BUSINESSES_H
#define BUSINESSES_H

#include <glib.h>

#include "perfect_hash.h"
#include "users.h"

typedef struct business *Business;
typedef struct business_collection *BusinessCollection;

Business create_business(char *business_id, char *name, char *city, char *state,
                         GPtrArray *categories);

char *get_business_id(Business self);

char *get_business_name(Business self);

char *get_business_city(Business self);

char *get_business_state(Business self);

GPtrArray *get_business_categories(Business self);

void free_business(Business self);
void g_free_business(gpointer data);

void add_business(BusinessCollection self, Business elem);

BusinessCollection create_business_collection();

Business get_businessCollection_business_by_id(BusinessCollection self,
                                               char *id);
GPtrArray *get_businessCollection_business_by_city(BusinessCollection self,
                                                   char *city);

GPtrArray *get_businessCollection_business_by_letter(BusinessCollection self,
                                                     char *name);

char *get_state_by_business_id(BusinessCollection business_collection,
                               char *business_id);

void free_businessCollection(BusinessCollection self);
#endif
