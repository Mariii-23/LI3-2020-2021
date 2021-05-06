/**
 * @file ast.h
 * @author Mariana Rodrigues, Matilde Bravo e Pedro Alves
 * @date 4 Maio 2021
 * @brief This Module is responsible to manipulated all information.
 */

#ifndef AST_H
#define AST_H

#include <glib.h>

// Um elemento pode ser um nome, um igual, uma virgula, um número, parênteses ou
// um ponto e virgula
typedef enum token_type {
  TOK_NAME,      // e.g. x, avg, fromCSV
  TOK_STRING,    // e.g. "business.csv"
  TOK_NUMBER,    // e.g. 0, 15
  TOK_FLOAT,     // e.g. 0.3
  TOK_EQUALS,    // =
  TOK_COMMA,     // ,
  TOK_OPAREN,    // (
  TOK_CPAREN,    // )
  TOK_SEMICOLON, // ;
  TOK_OSQ,       // [
  TOK_CSQ,       // ]
  TOK_OBRACKET,  // {
  TOK_CBRACKET,  // }
  TOK_FINISH     // Não temos mais elementos
} TokenType;

typedef enum ast_type {
  AST_NONE,
  AST_FUNCTIONCALL,
  AST_ASSIGNMENT,
  AST_VARIABLE,
  AST_NUMBER,
  AST_FLOAT,
  AST_STRING,
  AST_INDEX,
  AST_ARRAY
} ASTType;

typedef struct token Token;
typedef Token *TokenStream;
typedef struct ast *AST;
typedef struct var_assignment *VarAssignment;
typedef struct indexed *Indexed;
typedef struct syntax_error *SyntaxError;
typedef struct function_call *FunctionCall;

//
// LEXING
//
// Identifica um token numa string, e devolve a string restante.
const char *identify(const char *string, Token *dest);
Token *token_dup(const Token *t);
void free_token(Token *t);
void set_token_position(Token *t, int pos);
int get_token_position(const Token *t);
const char *get_token_text(const Token *t);
TokenType get_token_type(const Token *t);

// Cria uma sequência de n tokens
TokenStream make_token_stream(int n);
TokenStream resize_token_stream(TokenStream t, int n);
Token *get_token_stream_token(TokenStream t, int i);
void free_token_stream(TokenStream t);

//
// AST
AST make_empty_ast();
AST ast_dup(const AST ast);
void free_ast(AST ast);
ASTType get_ast_type(AST ast);
void set_ast_type(AST ast, ASTType type);

const VarAssignment get_ast_assignment(AST ast);
const FunctionCall get_ast_function_call(AST ast);
const Indexed get_ast_index(AST ast);
const char *get_ast_variable(AST ast);
const char *get_ast_string(AST ast);
const GPtrArray *get_ast_array(AST ast);
int get_ast_number(AST ast);
float get_ast_float(AST ast);

// AVISO: Para evitar alocações desnecessárias, estas funções passam a gerir o
// seu segundo argumento, já que são sempre algo criado apenas para a função. A
// única exceção é set_ast_string e set_ast_variable.
void set_ast_function(AST ast, FunctionCall call);
void set_ast_var_assignment(AST ast, VarAssignment assignment);
void set_ast_index(AST ast, Indexed i);
void set_ast_number(AST ast, int n);
void set_ast_float(AST ast, float n);
void set_ast_variable(AST ast, const char *variable);
void set_ast_string(AST ast, const char *string);
void set_ast_array(AST ast, GPtrArray *array);

FunctionCall make_function_call(const char *name);
FunctionCall function_call_dup(const FunctionCall f);
void function_call_add_arg(FunctionCall f, AST arg);
void free_function_call(FunctionCall f);
const char *get_function_name(const FunctionCall f);
const GPtrArray *get_function_args(const FunctionCall f);

VarAssignment make_var_assignment(const char *variable);        // TODO
void free_var_assignment(VarAssignment var);                    // TODO
VarAssignment var_assignment_dup(const VarAssignment v);        // TODO
void set_var_assignment_value(VarAssignment v, AST val);        // TODO
const AST get_var_assignment_value(const VarAssignment v);      // TODO
const char *get_var_assignment_variable(const VarAssignment v); // TODO

Indexed indexed_dup(const Indexed i);
void index_expression(AST expression, AST index);
void free_indexed(Indexed i); // TODO
const AST get_indexed_expression(const Indexed i);
const AST get_indexed_index(const Indexed i);

SyntaxError syntax_error(const char *expected, const Token *token);
void free_syntax_error(SyntaxError e);
void print_syntax_error(SyntaxError e);

#endif
