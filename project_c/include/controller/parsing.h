/**
 * @file parsing.h
 * @author Mariana Rodrigues, Matilde Bravo e Pedro Alves
 * @date 4 Maio 2021
 * @brief This Module is responsible to manipulated all information.
 */

#ifndef PARSING_H
#define PARSING_H
#include "model/ast.h"
#include <glib.h>

// Lê uma linha e devolve uma TokenStream
TokenStream split_line(const char *line);

SyntaxError parse_function(const TokenStream tokens, AST node, int *consumed);
SyntaxError parse_assignment(const TokenStream tokens, AST node, int *consumed);
SyntaxError parse_expression(const TokenStream tokens, AST node, int *consumed);
SyntaxError parse_statement(const TokenStream tokens, AST node, int *consumed);
SyntaxError parse_array(const TokenStream tokens, AST node, int *consumed);
SyntaxError parse_index(const TokenStream tokens, AST node, int *consumed);

#endif
