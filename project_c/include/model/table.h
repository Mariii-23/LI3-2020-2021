#ifndef TABLE_H
#define TABLE_H
#include <stdio.h>

#include "glib.h"
typedef struct table *TABLE;

TABLE new_table_ptr_array(GPtrArray *header);
TABLE new_table(char **header, size_t number_fields);
void add_field(TABLE table, char *field);
void fprintf_table(FILE *stream, TABLE table, char *delim_header,
                   char *delim_main);
void add_footer(TABLE table, char *footer_name, char *footer_value);
char *table_index(TABLE table, size_t i, size_t j);
char *field_index(TABLE table, size_t i);
size_t get_number_fields_table(TABLE table);
size_t get_number_lines_table(TABLE table);
GPtrArray *get_fields_table(TABLE table);
GPtrArray *get_header_table(TABLE table);
TABLE new_table_without_fields(size_t number_fields);
void free_table(TABLE table);

#endif

