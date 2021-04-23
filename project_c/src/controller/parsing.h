#ifndef PARSING_H
#define PARSING_H
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

typedef struct token {
    TokenType type;
    char* text;
    unsigned int position;
} Token;

// Com isto podemos converter e.g. data = fromCSV("reviews.csv"); em:
// { TOK_NAME("data"), TOK_EQUALS, TOK_NAME("fromCSV"), TOK_OPAREN,
// TOK_STRING("reviews.csv"), TOK_CPAREN, TOK_SEMICOLON, TOK_FINISH }

Token* split_line(const char* string);
const char* identify(const char* string, Token* dest);

typedef enum ast_type {
    AST_FUNCTIONCALL,
    AST_ASSIGNMENT,
    AST_VARIABLE,
    AST_NUMBER,
    AST_STRING,
    AST_INDEX,
    AST_ARRAY
} ASTType;

typedef struct function_call {
    char* function_name;
    GArray* args;
} FunctionCall;

typedef struct var_assignment {
    char* variable;
    struct ast* value;
} VarAssignment;

typedef struct indexed {
    struct ast* expression;
    struct ast* index;
} Indexed;

typedef struct ast {
    ASTType type;
    union {
        FunctionCall* function;
        VarAssignment* assignment;
        char* variable;
        int number;
        char* string;
        GArray* array;
        Indexed* index;
    } value;
} AST;

typedef struct syntax_error {
    const char* expected;
    const Token* token;
} SyntaxError;

SyntaxError* syntax_error(const char* expected, const Token* token);
void print_error(SyntaxError* error, const char* line);

GArray* parse_line(const char* string);

SyntaxError* parse_function(const Token* tokens, AST* node, int* consumed);
SyntaxError* parse_assignment(const Token* tokens, AST* node, int* consumed);
SyntaxError* parse_expression(const Token* tokens, AST* node, int* consumed);
SyntaxError* parse_statement(const Token* tokens, AST* node, int* consumed);
SyntaxError* parse_array(const Token* tokens, AST* node, int* consumed);
SyntaxError* parse_index(const Token* tokens, AST* node, int* consumed);

const char* token_text(const Token* token);
void print_element(Token* e);

#endif
