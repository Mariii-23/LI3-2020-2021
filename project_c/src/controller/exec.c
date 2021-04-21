#include "exec.h"
#include "sgr.h"
#include "model/table.h"
#include "model/state.h"
#include "parsing.h"

struct function {
  VariableType return_type;
  const char *help_text; // Pode ser NULL

  int n_args;
  VariableType *arg_types;
};

struct variable {
  VariableType type;
  char *name;     // Pode ser null se não tiver nome
  VariableValue value;
};

Variable execute(STATE state, AST *ast) {
  Variable ret = NULL;
  VariableValue val;
  char *str;

  switch (ast->type) {
    case AST_VARIABLE:
      ret = find_variable(state, ast->value.variable);
      break;
    case AST_NUMBER:
      val.number = ast->value.number;
      ret = init_var(VAR_NUMBER, val, NULL);
      break;
    case AST_STRING:
      // Tenho de retirar as aspas
      str = malloc(strlen(ast->value.string) - 1);
      int i = 0, j = 0;
      
      for (; ast->value.string[j]; j++) {
        if (ast->value.string[j] != '"') {
          // TODO
        }
      }

      break;
    case AST_ASSIGNMENT:
      ret = execute(state, ast->value.assignment->value);
      set_var_name(ret, ast->value.assignment->variable);
      create_variable(state, ret);
      break;
    case AST_FUNCTIONCALL:
      // TODO!!!
      break;
  }

  return ret;
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

void print_var(Variable var) {
  // TODO
}
