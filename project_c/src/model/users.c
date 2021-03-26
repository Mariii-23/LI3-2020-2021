#include "users.h"

#include <glib.h>
#include <string.h>

struct user {
    char* user_id;
    char* name;
    GPtrArray* friends;  // char* []
};

struct user_collection {
    GArray* users;      // struct user[]
    GHashTable* by_id;  // <user_id*,user*>
};

char const* get_user_id(User user) {
    return user->user_id;
}
char const* get_name(User user) {
    return user->name;
}
GPtrArray const* get_friends(User user) {
    return user->friends;
}
GArray const* get_users(UserCollection collection) {
    return collection->users;
}
User const* get_user_by_id(UserCollection user_collection, int* user_id) {
    return g_hash_table_lookup(user_collection->by_id, user_id);
}
