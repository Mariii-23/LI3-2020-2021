#include "view/cli.h"

int main() {
  Commands commands = init_commands();
  insert_command(commands, make_command(":h", "Get help", 1, NULL));
  insert_command(commands, make_command(":help", "Get help", 1, NULL));
  insert_command(commands, make_command(":quit", "Quit", 0, NULL));

  repl(commands);
}
