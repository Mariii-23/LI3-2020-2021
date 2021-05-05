#include "model/ast.h"

#include <stdlib.h>
#include <glib.h>
#include <stdio.h>
#include "view/colors.h"

struct token {
  TokenType type;
  char *text;
  unsigned int position;
};

struct syntax_error {
  char *expected;
  Token *token;
};

struct function_call {
  char *name;
  GPtrArray *args;
};

struct var_assignment {
    char* variable;
    struct ast* value;
};

struct indexed {
    struct ast* expression;
    struct ast* index;
};

struct ast {
  ASTType type;
  union {
    FunctionCall function;
    VarAssignment assignment;
    Indexed index;
    char *variable;
    char *string;
    int number;
    GPtrArray *array;
  } value;
};

const char *identify(const char *string, Token *dest) {
  const char *s;
  int i;

  // Vamos passar à frente qualquer espaço
  for (s = string; *s && *s == ' '; s++);

  dest->position = s - string;

  if (*s == '\0') {
    dest->type = TOK_FINISH;
    dest->text = NULL;
    return NULL;
  } else if (*s == '=') {
    dest->type = TOK_EQUALS;
    dest->text = g_strdup("=");
    return s + 1;
  } else if (*s == ',') {
    dest->type = TOK_COMMA;
    dest->text = g_strdup(",");
    return s + 1;
  } else if (*s == '(') {
    dest->type = TOK_OPAREN;
    dest->text = g_strdup("(");
    return s + 1;
  } else if (*s == ')') {
    dest->type = TOK_CPAREN;
    dest->text = g_strdup(")");
    return s + 1;
  } else if (*s == '{') {
    dest->type = TOK_OBRACKET;
    dest->text = g_strdup("{");
    return s + 1;
  } else if (*s == '}') {
    dest->type = TOK_CBRACKET;
    dest->text = g_strdup("}");
    return s + 1;
  } else if (*s == '[') {
    dest->type = TOK_OSQ;
    dest->text = g_strdup("[");
    return s + 1;
  } else if (*s == ']') {
    dest->type = TOK_CSQ;
    dest->text = g_strdup("]");
    return s + 1;
  } else if (*s == ';') {
    dest->type = TOK_SEMICOLON;
    dest->text = g_strdup(";");
    return s + 1;
  } else if (*s >= '0' && *s <= '9') {
    // Encontrámos um número. Vamos ler até encontrarmos algo diferente
    for (i = 0; s[i] && s[i] >= '0' && s[i] <= '9'; i++)
      ;
    dest->type = TOK_NUMBER;
    dest->text = g_strndup(s, i);

    return s + i;
  } else if (*s == '"') {
    dest->type = TOK_STRING;

    // Vamos implementar escaping de strings, simplesmente ignorando um \ e
    // adicionando o caracter a seguir
    for (i = 1; s[i] && s[i] != '"'; i++) {
      if (s[i] == '\\')
        i++;
    }

    if (s[i] == '"')
      i++;

    dest->text = g_strndup(s, i);

    return s + i;
  } else {
    dest->type = TOK_NAME;

    // Validação enorme....
    // Com isto emojis são nomes de variáveis válidos, fun fact
    for (i = 0; s[i] && s[i] != '"' && s[i] != ' ' && s[i] != '\t' &&
                s[i] != '\n' && s[i] != '=' && s[i] != '(' && s[i] != ')' &&
                s[i] != '[' && s[i] != ']' && s[i] != '{' && s[i] != '}' &&
                s[i] != ';' && s[i] != ',';
         i++)
      ;

    dest->text = g_strndup(s, i);
    return s + i;
  }
}

Token *token_dup(const Token *t) {
  Token *d = malloc(sizeof(struct token));
  d->type = t->type;
  if (t->text != NULL)
    d->text = g_strdup(t->text);
  else
    d->text = NULL;
  d->position = t->position;

  return d;
}

void free_token(Token *t) {
  if (t->text)
    free(t->text);
  free(t);
}

void set_token_position(Token *t, int pos) {
  t->position = pos;
}

int get_token_position(const Token *t) {
  return t->position;
}

const char *get_token_text(const Token *t) {
  return t->text;
}

TokenType get_token_type(const Token *t) {
  return t->type;
}

TokenStream make_token_stream(int n) {
  return calloc(sizeof(Token), n);
}

TokenStream resize_token_stream(TokenStream t, int n) {
  return realloc(t, sizeof(Token) * n);
}

Token *get_token_stream_token(TokenStream t, int i) {
  return &t[i];
}

void free_token_stream(TokenStream t) {
  for (int i = 0; t[i].type != TOK_FINISH; i++) {
    if (t->text)
      free(t->text);
  }

  free(t);
}

AST make_empty_ast() {
  AST ret = malloc(sizeof(struct ast));
  ret->type = AST_NONE;
  return ret;
}

AST ast_dup(AST ast) {
  AST ret = make_empty_ast();
  ret->type = ast->type;

  switch (ret->type) {
    case AST_FUNCTIONCALL:
      set_ast_function(ret, function_call_dup(ast->value.function));
      break;
    default:
      printf(BOLD "NOT IMPLEMENTED\n" RESET_ALL);
      break;
  }

  return ret;
}

