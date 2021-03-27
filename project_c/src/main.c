#include "view/cli.h"

int main() {
  Commands commands = init_commands();
  insert_command(commands, make_command(":h", "Get help", 1, NULL));

  repl(commands);
}
