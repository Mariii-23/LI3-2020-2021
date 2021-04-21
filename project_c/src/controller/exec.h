#ifndef EXEC_H
#define EXEC_H

#include "parsing.h"
#include "model/state.h"
#include <glib.h>

Variable execute(STATE state, AST *ast);

void free_var(Variable var);

void print_var(Variable var);

#endif
