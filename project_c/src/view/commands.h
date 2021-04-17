#ifndef COMMANDS_H
#define COMMANDS_H

#include <glib.h>

#include "cli.h"
#include "model/table.h"

void cmd_quit(GArray* args);
void cmd_help(GArray* args);

void register_commands(Commands commands);
TABLE from_csv(char* filename, char* delim);
void to_csv(TABLE table, char* filename, char* delim);

#endif
