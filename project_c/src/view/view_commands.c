/**
 * @file view_commands.c
 * @author Mariana Rodrigues, Matilde Bravo e Pedro Alves
 * @date 4 Maio 2021
 * @brief Contém definições de comandos para o interpretador
 */

// Necessário para que clock_gettime exista
#define _POSIX_C_SOURCE 199309L

#include "view/view_commands.h"

#include "controller/commands.h"
#include "controller/exec.h"
#include "model/sgr.h"
#include "model/state.h"
#include "model/table.h"
#include "view/colors.h"
#include "view/paginacao.h"

#include <time.h>

static double get_time_taken(struct timespec start, struct timespec end) {
  double time_taken;
  time_taken = (end.tv_sec - start.tv_sec) * 1e9;
  time_taken = (time_taken + (end.tv_nsec - start.tv_nsec)) * 1e-9;
  return time_taken;
}

Variable print(STATE s, Variable *args) {
  print_var(*args);
  return void_var();
}

Variable quit(STATE s, Variable *args) {
  exit(0);
  return NULL;
}

Variable show(STATE s, Variable *args) {
  /* fprintf_table(stdout, get_var_value(args[0]).table, " | ", " | "); */
  show_table(get_var_value(args[0]).table);

  return void_var();
}

Variable help(STATE s, Variable *args) {
  if (get_function_help(get_var_value(args[0]).function)) {
    printf("%s", get_function_help(get_var_value(args[0]).function));
  } else {
    fprintf(stderr, BOLD FG_RED "Error: " RESET_ALL "no help available.\n");
  }
  return void_var();
}

Variable cmd_from_csv(STATE s, Variable *args) {
  VariableValue val;
  val.table =
      from_csv(get_var_value(args[0]).string, get_var_value(args[1]).string);
  return init_var(VAR_TABLE, val, NULL);
}

Variable cmd_to_csv(STATE s, Variable *args) {
  to_csv(get_var_value(args[0]).table, get_var_value(args[1]).string,
         get_var_value(args[2]).string);
  return void_var();
}

// Query 1
Variable cmd_load_sgr(STATE s, Variable *args) {
  struct timespec start, end;
  clock_gettime(CLOCK_MONOTONIC, &start);

  char *arg1, *arg2, *arg3;

  if (get_var_type(args[0]) == VAR_VOID) {
    Variable v = find_variable(s, "USERS_CSV");
    if (!v) {
      arg1 = "users.csv";
    } else {
      arg1 = get_var_value(v).string;
    }
  } else {
    arg1 = get_var_value(args[0]).string;
  }

  if (get_var_type(args[1]) == VAR_VOID) {
    Variable v = find_variable(s, "BUSINESSES_CSV");
    if (!v) {
      arg2 = "businesses.csv";
    } else {
      arg2 = get_var_value(v).string;
    }
  } else {
    arg2 = get_var_value(args[1]).string;
  }

  if (get_var_type(args[2]) == VAR_VOID) {
    Variable v = find_variable(s, "REVIEWS_CSV");
    if (!v) {
      arg3 = "reviews.csv";
    } else {
      arg3 = get_var_value(v).string;
    }
  } else {
    arg3 = get_var_value(args[2]).string;
  }

  VariableValue val;
  val.sgr = load_sgr(arg1, arg2, arg3);

  clock_gettime(CLOCK_MONOTONIC, &end);
  printf("\nTime: %f s\n", get_time_taken(start, end));
  return init_var(VAR_SGR, val, NULL);
}

// Query 2
Variable cmd_businesses_started_by_letter(STATE s, Variable *args) {
  struct timespec start, end;
  clock_gettime(CLOCK_MONOTONIC, &start);

  VariableValue val;
  val.table = businesses_started_by_letter(get_var_value(args[0]).sgr,
                                           // deveria ser char
                                           get_var_value(args[1]).string[0]);

  clock_gettime(CLOCK_MONOTONIC, &end);
  printf("\nTime: %f s\n", get_time_taken(start, end));
  return init_var(VAR_TABLE, val, NULL);
}

// Query 3
Variable cmd_business_info(STATE s, Variable *args) {
  struct timespec start, end;
  clock_gettime(CLOCK_MONOTONIC, &start);

  VariableValue val;
  val.table =
      business_info(get_var_value(args[0]).sgr, get_var_value(args[1]).string);

  clock_gettime(CLOCK_MONOTONIC, &end);
  printf("\nTime: %f s\n", get_time_taken(start, end));
  return init_var(VAR_TABLE, val, NULL);
}

// Query 4
Variable cmd_businesses_reviewed(STATE s, Variable *args) {
  struct timespec start, end;
  clock_gettime(CLOCK_MONOTONIC, &start);

  VariableValue val;
  val.table = businesses_reviewed(get_var_value(args[0]).sgr,
                                  get_var_value(args[1]).string);

  clock_gettime(CLOCK_MONOTONIC, &end);
  printf("\nTime: %f s\n", get_time_taken(start, end));
  return init_var(VAR_TABLE, val, NULL);
}

