#ifndef BUSINESSES_H
#define BUSINESSES_H

#include <glib.h>

typedef struct business *Business;
typedef struct business_collection *BusinessCollection;

Business create_business(char *business_id, char *name, char *city, char *state,
                         GPtrArray *categories);
char *get_business_id(Business self);
void set_business_id(Business self, char *business_id);
char *get_name(Business self);
void set_name(Business self, char *name);
char *get_city(Business self);
void set_city(Business self, char *city);
char *get_state(Business self);
void set_state(Business self, char *state);
GPtrArray *get_categories(Business self);
void set_categories(Business self, GPtrArray *categories);
void free_business(Business self);
BusinessCollection create_business_collection(GArray *businesses,
                                              GHashTable *by_id,
                                              GHashTable *by_city,
                                              GTree *by_name);
GArray *get_businesses(BusinessCollection self);
void set_businesses(BusinessCollection self, GArray *businesses);
void add_business(BusinessCollection self, Business elem);
GHashTable *get_by_id(BusinessCollection self);
void set_by_id(BusinessCollection self, GHashTable *by_id);
void add_by_id(BusinessCollection self, gpointer elem);
GHashTable *get_by_city(BusinessCollection self);
void set_by_city(BusinessCollection self, GHashTable *by_city);
void add_by_city(BusinessCollection self, gpointer elem);
GTree *get_by_name(BusinessCollection self);
void set_by_name(BusinessCollection self, GTree *by_name);

void add_by_name(BusinessCollection self, gpointer key, gpointer value);
void free_business_collection(BusinessCollection self);
#endif
