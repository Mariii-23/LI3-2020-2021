/**
 * @file cli.c
 * @author Mariana Rodrigues, Matilde Bravo e Pedro Alves
 * @date 4 Maio 2021
 * @brief This Module is responsible to manipulated all information.
 */

#include "view/cli.h"

#include <glib.h>
#include <gmodule.h>

#include "controller/exec.h"
#include "controller/parsing.h"
#include "model/state.h"
#include "view/colors.h"
#include "view/help.h"
#include "view/readline.h"
#include "view/view_commands.h"

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

// Executa o Read-Eval-Print Loop
void repl(STATE state) {
  char *line;

  // TODO autocomplete!
  /* rl_attempted_completion_function = command_complete; */

  // Funções novas
  define_function(state, "print", print, VAR_VOID, 0, 1, "Print a variable",
                  VAR_ANY);
  define_function(state, "quit", quit, VAR_VOID, 0, 0, "Quit");
  define_function(state, "help", help, VAR_VOID, 0, 1,
                  "Get help on a specific function", VAR_FUNCTION);
  define_function(state, "show", show, VAR_VOID, 0, 1, CMD_SHOW_HELP,
                  VAR_TABLE);
  define_function(state, "from_csv", cmd_from_csv, VAR_TABLE, 0, 2, "From CSV",
                  VAR_STRING, VAR_STRING);
  define_function(state, "to_csv", cmd_to_csv, VAR_VOID, 0, 3, CMD_TO_CSV_HELP,
                  VAR_TABLE, VAR_STRING, VAR_STRING);
  // Query 1
  define_function(state, "load_sgr", cmd_load_sgr, VAR_SGR, 1, 3,
                  CMD_LOAD_SGR_HELP, VAR_STRING, VAR_STRING, VAR_STRING);
  // Query 2
  define_function(state, "businesses_started_by_letter",
                  cmd_businesses_started_by_letter, VAR_TABLE, 0, 2,
                  CMD_BUSINESSES_STARTED_BY_LETTER_HELP, VAR_SGR, VAR_STRING);

  // Query 3
  define_function(state, "business_info", cmd_business_info, VAR_TABLE, 0, 2,
                  CMD_BUSINESS_INFO_HELP, VAR_SGR, VAR_STRING);

  // Query 4
  define_function(state, "businesses_reviewed", cmd_businesses_reviewed,
                  VAR_TABLE, 0, 2, CMD_BUSINESSES_REVIEWED_HELP, VAR_SGR,
                  VAR_STRING);

  // Query 5
  define_function(state, "businesses_with_stars_and_city",
                  cmd_businesses_with_stars_and_city, VAR_TABLE, 0, 3,
                  CMD_BUSINESSES_WITH_STARS_AND_CITY_HELP, VAR_SGR, VAR_FLOAT,
                  VAR_STRING);
  // Query 6
  define_function(state, "top_businesses_by_city", cmd_top_businesses_by_city,
                  VAR_TABLE, 0, 2, CMD_TOP_BUSINESSES_BY_CITY_HELP, VAR_SGR,
                  VAR_NUMBER);
  // Query 7
  define_function(state, "international_users", cmd_international_users,
                  VAR_TABLE, 0, 1, CMD_INTERNATIONAL_USERS_HELP, VAR_SGR);
  // Query 8
  define_function(state, "top_businesses_with_category",
                  cmd_top_businesses_with_category, VAR_TABLE, 0, 3,
                  CMD_TOP_BUSINESSES_WITH_CATEGORY_HELP, VAR_SGR, VAR_NUMBER,
                  VAR_STRING);
  // Query 9
  define_function(state, "reviews_with_word", cmd_reviews_with_word, VAR_TABLE,
                  0, 2, CMD_REVIEWS_WITH_WORD_HELP, VAR_SGR, VAR_STRING);

  define_function(state, "proj", cmd_projection, VAR_TABLE, 0, 2,
                  CMD_PROJECTION_HELP, VAR_TABLE, VAR_ARRAY);
  define_function(state, "filter", cmd_filter, VAR_TABLE, 0, 4, CMD_FILTER_HELP,
                  VAR_TABLE, VAR_STRING, VAR_STRING, VAR_OPERATOR);
  define_function(state, "join", cmd_join, VAR_TABLE, 0, 2, CMD_JOIN_HELP,
                  VAR_TABLE, VAR_TABLE);
  define_function(state, "avg", cmd_avg, VAR_FLOAT, 0, 2, CMD_AVG_HELP,
                  VAR_TABLE, VAR_STRING);
  define_function(state, "max", cmd_max, VAR_TABLE, 0, 2, CMD_MAX_HELP,
                  VAR_TABLE, VAR_STRING);
  define_function(state, "min", cmd_min, VAR_TABLE, 0, 2, CMD_MIN_HELP,
                  VAR_TABLE, VAR_STRING);
  define_function(state, "state", cmd_state, VAR_TABLE, 0, 0, "Return a table with all variables");

  // O readline devolve NULL quando chega ao EOF
  while ((line = readline(BOLD FG_CYAN "> " RESET_ALL))) {
    // Se a linha não for nula...
    if (*line) {
      // adicionar ao histórico
      add_history(line);

      TokenStream toks = split_line(line);
      AST ast = make_empty_ast();
      int consumed = 0;
      SyntaxError e = NULL;
      while (e == NULL &&
             get_token_type(get_token_stream_token(toks, 0)) != TOK_FINISH) {
        e = parse_statement(toks, ast, &consumed);
        toks = get_token_stream_token(toks, consumed);

        if (!e) {
          Variable v = execute(state, ast);

          if (v) {
            if (get_var_type(v) != VAR_VOID)
              print_var(v);

            free_if_possible(v);
          }
        } else {
          print_syntax_error(e);
        }
      }
    }
  }
}
