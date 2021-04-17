#include "commands.h"

#include <glib.h>
#include <stdio.h>

#include "Leitura.h"
#include "auxiliary.h"
#include "cli.h"
#include "colors.h"
#include "model/table.h"

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
