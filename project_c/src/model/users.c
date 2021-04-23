#include "users.h"

#include <glib.h>
#include <string.h>

#include "auxiliary.h"

struct user {
  char *user_id;
  char *name;
  GPtrArray *friends; // char* user_id []
};

struct user_collection {
  GHashTable *by_id; // <char* user_id,User user>
};

User create_user(char *user_id, char *name, GPtrArray *friends) {
  User new_user = malloc(sizeof(struct user));
  *new_user =
      (struct user){.user_id = g_strdup(user_id),
                    .name = g_strdup(name),
                    .friends = g_ptr_array_copy(friends, strdup_copy, NULL)};
  return new_user;
}

// using const and strdup with getters has its disadvantages
char *get_user_id(User user) {
  if (user) {
    return g_strdup(user->user_id);
  }
  return NULL;
}

char *get_user_name(User user) {
  if (user) {
    return g_strdup(user->name);
  }
  return NULL;
}

GPtrArray *get_user_friends(User user) {
  return g_ptr_array_copy(user->friends, strdup_copy, NULL);
}

static User clone_user(User user) {
  User new_user = malloc(sizeof(struct user));
  *new_user = (struct user){.user_id = get_user_id(user),
                            .name = get_user_name(user),
                            .friends = get_user_friends(user)};
  return new_user;
}

static gpointer g_user_copy(gconstpointer src, gpointer data) {
  return clone_user((User)src);
}

UserCollection create_user_collection() {
  UserCollection new_collection = malloc(sizeof(struct user_collection));
  new_collection->by_id = g_hash_table_new(g_str_hash, g_str_equal);
  return new_collection;
}

void free_user(User user) {
  if (user) {
    free(user->user_id);
    free(user->name);
    g_ptr_array_set_free_func(user->friends, free);
    g_ptr_array_free(user->friends, TRUE);
  }
  free(user);
}
void free_map_user(gpointer key, gpointer value, gpointer user_data) {
  free(key);
  free_user(value);
}

void free_user_collection(UserCollection user_collection) {
  if (user_collection) {
    g_hash_table_foreach(user_collection->by_id, free_map_user, NULL);
    g_hash_table_destroy(user_collection->by_id);
  }
}

void add_user(UserCollection user_collection, User user) {
  if (user_collection && user) {
    User new = clone_user(user);
    g_hash_table_insert(user_collection->by_id, user->user_id, new);
  }
}

void add_friend(User user, char *user_id) {
  if (user && user_id) {
    g_ptr_array_add(user->friends, g_strdup(user_id));
  }
}

GList *get_users(UserCollection collection) {
  return g_list_copy_deep(g_hash_table_get_values(collection->by_id),
                          g_user_copy, NULL);
}

User get_user_by_id(UserCollection user_collection, int *user_id) {
  return clone_user(g_hash_table_lookup(user_collection->by_id, user_id));
}
