#ifndef STATE_H
#define STATE_H
#include <glib.h>
#include "sgr.h"
#include "model/table.h"
#include "controller/commands.h"

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

typedef struct variable *Variable;
typedef struct function *FunctionVal;
typedef Variable (*FunctionPtr)(Variable* args);

// STATE é o estado do programa - contem todas as variáveis e os seus
// valores
typedef GTree *STATE;

Variable init_var(VariableType type, VariableValue val, const char *name);
void free_var(Variable var);
void free_if_possible(Variable var);
VariableType get_var_type(Variable var);
VariableValue get_var_value(Variable var);
void set_var_name(Variable var, const char *name);
// Devolve uma variável do tipo void
Variable void_var();

const char *type_name(VariableType type);

STATE init_state();
void free_state(STATE state);

void create_variable(STATE state, Variable var);
Variable find_variable(STATE state, const char *name);

FunctionVal create_function(int n_args, VariableType return_type, FunctionPtr function, const VariableType* args, const char *help);
int get_n_args(FunctionVal func);
VariableType get_arg_type(FunctionVal func, int i);
FunctionPtr get_function(FunctionVal func);

#endif
