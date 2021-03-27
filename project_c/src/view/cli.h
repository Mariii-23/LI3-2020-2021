#ifndef CLI_H
#define CLI_H

#include <glib.h>

typedef struct command *Command;
typedef GTree *Commands;

void repl(Commands commands);

Commands init_commands();
void insert_command(Commands commands, Command command);

Command make_command(const char *name, const char *desc, int n_args, char **args);

#endif
