#include "commands.h"

#include <glib.h>
#include <stdbool.h>
#include <stdio.h>

#include "Leitura.h"
#include "auxiliary.h"
#include "model/table.h"
#include "view/colors.h"

typedef enum { LT = -1, EQ, GT } OPERATOR;

void cmd_quit(GArray* args) {
    printf("Goodbye!\n");
    exit(0);
}

void cmd_help(GArray* args) {
    printf(
        FG_BLUE UNDERLINED "Help for " BOLD "%s" RESET_ALL "\n",
        g_array_index(args, char*, 1));
}

void cmd_print(GArray* args) {
    printf(":%s:\n", g_array_index(args, char*, 1));
}

TABLE from_csv(char* filename, char* delim) {
    FILE* fp = fopen(filename, "r");
    char* header = read_line(fp);
    GPtrArray* fields = read_to_ptr_array(header, delim);
    free(header);
    TABLE table = new_table(fields);
    char* line;
    size_t n_fields = fields->len;
    while ((line = read_line(fp))) {
        char** line_in_array = read_to_array(line, delim, n_fields);
        if (!line_in_array) {
            // TODO free
            return NULL;
        }
        for (int i = 0; i < n_fields; i++) {
            add_field(table, line_in_array[i]);
        }
    }
    return table;
}
void to_csv(TABLE table, char* filename, char* delim) {
    FILE* fp = fopen(filename, "w");
    fprintf_table(fp, table, delim, delim);
}

bool matches_by_operator(int the_value, int current_value, OPERATOR op) {
    int res = current_value - the_value;
    return res == (op * res);
}

// to change
ssize_t whereis_field(TABLE table, char* field_name) {
    int j;
    for (j = 0; j < get_number_fields_table(table); j++) {
        if (!strcmp(table_index(table, 0, j), field_name)) {
            return j;
        }
    }
    return -1;
}
TABLE filter(TABLE table, char* field_name, char* value, OPERATOR op) {
    GPtrArray* fields = g_ptr_array_sized_new(1);
    g_ptr_array_add(fields, field_name);
    ssize_t col_index = whereis_field(table, field_name);
    if (col_index != -1) {
        printf("No such field in this table\n");
        // se o field_name for dinamico tambem tem que se fazer free
        g_ptr_array_free(fields, TRUE);
        return NULL;
    }
    TABLE table_two = new_table(fields);
    size_t number_lines = get_number_lines_table(table);
    for (int i = 0; i < number_lines; i++) {
        char* elem = table_index(table, i, col_index);
        if (matches_by_operator(atoi(value), atoi(elem), op)) {
            add_field(table, elem);
        }
    }
    return table_two;
}
TABLE projection(TABLE table, GPtrArray* colunas) {
    TABLE table_two = new_table_without_fields(colunas->len);
    size_t number_fields = get_number_fields_table(table);
    for (int i = 0; i < get_number_lines_table(table); i++) {
        for (int j = 0; j < colunas->len; j++) {
            size_t col = *((size_t*) g_ptr_array_index(colunas, j));
            if (col >= number_fields)
                continue;  // ignorar numeros de colunas que nao existem
            add_field(table_two, table_index(table, i, col));
        }
    }
    return table_two;
}

char* indexation(TABLE table, char* line, char* col) {
    return table_index(table, atoi(line), atoi(col));
}
