#include "state.h"

#include <glib.h>
#include <stdlib.h>

struct variable {
    VariableType type;
    char* name;
    VariableValue value;
};

struct function {
    VariableType return_type;
    const char* help_text;

    int n_args;
    VariableType* args;

    FunctionPtr function;
};

Variable init_var(VariableType type, VariableValue val, const char* name) {
    Variable var = malloc(sizeof(struct variable));
    var->type = type;
    if (name != NULL)
        var->name = g_strdup(name);
    else
        var->name = NULL;
    var->value = val;

    return var;
}

void free_var(Variable var) {
    if (var->name) {
        free(var->name);
    }

    switch (var->type) {
        case VAR_STRING:
            free(var->value.string);
            free(var);
            break;
        case VAR_SGR:
            // alguma cena para fazer free da SGR
            /* free_sgr(var->value.sgr); */
            free(var);
            break;
        case VAR_TABLE:
            // mesma coisa que para a SGR
            /* free_table(var->value.table); */
            free(var);
            break;
        case VAR_FUNCTION:
            free(var->value.function);
            free(var);
            break;
        default:
            free(var);
            break;
    }
}

void free_if_possible(STATE state, Variable var) {
    if (var->name == NULL || find_variable(state, var->name) == NULL) {
        free_var(var);
    }
}

VariableType get_var_type(Variable var) {
    return var->type;
}

VariableValue get_var_value(Variable var) {
    return var->value;
}

void set_var_name(Variable var, char* name) {
    if (var != NULL) var->name = name;
}

Variable void_var() {
    VariableValue val;
    val.number = 0;
    return init_var(VAR_VOID, val, NULL);
}

const char* type_name(VariableType type) {
    switch (type) {
        case VAR_NUMBER:
            return "number";
        case VAR_SGR:
            return "SGR";
        case VAR_TABLE:
            return "table";
        case VAR_STRING:
            return "string";
        case VAR_FUNCTION:
            return "function";
        case VAR_VOID:
            return "void";
        case VAR_ARRAY:
            return "array";
        case VAR_ANY:
            return "any";
    }
    return NULL;
}

STATE init_state() {
    STATE s = g_tree_new((int (*)(const void*, const void*)) g_strcmp0);

    // Vamos criar variáveis globais para os comparators
    VariableValue val;
    val.operator = GT;
    create_variable(s, init_var(VAR_OPERATOR, val, "GT"));
    val.operator = EQ;
    create_variable(s, init_var(VAR_OPERATOR, val, "EQ"));
    val.operator = LT;
    create_variable(s, init_var(VAR_OPERATOR, val, "LT"));

    return s;
}

void create_variable(STATE state, Variable var) {
    g_tree_insert(state, var->name, var);
}

Variable find_variable(STATE state, char* name) {
    return g_tree_lookup(state, name);
}

FunctionVal create_function(
    int n_args,
    VariableType return_type,
    FunctionPtr function,
    const VariableType* args,
    const char* help) {
    FunctionVal ret = malloc(sizeof(struct function));

    ret->return_type = return_type;
    ret->help_text = help;
    ret->args = memcpy(
        malloc(n_args * sizeof(VariableType)),
        args,
        n_args * sizeof(VariableType));
    ret->n_args = n_args;
    ret->function = function;

    return ret;
}

int get_n_args(FunctionVal func) {
    return func->n_args;
}

VariableType get_arg_type(FunctionVal func, int i) {
    return func->args[i];
}

FunctionPtr get_function(FunctionVal func) {
    return func->function;
}
