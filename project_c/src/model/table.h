#ifndef TABLE_H
#define TABLE_H
#include <stdio.h>

#include "glib.h"
typedef struct table* TABLE;

TABLE new_table(GPtrArray* fields);
void set_fieldnames(TABLE table, GPtrArray* field_names);
void new_line(TABLE table);
void add_to_last_line(TABLE table, char* field);
void add_field_name(TABLE table, char* field_name);
char* table_index(TABLE table, size_t i, size_t j);
void fprintf_table(
    FILE* stream, TABLE table, char* delim_header, char* delim_main);
GPtrArray* get_field_names(TABLE table);
size_t get_number_lines_table(TABLE table);
void free_table(TABLE table);
#endif

