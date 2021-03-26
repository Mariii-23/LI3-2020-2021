#include "users.h"
#include <glib.h>

struct user {
  char *user_id;
  char *name;
  GPtrArray *friends;
};

struct user_collection {
  GArray *users;     // struct user[]
  GHashTable *by_id; // user_id -> *user
};
