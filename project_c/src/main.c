#include "view/cli.h"
#include <stdio.h>
#include <glib.h>

void quit_cli(GArray *args) {
  printf("Goodbye :(\n");
  exit(0);
}

void help_cli(GArray *args) {
  printf("Help for %s :)\n", g_array_index(args, char*, 1));
}

int main() {
  Commands commands = init_commands();

  insert_command(commands, make_command(":h", "Get help", help_cli, 1, NULL));
  insert_command(commands, make_command(":help", "Get help", help_cli, 1, NULL));
  insert_command(commands, make_command(":quit", "Quit", quit_cli, 0, NULL));

  repl(commands);
}
