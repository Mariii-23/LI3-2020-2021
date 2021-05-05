#include "controller/commands.h"

#include <ctype.h>
#include <stdbool.h>
#include <string.h>

#include "model/auxiliary.h"
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

bool matches_by_operator(char *the_value, char *current_value, OPERATOR op,
                         bool is_number) {

  if (!current_value || !the_value)
    return false;
  int res;
  if (is_number) {
    res = atoi(the_value) - atoi(current_value);

  } else {
    res = strcmp(the_value, current_value);
  }
  return !res ? (op == EQ) : (res / abs(res)) == op;
}

TABLE filter(TABLE table, char *field_name, char *value, OPERATOR op) {
  bool isnumber = false;
  size_t number_fields = get_number_fields_table(table);
  GPtrArray *fields = g_ptr_array_sized_new(number_fields);
  ssize_t col_index = -1;
  // build header
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
  char *first_value = table_index(table, 0, col_index);
  if (is_number(value) && is_number(first_value)) {
    isnumber = true;
  }
  free(first_value);
  TABLE table_two = new_table_ptr_array(fields);
  size_t number_lines = get_number_lines_table(table);
  for (int i = 0; i < number_lines; i++) {
    char *elem = table_index(table, i, col_index);
    if (matches_by_operator(elem, value, op, isnumber)) {
      free(elem);
      for (int j = 0; j < number_fields; j++) {
        elem = table_index(table, i, j);
        add_field(table_two, elem);
        free(elem);
      }
    }
  }
  return table_two;
}

TABLE projection(TABLE table, GArray *colunas) {
  // se der valor negativo colunas?
  size_t n_col = colunas->len;
  size_t number_fields = get_number_fields_table(table);
  char **header = malloc(sizeof(char *) * n_col);
  int a = 0;
  for (int i = 0; a < n_col; i++) {
    // encapsulamento
    int coluna_to_display = g_array_index(colunas, size_t, a);
    if (coluna_to_display < number_fields) {
      header[a++] = field_index(table, coluna_to_display);
    } else {
      g_array_remove_index(colunas, a);
      n_col--;
    }
  }
  TABLE table_two = new_table(header, colunas->len);
  for (int i = 0; i < get_number_lines_table(table); i++) {
    for (int j = 0; j < colunas->len; j++) {
      size_t col = g_array_index(colunas, size_t, j);
      if (col >= number_fields)
        continue; // ignorar numeros de colunas que nao existem
      char *elem = table_index(table, i, col);
      add_field(table_two, elem);
      free(elem);
    }
  }
  return table_two;
}

// join two tables with same fields
TABLE join(TABLE table_x, TABLE table_y) {
  if ((!table_x && table_y) || (!table_y && table_x))
    return NULL;
  if (!table_y && !table_x)
    return NULL;
  GPtrArray *table_x_fields = get_header_table(table_x);
  GPtrArray *table_y_fields = get_header_table(table_y);
  size_t fields_x = get_number_fields_table(table_x);
  int i;
  for (i = 0; i < fields_x; i++) {
    if (strcmp(g_ptr_array_index(table_x_fields, i),
               g_ptr_array_index(table_y_fields, i)))
      break;
  }
  TABLE nova;
  if (i == fields_x) {
    nova = new_table_ptr_array(table_x_fields);
    for (int i = 0; i < get_number_lines_table(table_x); i++) {
      for (int j = 0; j < fields_x; j++) {
        char *c = table_index(table_x, i, j);
        add_field(nova, c);
        free(c);
      }
    }
    for (int i = 0; i < get_number_lines_table(table_y); i++) {
      for (int j = 0; j < fields_x; j++) {
        char *c = table_index(table_y, i, j);
        add_field(nova, c);
        free(c);
      }
    }
  } else {
    nova = NULL;
  }
  // free_ptr_array_deep(table_x_fields);
  // free_ptr_array_deep(table_y_fields);
  return nova;
}
static char *max_min(TABLE table, char *field_name,
                     float (*cmp)(float, float)) {
  ssize_t column = whereis_field(table, field_name);
  if (column == -1) {
    printf("Field doesn't exist\n");
    return NULL;
  }
  char *first_value = table_index(table, 0, column);
  float max_min = atof(first_value);
  size_t number_lines = get_number_lines_table(table);
  if (!is_number(first_value) || number_lines <= 0) {
    printf("Please provide a colum with numbers\n");
    free(first_value);
    return NULL;
  }
  free(first_value);
  for (int i = 0; i < number_lines; i++) {
    char *curr = table_index(table, i, column);
    float curr_float = atof(curr);
    max_min = cmp(curr_float, max_min);
    free(curr);
  }
  return g_strdup_printf("%.2f", max_min);
}
char *max_table(TABLE table, char *field_name) {
  return max_min(table, field_name, max_float);
}

char *min_table(TABLE table, char *field_name) {
  return max_min(table, field_name, min_float);
}

char *avg(TABLE table, char *field_name) {
  float sum = 0;
  ssize_t column = whereis_field(table, field_name);
  if (column == -1) {
    printf("Field doesn't exist\n");
    return NULL;
  }
  char *first_value = table_index(table, 0, column);
  size_t number_lines = get_number_lines_table(table);
  if (!is_number(first_value) || number_lines <= 0) {
    printf("Please provide a colum with numbers\n");
    free(first_value);
    return NULL;
  }
  free(first_value);
  for (int i = 0; i < number_lines; i++) {
    char *curr = table_index(table, i, column);
    sum += atof(curr);
    free(curr);
  }
  float avg = sum / number_lines;
  return g_strdup_printf("%.2f", avg);
}
