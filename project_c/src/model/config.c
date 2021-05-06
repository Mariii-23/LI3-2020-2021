#include "model/config.h"
#include "controller/commands.h"
#include "model/state.h"
#include "model/table.h"
#include <glib.h>
#include <stdio.h>
#include <stdlib.h>

void read_config_to_state(STATE s, char *path_to_config) {
  if (path_to_config) {
    TABLE t = from_csv(path_to_config, ";");
    if (t) {
      for (int i = 0; i < get_number_lines_table(t); i++) {
        VariableValue v;
        v.string = g_strdup(table_index(t, i, 1));
        create_variable(s, init_var(VAR_STRING, v, table_index(t, i, 0)));
      }

      free_table(t);
    }
  }
}
