#include "users.h"

#include <glib.h>
#include <string.h>

struct user {
    char* user_id;
    char* name;
    GPtrArray* friends;  // char* user_id []
};

struct user_collection {
    GArray* users;      // User[]
    GHashTable* by_id;  // <char* user_id,User user*>
};

User create_user(char* user_id, char* name, GPtrArray* friends) {
    User new_user = malloc(sizeof(struct user));
    *new_user = (struct user){
        .user_id = g_strdup(user_id),
        .name = g_strdup(name),
        .friends = friends};
    return new_user;
}

UserCollection create_collection(GArray* users, GHashTable* by_id) {
    UserCollection new_collection = malloc(sizeof(struct user_collection));
    *new_collection = (struct user_collection){.users = users, .by_id = by_id};
    return new_collection;
}

void free_user(User user) {
    free(user->user_id);
    free(user->name);
    g_ptr_array_set_free_func(user->friends, free);
    g_ptr_array_free(user->friends, TRUE);
}

void free_user_collection(UserCollection user_collection) {
    g_array_free(user_collection->users, TRUE);
    g_hash_table_destroy(
        user_collection->by_id);  //  calls GDestroyNotify function
}

void add_user(UserCollection user_collection, User user) {
    g_array_append_vals(user_collection->users, user, 1);
    g_hash_table_insert(user_collection->by_id, user->user_id, user);
}

void add_friend(User user, char* user_id) {
    g_ptr_array_add(user->friends, g_strdup(user_id));
}
char const* get_user_id(User user) {
    return user->user_id;
}
char const* get_user_name(User user) {
    return user->name;
}
GPtrArray* get_friends(User user) {
    return user->friends;
}
GArray* get_users(UserCollection collection) {
    return collection->users;
}
User* get_user_by_id(UserCollection user_collection, int* user_id) {
    return g_hash_table_lookup(user_collection->by_id, user_id);
}
void set_user_id(User user, char* user_id) {
    user->user_id = g_strdup(user_id);
}
void set_name(User user, char* name) {
    user->name = g_strdup(name);
}
