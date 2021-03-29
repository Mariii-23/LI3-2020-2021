#ifndef CLI_H
#define CLI_H

#include <glib.h>

typedef void (*cli_function_type)(GArray *args);
typedef struct command *Command;
typedef GTree *Commands;

void repl(Commands commands);

Commands init_commands();
void insert_command(Commands commands, Command command);

Command make_command(const char *name, const char *desc, cli_function_type function, int n_args, char **args);

#endif
