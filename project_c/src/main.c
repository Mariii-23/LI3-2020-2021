#include <glib.h>
#include <stdio.h>

#include "view/cli.h"
#include "view/view_commands.h"

int main() {
    Commands commands = init_commands();
    repl(commands);
}
