#include "exec.h"
#include "sgr.h"
#include "parsing.h"

enum variable_type {
  VAR_NUMBER,
  VAR_SGR,
  VAR_TABLE,
  VAR_STRING,
};

struct variable {
  enum variable_type type;
  char *name;     // Pode ser null se não tiver nome
  union {
    int number;
    SGR *sgr;
    TABLE *table;
    char *string;
  } value;
};

Variable *execute(AST *ast) {
  Variable *ret = NULL;

  switch (ast->type) {
    case AST_VARIABLE:
      break;
    case AST_NUMBER:
      ret = malloc(sizeof (Variable));
      ret->type = VAR_NUMBER;
      ret->name = NULL;
      ret->value.number = ast->value.number;
      break;
    default: break;
  }

  return ret;
}

void free_var(Variable *var) {
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
      free(var);
      break;
    case VAR_TABLE:
      // mesma coisa que para a SGR
      free(var);
      break;
    default:
      free(var);
      break;
  }
}

void print_var(Variable *var) {
  // TODO
}
