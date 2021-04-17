#include "table.h"

#include <stdio.h>
#include <stdlib.h>

#include "auxiliary.h"
#include "glib.h"

struct table {
    GPtrArray* field_names;  // Nomes dos fields, no caso de um business são os
                             // campos dos businesses que é cada coluna
    GPtrArray*
        lines;  // cada linha, que neste caso seria informação sobre um business
};

TABLE new_table(GPtrArray* fields) {
    TABLE table = malloc(sizeof(struct table));
    table->field_names = g_ptr_array_copy(fields, strdup_copy, NULL);
    table->lines = g_ptr_array_new();
    return table;
}
void new_line(TABLE table) {
    g_ptr_array_add(table->lines, g_ptr_array_new());
}

void add_to_last_line(TABLE table, char* field) {
    GPtrArray* last_line = get_last_ptr(table->lines);
    g_ptr_array_add(last_line, g_strdup(field));
}

void add_field_name(TABLE table, char* field_name) {
    g_ptr_array_add(table->field_names, g_strdup(field_name));
}

void fprintf_table(
    FILE* stream, TABLE table, char* delim_header, char* delim_main) {
    fprint_str_array(stream, table->field_names, delim_header);
    for (int i = 0; i < table->lines->len; i++) {
        fprint_str_array(
            stream, g_ptr_array_index(table->lines, i), delim_main);
    }
}
size_t number_lines_table(TABLE table) {
    return table->lines->len;
}

GPtrArray* line_at_index_table(TABLE table, size_t index) {
    return g_ptr_array_index(table->lines, index);
}

