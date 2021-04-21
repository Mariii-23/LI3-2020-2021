#ifndef STATE_H
#define STATE_H
#include <glib.h>
#include "sgr.h"
#include "model/table.h"

// Uma variável é qualquer valor no programa - incluindo funções.
typedef enum variable_type {
  VAR_NUMBER,
  VAR_SGR,
  VAR_TABLE,
  VAR_STRING,
  VAR_FUNCTION
} VariableType;

typedef union {
  int number;
  SGR sgr;
  TABLE table;
  char *string;
  struct function *function;
} VariableValue;

typedef struct variable *Variable;

// STATE é o estado do programa - contem todas as variáveis e os seus
// valores
typedef GTree *STATE;

Variable init_var(VariableType type, VariableValue val, char *name);
void free_var(Variable var);
VariableType get_var_type(Variable var);
VariableValue get_var_value(Variable var);
void set_var_name(Variable var, char *name);

STATE init_state();
void free_state(STATE state);

void create_variable(STATE state, Variable var);
Variable find_variable(STATE state, char *name);

#endif
