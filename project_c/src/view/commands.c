#include "commands.h"

#include <glib.h>
#include <stdbool.h>
#include <stdio.h>

#include "Leitura.h"
#include "auxiliary.h"
#include "cli.h"
#include "colors.h"
#include "model/table.h"

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
    GPtrArray* fields = read_to_array(header, delim);
    TABLE table = new_table(fields);
    char* line;
    int lin = 0;
    while ((line = read_line(fp))) {
        lin++;
        new_line(table);
        GPtrArray* line_in_array = read_to_array(line, delim);
        for (int i = 0; i < line_in_array->len; i++) {
            char* test = g_ptr_array_index(line_in_array, i);
            add_to_last_line(table, test);
        }
    }
    return table;
}
void to_csv(TABLE table, char* filename, char* delim) {
    FILE* fp = fopen(filename, "w");
    fprintf_table(fp, table, delim, delim);
}
// to change
ssize_t whereis_field(TABLE table, char* field_name) {
    int i;
    GPtrArray* field_names = get_field_names(table);
    for (i = 0; i < field_names->len; i++) {
        if (!strcmp(field_names->pdata[i], field_name)) {
            return i;
        }
    }
    return -1;
}

bool matches_by_operator(int the_value, int current_value, OPERATOR op) {
    int res = current_value - the_value;
    return res == (op * res);
}

TABLE filter(TABLE table, char* field_name, char* value, OPERATOR op) {
    GPtrArray* fields = g_ptr_array_sized_new(1);
    g_ptr_array_add(fields, field_name);
    TABLE table_two = new_table(fields);
    ssize_t col_index = whereis_field(table, field_name);
    if (col_index != -1) {
        printf("No such field in this table\n");
        free_table(table_two);
        return NULL;
    }
    size_t number_lines = get_number_lines_table(table);
    for (int i = 0; i < number_lines; i++) {
        char* elem = table_index(table, i, col_index);
        if (matches_by_operator(atoi(value), atoi(elem), op)) {
            new_line(table_two);
            add_to_last_line(table_two, elem);
        }
    }
    return table_two;
}
void projection(TABLE table, size_t col, ...) {
    // TODO
}

char* indexation(TABLE table, char* line, char* col) {
    return table_index(table, atoi(line), atoi(col));
}

// Regista todos os comandos
void register_commands(Commands commands) {
    insert_command(commands, make_command(":h", "Get help", cmd_help, 1, NULL));
    insert_command(
        commands, make_command(":help", "Get help", cmd_help, 1, NULL));
    insert_command(commands, make_command(":q", "Quit", cmd_quit, 0, NULL));
    insert_command(commands, make_command(":quit", "Quit", cmd_quit, 0, NULL));
    insert_command(
        commands, make_command("print", "Print", cmd_print, 1, NULL));
}
