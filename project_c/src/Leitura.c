#include <glib.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "model/users.h"
#define LINESIZE 100

User parse_user_line(char* str) {
    GPtrArray* friends = g_ptr_array_new();
    char* user_id = strsep(&str, ";");
    char* name = strsep(&str, ";");
    char* friend = strsep(&str, ",");
    while (friend) {
        printf("%s\n", friend);
        g_ptr_array_add(friends, g_strdup(friend));
        friend = strsep(&str, ",");
    }
    return create_user(user_id, name, friends);
}
char* ler_linha(FILE* fp) {
    char linha[LINESIZE];
    bool has_new_line = false;
    GString* dynamic_string = g_string_sized_new(LINESIZE);
    while (!has_new_line) {
        if (!fgets(linha, LINESIZE, fp)) return NULL;
        g_string_append(dynamic_string, linha);
        has_new_line = strchr(linha, '\n') != NULL;
    }
    g_string_append_unichar(dynamic_string, 0);
    parse_user_line(dynamic_string->str);
    return g_string_free(dynamic_string, FALSE);
}

int main(int argc, char** argv) {
    FILE* fp = fopen(argv[1], "r");
    char line[50];
    fgets(line, 50, fp);
    while (ler_linha(fp))
        ;
}
