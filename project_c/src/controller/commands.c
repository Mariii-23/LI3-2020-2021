#include "commands.h"

#include <stdbool.h>
#include <string.h>

#include "model/leitura.h"
#include "model/table.h"
#include "view/colors.h"
#include <gmodule.h>

void cmd_quit(GArray *args) {
  printf("Goodbye!\n");
  exit(0);
}

void cmd_help(GArray *args) {
  printf(FG_BLUE UNDERLINED "Help for " BOLD "%s" RESET_ALL "\n",
         g_array_index(args, char *, 1));
}

void cmd_print(GArray *args) {
  printf(":%s:\n", g_array_index(args, char *, 1));
}

TABLE from_csv(char *filename, char *delim) {
  FILE *fp = fopen(filename, "r");
  if (!fp) {
    printf("Error reading file %s\n", filename);
    return NULL;
  }
  char *header = read_line(fp);
  GPtrArray *fields = read_to_ptr_array(header, delim);
  free(header);
  size_t n_fields = fields->len;
  // it free ptr_array
  TABLE table = new_table_ptr_array(fields);
  char *line;
  while ((line = read_line(fp))) {
    char **line_in_array = read_to_array(line, delim, n_fields);
    free(line);
    if (!line_in_array) {
      // ignorar linhas invalidas
      continue;
    }
    for (int i = 0; i < n_fields; i++) {
      char *field = line_in_array[i];
      add_field(table, field);
      free(field);
    }
  }
  return table;
}
void to_csv(TABLE table, char *filename, char *delim) {
  FILE *fp = fopen(filename, "w");
  if (!fp) {
    printf("Error opening file %s\n", filename);
    return;
  }
  fprintf_table(fp, table, delim, delim);
}

bool matches_by_operator(char *the_value, char *current_value, OPERATOR op) {
  int res = strcmp(the_value, current_value);
  return !res ? (op == EQ) : (res / abs(res)) == op;
}

// to change
ssize_t whereis_field(TABLE table, char *field_name) {
  int j;
  for (j = 0; j < get_number_fields_table(table); j++) {
    if (!strcmp(table_index(table, 0, j), field_name)) {
      return j;
    }
  }
  return -1;
}

TABLE filter(TABLE table, char *field_name, char *value, OPERATOR op) {
  size_t number_fields = get_number_fields_table(table);
  GPtrArray *fields = g_ptr_array_sized_new(number_fields);
  ssize_t col_index = -1;
  for (int i = 0; i < number_fields; i++) {
    char *curr_field = field_index(table, i);
    g_ptr_array_add(fields, curr_field);
    if (col_index == -1 && !strcmp(field_name, curr_field))
      col_index = i;
  }

  if (col_index == -1) {
    printf("No such field in this table\n");
    // se o field_name for dinamico tambem tem que se fazer free
    g_ptr_array_free(fields, TRUE);
    // more to free?
    return NULL;
  }
  TABLE table_two = new_table_ptr_array(fields);
  size_t number_lines = get_number_lines_table(table);
  for (int i = 0; i < number_lines; i++) {
    char *elem = table_index(table, i, col_index);
    if (matches_by_operator(elem, value, op)) {
      for (int j = 0; j < number_fields; j++) {
        add_field(table_two, elem);
        elem = table_index(table, i, j);
      }
    }
  }
  return table_two;
}

TABLE projection(TABLE table, GArray *colunas) {
  size_t n_col = colunas->len;
  size_t number_fields = get_number_fields_table(table);
  char **header = malloc(sizeof(char *) * n_col);
  for (int i = 0; i < n_col; i++) {
    // encapsulamento
    header[i] = field_index(table, g_array_index(colunas, size_t, i));
  }
  TABLE table_two = new_table(header, n_col);
  for (int i = 0; i < get_number_lines_table(table); i++) {
    for (int j = 0; j < colunas->len; j++) {
      if (j >= number_fields)
        continue; // ignorar numeros de colunas que nao existem
      add_field(table_two,
                table_index(table, i, g_array_index(colunas, size_t, j)));
    }
  }
  return table_two;
}

