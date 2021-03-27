#include <stdio.h>
#include <readline.h>
#include <history.h>
#include <glib.h>
#include <gmodule.h>
#include "colors.h"
#include "cli.h"

struct command {
  char *name;
  char *description;

  int n_args;
  char **args;
  // algum apontador para uma função
};

Commands init_commands() {
  return g_tree_new((int (*)(const void*, const void*)) g_strcmp0);
}

void insert_command(Commands commands, Command command) {
  g_tree_insert(commands, command->name, command);
}

Command make_command(const char *name, const char *desc, int n_args, char **args) {
  Command c = malloc(sizeof(struct command));

  c->name = g_strdup(name);
  c->description = g_strdup(desc);
  c->n_args = n_args;
  c->args = args;

  return c;
}

// Necessário para poder aceder dentro de tab_complete
Commands g_commands;

int tab_complete(int count, int key) {
  // Isto deve ser o texto até ao cursor, não 'h'
  /* GTreeNode *lower_bound = g_tree_lower_bound(g_commands, "h"); */

  return 0;
}

// Executa o Read-Eval-Print Loop
void repl(Commands commands) {
  char *line;

  g_commands = commands;
  rl_bind_key('\t', tab_complete);
  // O readline devolve NULL quando chega ao EOF
  while ((line = readline(BOLD FG_CYAN "> " RESET_ALL))) {
    // Se a linha não for nula...
    if (*line) {
      // adicionar ao histórico
      add_history(line);
    }
  }
}
