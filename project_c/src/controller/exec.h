#ifndef EXEC_H
#define EXEC_H

#include "parsing.h"

typedef struct variable Variable;

Variable *execute(AST *ast);

void free_var(Variable *var);

void print_var(Variable *var);

#endif
