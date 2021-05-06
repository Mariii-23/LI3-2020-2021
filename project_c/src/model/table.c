#include "model/table.h"

#include <stdio.h>
#include <stdlib.h>

#include "glib.h"
#include "model/auxiliary.h"

struct table {
  size_t number_fields;
  size_t number_footers;
  char **header;    // tem size == number_fields
  char **footer;    // tem size 2*number_footers, name do footer e value
  GPtrArray *lines; // array de strings que será uma especie de matriz
};

/**
  Creates a table with the headers passed as a parameter, inside a GPtrArray.

*/
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
  table->number_footers = 0;
  table->footer = NULL;
  // g_ptr_array_copy(fields, strdup_copy, NULL);
  // free_ptr_array_deep(fields);
  return table;
}
/**
  Creates a table with the headers passed as a parameter, in an array.

*/
TABLE new_table(char **header, size_t number_fields) {
  TABLE table = malloc(sizeof(struct table));
  table->header =
      copy_char_array(header, number_fields); // breaks encapsulamento
  table->lines = g_ptr_array_sized_new(number_fields);
  table->number_fields = number_fields;
  table->number_footers = 0;
  table->footer = NULL;
  return table;
}

/**
  Creates a table without specifying the header names. Only the number of fields
  in the header are provided.

*/

TABLE new_table_without_fields(size_t number_fields) {
  TABLE table = malloc(sizeof(struct table));
  table->header = malloc(sizeof(char *) * number_fields);
  table->lines = g_ptr_array_sized_new(number_fields);
  table->number_fields = number_fields;
  table->number_footers = 0;
  table->footer = NULL;
  return table;
}

/** Adds an element (field) to the table*/
void add_field(TABLE table, char *field) {
  g_ptr_array_add(table->lines, g_strdup(field));
}

/** Adds a footer to the table, with the provided name and value*/
void add_footer(TABLE table, char *footer_name, char *footer_value) {
  char **ft = table->footer;
  table->number_footers += 1;

  if (!ft) {
    ft = malloc(sizeof(char *) * table->number_footers);
  } else {
    ft = realloc(ft, sizeof(char *) * table->number_footers);
  }

  table->footer = ft;

  ft[table->number_footers * 2 - 2] = g_strdup(footer_name);
  ft[table->number_footers * 2 - 1] = g_strdup(footer_value);
}

/** Writes the contents of the table to the specified stream. This function can
 * be used for converting a table to a csv file or to write a table to stdout,
 * mostly for debugging. */
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

/** Returns the value (string) at the provided line and column of the table*/
char *table_index(TABLE table, size_t i, size_t j) {
  // encapsulamento
  return g_strdup(table->lines->pdata[i * table->number_fields + j]);
}

/**Given a field name, it determines which column  it corresponds to. Returns -1
 * if field doesn't exist*/
ssize_t whereis_field(TABLE table, char *field_name) {
  int j;
  for (j = 0; j < table->number_fields; j++) {
    if (!strcmp(table->header[j], field_name)) {
      return j;
    }
  }
  return -1;
}

char *table_index_by_field(TABLE table, char *field_name, size_t line) {
  int j = whereis_field(table, field_name);
  return table_index(table, line, j);
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

/** Retuns header of the table as a GPtrArray*/
GPtrArray *get_header_table(TABLE table) {
  return build_ptr_array(table->header, table->number_fields);
}

/** Retuns footer name given its index*/
char *get_footer_name(TABLE table, size_t i) { return table->footer[i * 2]; }

/** Retuns footer value given its index*/
char *get_footer_value(TABLE table, size_t i) {
  return table->footer[i * 2 + 1];
}

/** Retuns number of footers present in the table*/
size_t get_number_footers_table(TABLE table) { return table->number_footers; }
/**Frees table structure*/

void free_table(TABLE table) {
  free_ptr_array_deep(table->lines);

  for (int i = 0; i < table->number_fields; i++) {
    free(table->header[i]);
  }
  free(table->header);

  for (int i = 0; i < table->number_footers; i++) {
    free(table->footer[i * 2]);
    free(table->footer[i * 2 + 1]);
  }

  free(table->footer);

  free(table);
}
