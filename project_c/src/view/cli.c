#include "cli.h"

#include <glib.h>
#include <gmodule.h>
#include <stdio.h>
#include <history.h>
#include <readline.h>

#include "colors.h"
#include "controller/parsing.h"
#include "controller/exec.h"

struct command {
  char* name;
  char* description;

  int n_args;
  char** args;

  cli_function_type function;
};

Commands init_commands() {
  return g_tree_new((int (*)(const void*, const void*)) g_strcmp0);
}

void insert_command(Commands commands, Command command) {
  g_tree_insert(commands, command->name, command);
}

Command make_command(
    const char* name,
    const char* desc,
    cli_function_type function,
    int n_args,
    char** args) {
  Command c = malloc(sizeof(struct command));

  c->name = g_strdup(name);
  c->description = g_strdup(desc);
  c->n_args = n_args;
  c->function = function;
  c->args = args;

  return c;
}

// Necessário para poder aceder dentro de tab_complete
Commands g_commands;

char** command_complete(const char* text, int start, int end) {
  GTreeNode* lower_bound = g_tree_lower_bound(g_commands, rl_line_buffer);
  int completion_buffer_size = 2, i = 1;
  char** completion_buffer = malloc(sizeof(char*) * completion_buffer_size);

  // Adicionamos o próprio à lista de sugestões, pois não o queremos
  // substituir
  completion_buffer[0] = g_strdup(text);

  while (lower_bound &&
      g_str_has_prefix(*(char**) g_tree_node_value(lower_bound), text)) {
    if (i >= completion_buffer_size - 1) {
      completion_buffer_size *= 2;
      completion_buffer = realloc(
          completion_buffer, sizeof(char*) * completion_buffer_size);
    }

    completion_buffer[i] =
      g_strdup(*(char**) g_tree_node_value(lower_bound));

    lower_bound = g_tree_node_next(lower_bound);
    i++;
  }

  completion_buffer[i] = NULL;

  // Caso só tenhamos um resultado, devolver logo esse
  if (i == 2) {
    g_free(completion_buffer[0]);
    completion_buffer[0] = completion_buffer[1];
    completion_buffer[1] = NULL;
  }

  if (i == 0) return NULL;

  return completion_buffer;
}

// Executa o Read-Eval-Print Loop
void repl(Commands commands) {
  char *line;

  g_commands = commands;
  rl_attempted_completion_function = command_complete;

  // O readline devolve NULL quando chega ao EOF
  while ((line = readline(BOLD FG_CYAN "> " RESET_ALL))) {
    // Se a linha não for nula...
    if (*line) {
      // adicionar ao histórico
      add_history(line);


      Token *toks = split_line(line);
      AST ast;
      int consumed = 0;
      SyntaxError *e = NULL;
      while (e == NULL && toks->type != TOK_FINISH) {
        e = parse_statement(toks, &ast, &consumed);
        toks += consumed;

        if (!e) {
          Variable *v = execute(&ast);

          print_var(v);

          free(v);
        } else {
          print_error(e, line);
        }
      }
    }
  }
}
