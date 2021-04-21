#include <stdlib.h>
#include <glib.h>
#include "state.h"

struct variable {
  VariableType type;
  char *name;
  VariableValue value;
};

struct function {
  VariableType return_type;
  const char *help_text;

  int n_args;
  VariableType *args;

  void *function;
};

Variable init_var(VariableType type, VariableValue val, const char *name) {
  Variable var = malloc(sizeof (struct variable));
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

VariableType get_var_type(Variable var) {
  return var->type;
}

VariableValue get_var_value(Variable var) {
  return var->value;
  }

void set_var_name(Variable var, char *name) {
  if (var != NULL)
    var->name = name;
}

STATE init_state() {
  return g_tree_new(g_strcmp0);
}

void create_variable(STATE state, Variable var) {
  g_tree_insert(state, var->name, var);
}

Variable find_variable(STATE state, char *name) {
  return g_tree_lookup(state, name);
}
