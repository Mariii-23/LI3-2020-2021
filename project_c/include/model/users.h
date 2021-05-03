#ifndef UTILIZADORES_H
#define UTILIZADORES_H

#include <glib.h>

typedef struct user *User;
typedef struct user_collection *UserCollection;

User create_user(char *user_id, char *name);
UserCollection create_user_collection();
void free_user(User user);
void free_user_collection(UserCollection user_collection);
void add_user(UserCollection user_collection, User user);
char *get_user_id(User user);
char *get_user_name(User user);
GList *get_users(UserCollection user_collection);
User get_user_by_id(UserCollection user_collection, char *user_id);

#endif
