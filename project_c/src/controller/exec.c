#include "exec.h"
#include "sgr.h"
#include "model/table.h"
#include "model/state.h"
#include "parsing.h"

Variable execute(STATE state, AST *ast) {
  Variable ret = NULL;
  VariableValue val;

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
      val.string = malloc(strlen(ast->value.string) - 1);
      int i = 0, j = 0;

      for (; ast->value.string[j]; j++) {
        if (ast->value.string[j] != '"') {
          if (ast->value.string[j] == '\\')
            j++;
          val.string[i] = ast->value.string[j];
          i++;
        }
      }

      val.string[i] = '\0';

      ret = init_var(VAR_STRING, val, NULL);

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
    default: break; // TODO!
  }
}
