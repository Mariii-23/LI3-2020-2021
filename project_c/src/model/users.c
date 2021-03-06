/**
 * @file users.c
 * @author Mariana Rodrigues, Matilde Bravo e Pedro Alves
 * @date 4 Maio 2021
 * @brief This Module is responsible to manipulated all information relative a
 * users or users collections.
 */
#include "model/users.h"
#include "model/auxiliary.h"

#include <glib.h>
#include <string.h>

/**
 \brief Struct that stores one user.
 */
struct user {
  char *user_id;
  char *name;
};

/**
 \brief Struct that stores several users.
 */
struct user_collection {
  GHashTable *by_id; // <char* user_id,User user>
};

/**
 \brief Creates one user.
 * */
User create_user(char *user_id, char *name) {
  User new_user = malloc(sizeof(struct user));
  *new_user =
      (struct user){.user_id = g_strdup(user_id), .name = g_strdup(name)};
  return new_user;
}

/**
 \brief Given a user, returns his user id.
 * */
char *get_user_id(User user) {
  if (user) {
    return g_strdup(user->user_id);
  }
  return NULL;
}

/**
 \brief Given a user, returns his user name.
 * */
char *get_user_name(User user) {
  if (user) {
    return g_strdup(user->name);
  }
  return NULL;
}

/**
 \brief Given a user, returns a clone of him self.
 * */
static User clone_user(User user) {
  if (!user)
    return NULL;
  User new_user = malloc(sizeof(struct user));
  *new_user =
      (struct user){.user_id = get_user_id(user), .name = get_user_name(user)};
  return new_user;
}

/**
 \brief Given a user, returns a clone of him self.
 * */
static gpointer g_user_copy(gconstpointer src, gpointer data) {
  return clone_user((User)src);
}

/**
 \brief Free memory nedeed by one user.
 * */
void free_user(User user) {
  if (!user)
    return;
  if (user->user_id)
    free(user->user_id);
  if (user->name)
    free(user->name);

  free(user);
}

/**
 \brief Free memory nedeed by one user.
 * */
void g_free_user(gpointer data) { free_user((User)data); }

/**
 \brief Creates one user collection.
 * */
UserCollection create_user_collection() {
  UserCollection new_collection = malloc(sizeof(struct user_collection));
  new_collection->by_id =
      g_hash_table_new_full(g_str_hash, g_str_equal, NULL, g_free_user);
  return new_collection;
}

/**
 \brief Free memory
 * */
void free_map_user(gpointer key, gpointer value, gpointer user_data) {
  free(key);
  free_user(value);
}

/**
 \brief Free memory nedeed by one user collection.
 * */
void free_user_collection(UserCollection user_collection) {
  if (user_collection) {
    g_hash_table_destroy(user_collection->by_id);
    free(user_collection);
  }
}

/**
 \brief Added one given user to a user collection.
 * */
void add_user(UserCollection user_collection, User user) {
  if (user_collection && user) {
    User new = clone_user(user);
    g_hash_table_insert(user_collection->by_id, new->user_id, new);
  }
}

/**
 \brief Given user collection, returns a clone of a Glist* with all users.
 * */
GList *get_users(UserCollection collection) {
  if (collection->by_id == NULL)
    return NULL;
  return g_list_copy_deep(g_hash_table_get_values(collection->by_id),
                          g_user_copy, NULL);
}

/**
 \brief Given a user collection and a user id, returns a clone of this user or
 null in case don't exists.
 * */
User get_user_by_id(UserCollection user_collection, char *user_id) {
  User new = g_hash_table_lookup(user_collection->by_id, user_id);
  User resul = NULL;
  if (new)
    resul = clone_user(new);
  return resul;
}
