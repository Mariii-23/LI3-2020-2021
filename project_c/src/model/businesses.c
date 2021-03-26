#include "businesses.h"
#include <glib.h>

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
  GHashTable *by_city;  // char* -> tree de negócios

  GTree *by_name;
};
