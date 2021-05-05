#ifndef AST_H
#define AST_H

#include <glib.h>

// Um elemento pode ser um nome, um igual, uma virgula, um número, parênteses ou
// um ponto e virgula
typedef enum token_type {
    TOK_NAME,       // e.g. x, avg, fromCSV
    TOK_STRING,     // e.g. "business.csv"
    TOK_NUMBER,     // e.g. 0, 15
    TOK_EQUALS,     // =
    TOK_COMMA,      // ,
    TOK_OPAREN,     // (
    TOK_CPAREN,     // )
    TOK_SEMICOLON,  // ;
    TOK_OSQ,        // [
    TOK_CSQ,        // ]
    TOK_OBRACKET,   // {
    TOK_CBRACKET,   // }
    TOK_FINISH      // Não temos mais elementos
} TokenType;

typedef enum ast_type {
    AST_NONE,
    AST_FUNCTIONCALL,
    AST_ASSIGNMENT,
    AST_VARIABLE,
    AST_NUMBER,
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
AST ast_dup(AST ast);
void free_ast(AST ast);
ASTType get_ast_type(AST ast);
void set_ast_type(AST ast, ASTType type);

// AVISO: Para evitar alocações desnecessárias, estas funções passam a gerir o seu segundo argumento, já que são sempre algo criado apenas para a função. A única exceção é set_ast_string e set_ast_variable.
void set_ast_function(AST ast, FunctionCall call);
void set_ast_var_assignment(AST ast, VarAssignment assignment); // TODO
void set_ast_number(AST ast, int n); // TODO
void set_ast_variable(AST ast, const char *variable); // TODO
void set_ast_string(AST ast, const char *string); // TODO
void set_ast_array(AST ast, GPtrArray *array); // TODO

FunctionCall make_function_call(const char *name);
FunctionCall function_call_dup(FunctionCall f);
void function_call_add_arg(FunctionCall f, AST arg);
void free_function_call(FunctionCall f);

VarAssignment make_var_assignment(const char *variable); // TODO
VarAssignment var_assignment_dup(VarAssignment v); // TODO
void set_var_assignment_value(VarAssignment v, AST val); // TODO
void free_var_assignment(VarAssignment var); // TODO

void index_expression(AST expression, AST index);
void free_indexed(Indexed i); // TODO

SyntaxError syntax_error(const char *expected, const Token *token);
void free_syntax_error(SyntaxError e);
void print_syntax_error(SyntaxError e);

#endif
