#include <glib.h>
#include <stdio.h>

#include "controller/commands.h"
#include "model/config.h"
#include "model/sgr.h"
#include "model/state.h"
#include "model/table.h"
#include "view/cli.h"

int main(int argc, char **argv) {

  char *path_to_config = NULL;
  if (argc > 1 && !strcmp(argv[1], "--config")) {
    if (argc == 2) {
      printf("Please provide a valid configuration file\n");
      return -1;
    } else {
      path_to_config = argv[2];
    }
  }
  STATE s = init_state();
  read_config_to_state(s, path_to_config);
  repl(s);
  free_state(s);
}
