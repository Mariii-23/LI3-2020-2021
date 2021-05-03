#include "model/table.h"

#include <stdio.h>
#include <stdlib.h>

#include "glib.h"
#include "model/auxiliary.h"

struct table {
  size_t number_fields;
  char **header;    // tem size == number_fields
  char **footer;    // tem size 2 sempre, name do footer e value
  GPtrArray *lines; // array de strings que será uma especie de matriz
};

TABLE new_table_ptr_array(GPtrArray *header) {
  TABLE table = malloc(sizeof(struct table));
  size_t number_fields = header->len;
  table->header = malloc(sizeof(char *) * header->len);
  for (int i = 0; i < header->len; i++) {
    char *field = g_ptr_array_index(header, i);
    table->header[i] = g_strdup(field);
    free(field);
  }
  g_ptr_array_free(header, true);
  table->lines = g_ptr_array_sized_new(number_fields); // breaks encapsulamento
  table->number_fields = number_fields;
  table->footer = NULL;
  // g_ptr_array_copy(fields, strdup_copy, NULL);
  // free_ptr_array_deep(fields);
  return table;
}
char **copy_char_array(char **array, size_t n_fields) {
  char **x = malloc(sizeof(char *) * n_fields);
  for (int i = 0; i < n_fields; i++) {
    x[i] = g_strdup(array[i]);
  }
  return x;
}

TABLE new_table(char **header, size_t number_fields) {
  TABLE table = malloc(sizeof(struct table));
  table->header =
      copy_char_array(header, number_fields); // breaks encapsulamento
  table->lines = g_ptr_array_sized_new(number_fields);
  table->number_fields = number_fields;
  table->footer = NULL;
  return table;
}

TABLE new_table_without_fields(size_t number_fields) {
  TABLE table = malloc(sizeof(struct table));
  table->header = malloc(sizeof(char *) * number_fields);
  table->lines = g_ptr_array_sized_new(number_fields);
  table->number_fields = number_fields;
  table->footer = NULL;
  return table;
}

void add_field(TABLE table, char *field) {
  g_ptr_array_add(table->lines, g_strdup(field));
}

void add_footer(TABLE table, char *footer_name, char *footer_value) {
  char **ft = table->footer;
  if (!ft) {
    ft = malloc(sizeof(char *) * 2);
    table->footer = ft;
  }
  // memleak
  ft[0] = g_strdup(footer_name);
  ft[1] = g_strdup(footer_value);
}
void fprintf_table(FILE *stream, TABLE table, char *delim_header,
                   char *delim_main) {
  if (table) {
    size_t n_fields = table->number_fields;
    for (int i = 0; i < n_fields; i++) {
      char *d = delim_header;
      char *new_line = "";
      if (i == n_fields - 1) {
        d = "";
        new_line = "\n";
      }
      fprintf(stream, "%s%s%s", table->header[i], d, new_line);
    }
    fprint_str_array(stream, table->lines, n_fields, delim_main);
  }
}
char *table_index(TABLE table, size_t i, size_t j) {
  // encapsulamento
  return table->lines->pdata[i * table->number_fields + j];
}
char *field_index(TABLE table, size_t i) { return g_strdup(table->header[i]); }

size_t get_number_lines_table(TABLE table) {
  return table->lines->len / table->number_fields;
}
size_t get_number_fields_table(TABLE table) { return table->number_fields; }

GPtrArray *get_fields_table(TABLE table) {
  size_t number_fields = table->number_fields;
  GPtrArray *fields = g_ptr_array_sized_new(number_fields);
  for (int i = 0; i < number_fields; i++) {
    g_ptr_array_add(fields, g_strdup(g_ptr_array_index(table->lines, i)));
  }
  return fields;
}
GPtrArray *get_header_table(TABLE table) {
  return build_ptr_array(table->header, table->number_fields);
}

void free_table(TABLE table) {
  free_ptr_array_deep(table->lines);

  for (int i = 0; i < table->number_fields; i++) {
    free(table->header[i]);
  }
  free(table->header);
  free(table->footer[0]);
  free(table->footer[1]);
  free(table->footer);
  free(table);
}