void free_ast(AST ast) {
  switch (ast->type) {
    case AST_FUNCTIONCALL:
      free_function_call(ast->value.function);
      break;
    case AST_ASSIGNMENT:
    case AST_VARIABLE:
    case AST_INDEX:
    case AST_ARRAY:
      printf(BOLD "NOT IMPLEMENTED\n" RESET_ALL);
      break;
    case AST_STRING:
      free(ast->value.string);
      break;
    default:
      break;
  }

  free(ast);
}

ASTType get_ast_type(AST ast) {
  return ast->type;
}

void set_ast_type(AST ast, ASTType type) {
  ast->type = type;
}

const VarAssignment get_ast_assignment(AST ast) {
  return ast->value.assignment;
}

const FunctionCall get_ast_function_call(AST ast) {
  return ast->value.function;
}

const Indexed get_ast_index(AST ast) {
  return ast->value.index;
}

const char *get_ast_variable(AST ast) {
  return ast->value.variable;
}

const char *get_ast_string(AST ast) {
  return ast->value.string;
}

const GPtrArray *get_ast_array(AST ast) {
  return ast->value.array;
}

int get_ast_number(AST ast) {
  return ast->value.number;
}

void set_ast_function(AST ast, FunctionCall call) {
  ast->type = AST_FUNCTIONCALL;
  ast->value.function = call;
}

void set_ast_var_assignment(AST ast, VarAssignment var) {
  ast->type = AST_ASSIGNMENT;
  ast->value.assignment = var;
}

void set_ast_number(AST ast, int n) {
  ast->type = AST_NUMBER;
  ast->value.number = n;
}

void set_ast_variable(AST ast, const char *variable) {
  ast->type = AST_VARIABLE;
  ast->value.variable = g_strdup(variable);
}

void set_ast_string(AST ast, const char *string) {
  ast->type = AST_STRING;
  ast->value.string = g_strdup(string);
}

void set_ast_array(AST ast, GPtrArray *array) {
  ast->type = AST_ARRAY;
  ast->value.array = array;
}

FunctionCall make_function_call(const char *name) {
  FunctionCall ret = malloc(sizeof(struct function_call));

  ret->name = g_strdup(name);
  ret->args = g_ptr_array_new_with_free_func((GDestroyNotify) free_ast);

  return ret;
}

FunctionCall function_call_dup(const FunctionCall f) {
  FunctionCall ret = make_function_call(f->name);
  for (int i = 0; i < f->args->len; i++) {
    function_call_add_arg(ret, g_ptr_array_index(f->args, i));
  }

  return ret;
}

void function_call_add_arg(FunctionCall f, AST arg) {
  g_ptr_array_add(f->args, ast_dup(arg));
}

void free_function_call(FunctionCall f) {
  g_ptr_array_free(f->args, TRUE);
  free(f->name);
  free(f);
}

const char *get_function_name(const FunctionCall f) {
  return f->name;
}

const GPtrArray *get_function_args(const FunctionCall f) {
  return f->args;
}

VarAssignment make_var_assignment(const char *variable) {
  VarAssignment ret = malloc(sizeof(struct var_assignment));
  ret->variable = g_strdup(variable);
  ret->value = NULL;
  return ret;
}

void free_var_assignment(VarAssignment var) {
  free(var->variable);
  if (var->value)
    free_ast(var->value);
}

VarAssignment var_assignment_dup(const VarAssignment v) {
  VarAssignment ret = make_var_assignment(v->variable);
  if (v->value)
    ret->value = ast_dup(v->value);

  return ret;
}

void set_var_assignment_value(VarAssignment v, AST val) {
  v->value = val;
}

const AST get_var_assignment_value(const VarAssignment v) {
  return v->value;
}

const char *get_var_assignment_variable(const VarAssignment v) {
  return v->variable;
}

void index_expression(AST expression, AST index) {
  Indexed indexed = malloc(sizeof(struct indexed));
  indexed->expression = memcpy(malloc(sizeof(struct ast)), expression, sizeof(struct ast));
  indexed->index = index;
  expression->type = AST_INDEX;
  expression->value.index = indexed;
}

void free_indexed(Indexed i) {
  free_ast(i->expression);
  free_ast(i->index);
  free(i);
}

const AST get_indexed_expression(const Indexed i) {
  return i->expression;
}

const AST get_indexed_index(const Indexed i) {
  return i->index;
}

SyntaxError syntax_error(const char *expected, const Token *token) {
  SyntaxError err = malloc(sizeof(struct syntax_error));
  err->expected = g_strdup(expected);
  err->token = token_dup(token);
  return err;
}

void free_syntax_error(SyntaxError err) {
  free(err->expected);
  free(err->token);
  free(err);
}

void print_syntax_error(SyntaxError error) {
  fprintf(stderr,
          BOLD FG_RED "Syntax error" RESET_ALL " on position %d. Expected " BOLD
                      "%s" RESET_ALL ", but found " BOLD "'%s'" RESET_ALL ".\n",
          error->token->position, error->expected, get_token_text(error->token));
}


