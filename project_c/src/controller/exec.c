#include "exec.h"

#include "../model/sgr.h"
#include "model/state.h"
#include "model/table.h"
#include "parsing.h"
#include "view/colors.h"

Variable execute(STATE state, AST* ast) {
    Variable ret = NULL;
    VariableValue val;

    switch (ast->type) {
        case AST_VARIABLE:
            ret = find_variable(state, ast->value.variable);
            if (!ret)
                fprintf(
                    stderr,
                    BOLD FG_RED "Error: " RESET_ALL
                                "variable %s does not exist.\n",
                    ast->value.variable);
            break;
        case AST_NUMBER:
            val.number = ast->value.number;
            ret = init_var(VAR_NUMBER, val, NULL);
            break;
        case AST_STRING:
            // Tenho de retirar as aspas
            val.string = malloc(strlen(ast->value.string) - 1);
            int i = 0, j = 0;

            for (; ast->value.string[j]; j++) {
                if (ast->value.string[j] != '"') {
                    if (ast->value.string[j] == '\\') j++;
                    val.string[i] = ast->value.string[j];
                    i++;
                }
            }

            val.string[i] = '\0';

            ret = init_var(VAR_STRING, val, NULL);

            break;
        case AST_ASSIGNMENT:
            // Bug possivel com garbage collection, provavelmente o melhor é ter
            // "names" em vez de name, com um array. Ou então simplesmente
            // fazemos reference counting, algo assim simples.
            ret = execute(state, ast->value.assignment->value);
            if (ret) {
                set_var_name(ret, ast->value.assignment->variable);
                create_variable(state, ret);
            }
            break;
        case AST_FUNCTIONCALL: {
            // Dentro de um block para podermos definir variáveis

            ret = find_variable(state, ast->value.function->function_name);
            if (!ret) {
                fprintf(
                    stderr,
                    BOLD FG_RED "Error: " RESET_ALL
                                "function %s does not exist.\n",
                    ast->value.function->function_name);
                return NULL;
            }

            FunctionVal function = get_var_value(ret).function;
            GArray* args_ast = ast->value.function->args;
            int n_args = get_n_args(function);

            if (args_ast->len != n_args) {
                fprintf(
                    stderr,
                    BOLD FG_RED "Error: " RESET_ALL
                                "wrong number of arguments, expected" BOLD
                                " %d" RESET_ALL ", got " BOLD "%d" RESET_ALL
                                ".\n",
                    n_args,
                    args_ast->len);
                return NULL;
            }

            Variable* args = malloc(sizeof(Variable) * n_args);
            for (int i = 0; i < n_args; i++) {
                AST arg = g_array_index(args_ast, AST, i);
                args[i] = execute(state, &arg);
                int error = args[i] == NULL;

                if (!error && get_arg_type(function, i) != VAR_ANY) {
                    if (get_arg_type(function, i) != get_var_type(args[i])) {
                        fprintf(
                            stderr,
                            BOLD FG_RED "Error on argument " FG_YELLOW
                                        "%d" FG_RED ": " RESET_ALL
                                        "expected type " BOLD "%s" RESET_ALL
                                        ", got " BOLD "%s" RESET_ALL ".\n",
                            i + 1,
                            type_name(get_arg_type(function, i)),
                            type_name(get_var_type(args[i])));
                        error = 1;
                    }
                }

                if (error) {
                    for (int j = 0; j <= i; j++) {
                        if (args[i]) free_if_possible(state, args[i]);
                    }
                    free(args);
                    return NULL;
                }
            }

            ret = get_function(function)(args);
        } break;
    }

    return ret;
}

void print_var(Variable var) {
    // TODO
    switch (get_var_type(var)) {
        case VAR_STRING:
            printf("String: %s\n", get_var_value(var).string);
            break;
        case VAR_NUMBER:
            printf("Number: %d\n", get_var_value(var).number);
            break;
        case VAR_FUNCTION:
            printf("Function\n");
            break;
        case VAR_SGR:
            printf("SGR\n");
            break;  // TODO!
        case VAR_TABLE:
            printf("Table\n");
            break;
        case VAR_VOID:
            printf("Void\n");
            break;
        case VAR_ANY:
            printf("Unknown type\n");
            break;
    }
}
