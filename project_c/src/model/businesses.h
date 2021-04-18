#ifndef BUSINESSES_H
#define BUSINESSES_H

#include <glib.h>

#include "../perfect_hash.h"
#include "users.h"

typedef struct business *Business;
typedef struct business_collection *BusinessCollection;

Business create_business(char *business_id, char *name, char *city, char *state,
                         GPtrArray *categories);

char *get_business_id(Business self);
void set_business_id(Business self, char *business_id);

char *get_business_name(Business self);
void set_business_name(Business self, char *name);

char *get_business_city(Business self);
void set_business_city(Business self, char *city);

char *get_business_state(Business self);
void set_business_state(Business self, char *state);

GPtrArray *get_business_categories(Business self);
void set_business_categories(Business self, GPtrArray *categories);

void free_business(Business self);

void set_businesses(BusinessCollection self, GPtrArray *businesses);
void add_business(BusinessCollection self, Business elem);

BusinessCollection create_business_collection();

Business get_businessCollection_business_by_id(BusinessCollection self,
                                               char *id);
void set_businessCollection_by_id(BusinessCollection self, GHashTable *by_id);

GPtrArray *get_businessCollection_business_by_city(BusinessCollection self,
                                                   char *city);
void set_businessCollection_by_city(BusinessCollection self,
                                    GHashTable *by_city);

GPtrArray *get_businessCollection_business_by_letter(BusinessCollection self,
                                                     char *id);
void set_businessCollection_by_letter(BusinessCollection self,
                                      PerfectHash by_letter);
void free_businessCollection(BusinessCollection self);
#endif
