/**
 * @file exec.h
 * @author Mariana Rodrigues, Matilde Bravo e Pedro Alves
 * @date 4 Maio 2021
 * @brief This Module is responsible to manipulated all information.
 */

#ifndef EXEC_H
#define EXEC_H

#include "model/state.h"
#include "parsing.h"
#include <glib.h>

Variable execute(STATE state, AST ast);

void free_var(Variable var);

void print_var(Variable var);

#endif
