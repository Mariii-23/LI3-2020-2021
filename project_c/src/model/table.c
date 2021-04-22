#include "table.h"

#include <stdio.h>
#include <stdlib.h>

#include "auxiliary.h"
#include "glib.h"

struct table {
    size_t number_fields;
    GPtrArray* lines;  // array de strings que será uma especie de matriz
};

TABLE new_table(GPtrArray* header) {
    TABLE table = malloc(sizeof(struct table));
    table->lines = header;  // breaks encapsulamento
    table->number_fields = header->len;
    // g_ptr_array_copy(fields, strdup_copy, NULL);
    // free_ptr_array_deep(fields);
    return table;
}

void add_field(TABLE table, char* field) {
    g_ptr_array_add(table->lines, g_strdup(field));
}

void fprintf_table(
    FILE* stream, TABLE table, char* delim_header, char* delim_main) {
    fprint_str_array(stream, table->lines, table->number_fields, delim_header);
}
char* table_index(TABLE table, size_t i, size_t j) {
    return table->lines->pdata[i * table->number_fields + j];
}
size_t get_number_lines_table(TABLE table) {
    return table->lines->len / table->number_fields;
}
size_t get_number_fields_table(TABLE table) {
    return table->number_fields;
}

void free_table(TABLE table) {
    free_ptr_array_deep(table->lines);
    free(table);
}
