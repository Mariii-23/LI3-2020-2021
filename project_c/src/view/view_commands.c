#include "view_commands.h"

#include "controller/commands.h"
#include "controller/exec.h"
#include "model/state.h"
#include "model/table.h"

Variable print(Variable* args) {
    print_var(*args);
    return void_var();
}

Variable quit(Variable* args) {
    exit(0);
    return NULL;
}
Variable show(Variable* args) {
    fprintf_table(stdout, get_var_value(args[0]).table, " | ", " | ");

    return void_var();
}
Variable cmd_from_csv(Variable* args) {
    VariableValue val;
    val.table =
        from_csv(get_var_value(args[0]).string, get_var_value(args[1]).string);
    return init_var(VAR_TABLE, val, NULL);
}

Variable cmd_to_csv(Variable* args) {
    to_csv(
        get_var_value(args[0]).table,
        get_var_value(args[1]).string,
        get_var_value(args[2]).string);
    return void_var();
}
