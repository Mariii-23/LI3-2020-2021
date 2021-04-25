#include "cli.h"

#include <glib.h>
#include <gmodule.h>

#include "colors.h"
#include "controller/exec.h"
#include "controller/parsing.h"
#include "model/state.h"
#include "readline.h"
#include "view_commands.h"

char **command_complete(const char *text, int start, int end) {
  /* GTreeNode* lower_bound = g_tree_lower_bound(g_commands, rl_line_buffer); */
  /* int completion_buffer_size = 2, i = 1; */
  /* char** completion_buffer = malloc(sizeof(char*) * completion_buffer_size);
   */

  /* // Adicionamos o próprio à lista de sugestões, pois não o queremos */
  /* // substituir */
  /* completion_buffer[0] = g_strdup(text); */

  /* while (lower_bound && */
  /*        g_str_has_prefix(*(char**) g_tree_node_value(lower_bound), text)) {
   */
  /*     if (i >= completion_buffer_size - 1) { */
  /*         completion_buffer_size *= 2; */
  /*         completion_buffer = realloc( */
  /*             completion_buffer, sizeof(char*) * completion_buffer_size); */
  /*     } */

  /*     completion_buffer[i] = */
  /*         g_strdup(*(char**) g_tree_node_value(lower_bound)); */

  /*     lower_bound = g_tree_node_next(lower_bound); */
  /*     i++; */
  /* } */

  /* completion_buffer[i] = NULL; */

  /* // Caso só tenhamos um resultado, devolver logo esse */
  /* if (i == 2) { */
  /*     g_free(completion_buffer[0]); */
  /*     completion_buffer[0] = completion_buffer[1]; */
  /*     completion_buffer[1] = NULL; */
  /* } */

  /* if (i == 0) return NULL; */

  /* return completion_buffer; */
  return NULL;
}

#define define_function(state, name, handler, ret, n_args, help, ...)          \
  {                                                                            \
    VariableType f_args[] = {__VA_ARGS__};                                     \
    VariableValue val;                                                         \
    val.function = create_function(n_args, ret, handler, f_args, help);        \
    create_variable(state, init_var(VAR_FUNCTION, val, name));                 \
  }

// Executa o Read-Eval-Print Loop
void repl() {
  char *line;

  rl_attempted_completion_function = command_complete;

  STATE state = init_state();

  // Funções novas
  define_function(state, "print", print, VAR_VOID, 1, NULL, VAR_ANY);
  define_function(state, "quit", quit, VAR_VOID, 0, "Quit");
  define_function(state, "show", show, VAR_VOID, 1, "Show Table", VAR_TABLE);
  define_function(state, "from_csv", cmd_from_csv, VAR_TABLE, 2, "From CSV",
                  VAR_STRING, VAR_STRING);
  define_function(state, "to_csv", cmd_to_csv, VAR_VOID, 3, "To CSV", VAR_TABLE,
                  VAR_STRING, VAR_STRING);
  // Query 1
  define_function(state, "load_sgr", cmd_load_sgr, VAR_SGR, 3, "Load SGR",
                  VAR_STRING, VAR_STRING, VAR_STRING);
  // Query 2
  define_function(state, "businesses_started_by_letter",
                  cmd_businesses_started_by_letter, VAR_TABLE, 2,
                  "Businesses started by letter", VAR_SGR, VAR_STRING);

  // Query 3
  define_function(state, "business_info", cmd_business_info, VAR_TABLE, 2,
                  "Businesses information", VAR_SGR, VAR_STRING);

  // Query 4
  define_function(state, "businesses_reviewed", cmd_businesses_reviewed,
                  VAR_TABLE, 2, "Businesses reviewed", VAR_SGR, VAR_STRING);

  // Query 5
  define_function(state, "businesses_with_stars_and_city",
                  cmd_businesses_with_stars_and_city, VAR_TABLE, 3,
                  "Businesses  with stars and city", VAR_SGR, VAR_NUMBER,
                  VAR_STRING);
  // Query 6
  define_function(state, "top_businesses_by_city", cmd_top_businesses_by_city,
                  VAR_TABLE, 2, "Top Businesses by city", VAR_SGR, VAR_NUMBER);
  // Query 7
  define_function(state, "international_users", cmd_international_users,
                  VAR_TABLE, 1, "International users", VAR_SGR);
  // Query 8
  define_function(state, "top_businesses_with_category",
                  cmd_top_businesses_with_category, VAR_TABLE, 3,
                  "Top businesses with category", VAR_SGR, VAR_NUMBER,
                  VAR_STRING);
  // Query 9
  define_function(state, "reviews_with_word", cmd_reviews_with_word, VAR_TABLE,
                  2, "Reviews with word", VAR_SGR, VAR_STRING);

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
          Variable v = execute(state, &ast);

          if (v) {
            if (get_var_type(v) != VAR_VOID)
              print_var(v);

            free_if_possible(state, v);
          }
        } else {
          print_error(e, line);
        }
      }
    }
  }
}
