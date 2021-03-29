#include "view/cli.h"
#include <stdio.h>

void quit_cli(int argc, char **argv) {
  printf("Goodbye :(\n");
  exit(0);
}

void help_cli(int argc, char **argv) {
  printf("Help for %s :)\n", *argv);
}

int main() {
  Commands commands = init_commands();

  insert_command(commands, make_command(":h", "Get help", help_cli, 1, NULL));
  insert_command(commands, make_command(":help", "Get help", help_cli, 1, NULL));
  insert_command(commands, make_command(":quit", "Quit", quit_cli, 0, NULL));

  repl(commands);
}
