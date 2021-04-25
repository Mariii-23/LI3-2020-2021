#ifndef COMMANDS_H
#define COMMANDS_H

#include <glib.h>

#include "model/table.h"

typedef enum { LT = -1, EQ = 0, GT = 1 } OPERATOR;

void cmd_quit(GArray* args);
void cmd_help(GArray* args);

TABLE from_csv(char* filename, char* delim);
void to_csv(TABLE table, char* filename, char* delim);
TABLE projection(TABLE table, GPtrArray* colunas);

#endif
