#include <glib.h>
#include <stdio.h>
#include "commands.h"
#include "cli.h"
#include "colors.h"

void cmd_quit(GArray *args) {
  printf("Goodbye!\n");
  exit(0);
}

void cmd_help(GArray *args) {
  printf(FG_BLUE UNDERLINED "Help for " BOLD "%s" RESET_ALL "\n", g_array_index(args, char*, 1));
}

// Regista todos os comandos
void register_commands(Commands commands) {
  insert_command(commands, make_command(":h", "Get help", cmd_help, 1, NULL));
  insert_command(commands, make_command(":help", "Get help", cmd_help, 1, NULL));
  insert_command(commands, make_command(":q", "Quit", cmd_quit, 0, NULL));
  insert_command(commands, make_command(":quit", "Quit", cmd_quit, 0, NULL));
}
