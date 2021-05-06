/**
 * @file config.c
 * @author Mariana Rodrigues, Matilde Bravo e Pedro Alves
 * @date 4 Maio 2021
 * @brief This Module is responsible to calculate and interpreted stats.
 * reviews and reviews collections.
 */

#include "model/config.h"
#include "controller/commands.h"
#include "model/state.h"
#include "model/table.h"
#include <glib.h>
#include <stdio.h>
#include <stdlib.h>

// O ficheiro de config é lido para o estado global
// Por exemplo, para uma linha do config
// NOME;valor
// é criada uma variável global NOME = "valor"
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
