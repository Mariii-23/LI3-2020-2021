#ifndef STATE_H
#define STATE_H
#include "controller/commands.h"
#include "model/table.h"
#include "sgr.h"
#include <glib.h>

// Uma variável é qualquer valor no programa - incluindo funções.
typedef enum variable_type {
  VAR_NUMBER,
  VAR_FLOAT,
  VAR_SGR,
  VAR_TABLE,
  VAR_STRING,
  VAR_FUNCTION,
  VAR_VOID,
  VAR_ARRAY,
  VAR_OPERATOR,
  VAR_ANY
} VariableType;

typedef union {
  int number;
  float float_num;
  SGR sgr;
  TABLE table;
  char *string;
  struct function *function;
  GPtrArray *array;
  OPERATOR operator;
} VariableValue;

// STATE é o estado do programa - contem todas as variáveis e os seus
// valores
typedef GTree *STATE;

typedef struct variable *Variable;
typedef struct function *FunctionVal;
typedef Variable (*FunctionPtr)(STATE s, Variable *args);

Variable init_var(VariableType type, VariableValue val, const char *name);
void free_var(Variable var);
void free_if_possible(Variable var);
VariableType get_var_type(Variable var);
VariableValue get_var_value(Variable var);
void set_var_name(Variable var, const char *name);
void set_var_value(Variable var, VariableValue v);
void set_var_type(Variable var, VariableType t);
// Devolve uma variável do tipo void
Variable void_var();

const char *type_name(VariableType type);

STATE init_state();
void free_state(STATE state);

void create_variable(STATE state, Variable var);
Variable find_variable(STATE state, const char *name);

FunctionVal create_function(int n_args, int defaultable,
                            VariableType return_type, FunctionPtr function,
                            const VariableType *args, const char *help);
int get_n_args(FunctionVal func);
int get_defaultable(FunctionVal func);
VariableType get_arg_type(FunctionVal func, int i);
FunctionPtr get_function(FunctionVal func);

// Esta macro serve para definir uma função rapidamente
#define define_function(state, name, handler, ret, defaultable, n_args, help,  \
                        ...)                                                   \
  {                                                                            \
    VariableType f_args[] = {__VA_ARGS__};                                     \
    VariableValue val;                                                         \
    val.function =                                                             \
        create_function(n_args, defaultable, ret, handler, f_args, help);      \
    create_variable(state, init_var(VAR_FUNCTION, val, name));                 \
  }

#endif
