#include "reviews.h"
#include <glib.h>

struct review {
  char *review_id;
  char *user_id;
  char *business_id;

  float stars;
  int useful;
  int funny;
  int cool;

  GDateTime *date;
  char *text;
};

struct review_collection {
  GArray *reviews;
  GHashTable *by_id;
  GHashTable *by_user;
  GHashTable *by_business;
};
