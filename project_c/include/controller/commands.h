#ifndef COMMANDS_H
#define COMMANDS_H

#include <glib.h>

#include "model/table.h"

typedef enum { LT = -1, EQ = 0, GT = 1 } OPERATOR;

void cmd_quit(GArray *args);
void cmd_help(GArray *args);

TABLE from_csv(char *filename, char *delim);
void to_csv(TABLE table, char *filename, char *delim);
TABLE projection(TABLE table, GArray *colunas);
TABLE filter(TABLE table, char *field_name, char *value, OPERATOR op);
TABLE join(TABLE table_x, TABLE table_y);
char *avg(TABLE table, char *field_name);
char *max_table(TABLE table, char *field_name);
char *min_table(TABLE table, char *field_name);

#endif
