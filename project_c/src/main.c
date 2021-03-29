#include "view/cli.h"
#include "view/commands.h"
#include <stdio.h>
#include <glib.h>

int main() {
  Commands commands = init_commands();
  register_commands(commands);
  repl(commands);
}
