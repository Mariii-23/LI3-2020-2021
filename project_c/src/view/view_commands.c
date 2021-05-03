#include "view_commands.h"

#include "controller/commands.h"
#include "controller/exec.h"
#include "model/sgr.h"
#include "model/state.h"
#include "model/table.h"
#include "view/colors.h"

#include "time.h"
static double get_time_taken(struct timespec start, struct timespec end) {
  double time_taken;
  time_taken = (end.tv_sec - start.tv_sec) * 1e9;
  time_taken = (time_taken + (end.tv_nsec - start.tv_nsec)) * 1e-9;
  return time_taken;
}

Variable print(Variable *args) {
  print_var(*args);
  return void_var();
}

Variable quit(Variable *args) {
  exit(0);
  return NULL;
}

Variable show(Variable *args) {
  fprintf_table(stdout, get_var_value(args[0]).table, " | ", " | ");

  return void_var();
}

Variable cmd_from_csv(Variable *args) {
  VariableValue val;
  val.table =
      from_csv(get_var_value(args[0]).string, get_var_value(args[1]).string);
  return init_var(VAR_TABLE, val, NULL);
}

Variable cmd_to_csv(Variable *args) {
  to_csv(get_var_value(args[0]).table, get_var_value(args[1]).string,
         get_var_value(args[2]).string);
  return void_var();
}

// Query 1
Variable cmd_load_sgr(Variable *args) {
  struct timespec start, end;
  clock_gettime(CLOCK_MONOTONIC, &start);

  VariableValue val;
  val.sgr =
      load_sgr(get_var_value(args[0]).string, get_var_value(args[1]).string,
               get_var_value(args[2]).string);

  clock_gettime(CLOCK_MONOTONIC, &end);
  printf("\nTime: %f s\n", get_time_taken(start, end));
  return init_var(VAR_SGR, val, NULL);
}

// Query 2
Variable cmd_businesses_started_by_letter(Variable *args) {
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
Variable cmd_business_info(Variable *args) {
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
Variable cmd_businesses_reviewed(Variable *args) {
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
Variable cmd_businesses_with_stars_and_city(Variable *args) {
  struct timespec start, end;
  clock_gettime(CLOCK_MONOTONIC, &start);

  VariableValue val;
  val.table = businesses_with_stars_and_city(get_var_value(args[0]).sgr,
                                             get_var_value(args[1]).number,
                                             get_var_value(args[2]).string);

  clock_gettime(CLOCK_MONOTONIC, &end);
  printf("\nTime: %f s\n", get_time_taken(start, end));
  return init_var(VAR_TABLE, val, NULL);
}

// Query 6
Variable cmd_top_businesses_by_city(Variable *args) {
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
Variable cmd_international_users(Variable *args) {
  struct timespec start, end;
  clock_gettime(CLOCK_MONOTONIC, &start);

  VariableValue val;
  val.table = international_users(get_var_value(args[0]).sgr);

  clock_gettime(CLOCK_MONOTONIC, &end);
  printf("\nTime: %f s\n", get_time_taken(start, end));
  return init_var(VAR_TABLE, val, NULL);
}

// Query 8
Variable cmd_top_businesses_with_category(Variable *args) {
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
Variable cmd_reviews_with_word(Variable *args) {
  struct timespec start, end;
  clock_gettime(CLOCK_MONOTONIC, &start);

  VariableValue val;
  val.table = reviews_with_word(get_var_value(args[0]).sgr,
                                get_var_value(args[1]).string);

  clock_gettime(CLOCK_MONOTONIC, &end);
  printf("\nTime: %f s\n", get_time_taken(start, end));
  return init_var(VAR_TABLE, val, NULL);
}

Variable cmd_projection(Variable *args) {
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

Variable cmd_filter(Variable *args) {
  VariableValue val;
  val.table =
      filter(get_var_value(args[0]).table, get_var_value(args[1]).string,
             get_var_value(args[2]).string, get_var_value(args[3]).operator);
  return init_var(VAR_TABLE, val, NULL);
}
