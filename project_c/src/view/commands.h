#ifndef COMMANDS_H
#define COMMANDS_H

#include "cli.h"
#include <glib.h>

void cmd_quit(GArray *args);
void cmd_help(GArray *args);

void register_commands(Commands commands);

#endif
