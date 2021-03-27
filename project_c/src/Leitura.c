#include <glib.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "model/users.h"
#define LINESIZE 100

static User parse_user_line(char* str) {
    GPtrArray* friends = g_ptr_array_new();
    char* user_id = strtok(str, ";");
    char* name = strtok(NULL, ";");
    char* friend = strtok(NULL, ";");
    friend = strtok(friend, ",");
    while (friend) {
        g_ptr_array_add(friends, g_strdup(friend));
        printf("friend : %s\n", friend);
        friend = strtok(NULL, ",");
    }
    return create_user(user_id, name, friends);
}
static char* read_line(FILE* fp) {
    char linha[LINESIZE];
    bool has_new_line = false;
    GString* dynamic_string = g_string_sized_new(LINESIZE);
    while (!has_new_line) {
        if (!fgets(linha, LINESIZE, fp)) return NULL;
        g_string_append(dynamic_string, linha);
        has_new_line = strchr(linha, '\n') != NULL;
    }
    g_string_append_unichar(dynamic_string, 0);  // to change
    return g_string_free(dynamic_string, FALSE);
}

UserCollection collect_users(FILE* fp) {
    char* line;
    GArray* users = g_array_new(FALSE, TRUE, sizeof(User));
    GHashTable* by_id = g_hash_table_new(g_str_hash, g_str_equal);
    while ((line = read_line(fp))) {
        parse_user_line(line);
        // populate hashtable
    }
    return create_user_collection(users, by_id);
}
