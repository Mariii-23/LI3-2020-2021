#ifndef TABLE_H
#define TABLE_H
#include <stdio.h>

#include "glib.h"
typedef struct table* TABLE;

TABLE new_table(GPtrArray* fields);
void add_field(TABLE table, char* field);
void fprintf_table(
    FILE* stream, TABLE table, char* delim_header, char* delim_main);
char* table_index(TABLE table, size_t i, size_t j);
size_t get_number_fields_table(TABLE table);
size_t get_number_lines_table(TABLE table);
void free_table(TABLE table);

#endif

