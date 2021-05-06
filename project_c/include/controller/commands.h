/**
 * @file commands.h
 * @author Mariana Rodrigues, Matilde Bravo e Pedro Alves
 * @date 4 Maio 2021
 * @brief This Module is responsible to manipulated all information.
 */

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
float avg(TABLE table, char *field_name);
TABLE max_table(TABLE table, char *field_name);
TABLE min_table(TABLE table, char *field_name);

#endif
