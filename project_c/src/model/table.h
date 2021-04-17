#ifndef TABLE_H
#define TABLE_H
#include "glib.h"
typedef struct table* TABLE;

TABLE new_table(GPtrArray* fields);
void set_fieldnames(TABLE table, GPtrArray* field_names);
void new_line(TABLE table);
void add_to_last_line(TABLE table, char* field);
void add_field_name(TABLE table, char* field_name);

#endif