// Query 5
Variable cmd_businesses_with_stars_and_city(STATE s, Variable *args) {
  struct timespec start, end;
  clock_gettime(CLOCK_MONOTONIC, &start);

  VariableValue val;
  val.table = businesses_with_stars_and_city(get_var_value(args[0]).sgr,
                                             get_var_value(args[1]).float_num,
                                             get_var_value(args[2]).string);

  clock_gettime(CLOCK_MONOTONIC, &end);
  printf("\nTime: %f s\n", get_time_taken(start, end));
  return init_var(VAR_TABLE, val, NULL);
}

// Query 6
Variable cmd_top_businesses_by_city(STATE s, Variable *args) {
  struct timespec start, end;
  clock_gettime(CLOCK_MONOTONIC, &start);

  VariableValue val;
  val.table = top_businesses_by_city(get_var_value(args[0]).sgr,
                                     get_var_value(args[1]).number);

  clock_gettime(CLOCK_MONOTONIC, &end);
  printf("\nTime: %f s\n", get_time_taken(start, end));
  return init_var(VAR_TABLE, val, NULL);
}

// Query 7
Variable cmd_international_users(STATE s, Variable *args) {
  struct timespec start, end;
  clock_gettime(CLOCK_MONOTONIC, &start);

  VariableValue val;
  val.table = international_users(get_var_value(args[0]).sgr);

  clock_gettime(CLOCK_MONOTONIC, &end);
  printf("\nTime: %f s\n", get_time_taken(start, end));
  return init_var(VAR_TABLE, val, NULL);
}

// Query 8
Variable cmd_top_businesses_with_category(STATE s, Variable *args) {
  struct timespec start, end;
  clock_gettime(CLOCK_MONOTONIC, &start);

  VariableValue val;
  val.table = top_businesses_with_category(get_var_value(args[0]).sgr,
                                           get_var_value(args[1]).number,
                                           get_var_value(args[2]).string);

  clock_gettime(CLOCK_MONOTONIC, &end);
  printf("\nTime: %f s\n", get_time_taken(start, end));
  return init_var(VAR_TABLE, val, NULL);
}

// Query 9
Variable cmd_reviews_with_word(STATE s, Variable *args) {
  struct timespec start, end;
  clock_gettime(CLOCK_MONOTONIC, &start);

  VariableValue val;
  val.table = reviews_with_word(get_var_value(args[0]).sgr,
                                get_var_value(args[1]).string);

  clock_gettime(CLOCK_MONOTONIC, &end);
  printf("\nTime: %f s\n", get_time_taken(start, end));
  return init_var(VAR_TABLE, val, NULL);
}

Variable cmd_projection(STATE s, Variable *args) {
  VariableValue val;
  GPtrArray *col_array = get_var_value(args[1]).array;
  GArray *columns =
      g_array_sized_new(FALSE, FALSE, sizeof(size_t), col_array->len);

  for (int i = 0; i < col_array->len; i++) {
    if (get_var_type(g_ptr_array_index(col_array, i)) != VAR_NUMBER) {
      fprintf(stderr, BOLD FG_RED "Error: " RESET_ALL
                                  "expected an array of numbers.\n");
      g_array_free(columns, TRUE);
      return NULL;
    }

    size_t col = get_var_value(g_ptr_array_index(col_array, i)).number;
    g_array_append_val(columns, col);
  }

  val.table = projection(get_var_value(args[0]).table, columns);
  return init_var(VAR_TABLE, val, NULL);
}

Variable cmd_filter(STATE s, Variable *args) {
  VariableValue val;
  val.table =
      filter(get_var_value(args[0]).table, get_var_value(args[1]).string,
             get_var_value(args[2]).string, get_var_value(args[3]).operator);
  return init_var(VAR_TABLE, val, NULL);
}
Variable cmd_join(STATE s, Variable *args) {
  VariableValue val;
  val.table = join(get_var_value(args[0]).table, get_var_value(args[1]).table);
  return init_var(VAR_TABLE, val, NULL);
}

Variable cmd_avg(STATE s, Variable *args) {
  VariableValue val;
  val.float_num =
      avg(get_var_value(args[0]).table, get_var_value(args[1]).string);
  return init_var(VAR_FLOAT, val, NULL);
}

Variable cmd_max(STATE s, Variable *args) {
  VariableValue val;
  val.table =
      max_table(get_var_value(args[0]).table, get_var_value(args[1]).string);
  return init_var(VAR_TABLE, val, NULL);
}

Variable cmd_min(STATE s, Variable *args) {
  VariableValue val;
  val.table =
      min_table(get_var_value(args[0]).table, get_var_value(args[1]).string);
  return init_var(VAR_TABLE, val, NULL);
}

Variable cmd_state(STATE s, Variable *args) {
  VariableValue val;
  val.table = state_table(s);

  return init_var(VAR_TABLE, val, NULL);
}
