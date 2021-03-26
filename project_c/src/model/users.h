#ifndef UTILIZADORES_H
#define UTILIZADORES_H

#include <glib.h>

typedef struct user* User;
typedef struct user_collection* UserCollection;

char const* get_user_id(User user);
char const* get_name(User user);
GPtrArray const* get_friends(User user);
GArray const* get_users(UserCollection user_collection);
User const* get_user_by_id(UserCollection user_collection, int* user_id);

#endif
