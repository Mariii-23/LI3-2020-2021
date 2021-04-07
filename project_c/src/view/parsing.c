#include "parsing.h"
#include "colors.h"
#include <stdio.h>
#include <glib.h>

// Verifica se a string é uma referência a uma variável
int is_variable_reference(const char *string) {
  int i = 0;

  // Passa à frente todos os espaços
  for (; string[i] && string[i] == ' '; i++);

  // É um comando
  if (string[i] == ':')
    return 0;

  for (; string[i] && string[i] != ' '; i++) {
    if (string[i] == '(')
      return 0;
  }

  return 1;
}

GArray *split_args(char *string) {
  char is_function = 0;
  GArray *args = g_array_new(FALSE, FALSE, sizeof (char *));
  // 1. retiramos whitespace do inicio da string
  g_strchug(string);

  // 2. Verificamos se é um comando (começa por ':' e não tem parênteses) ou uma função
  if (*string != ':') {
    is_function = 1;

    string = g_strchomp(strtok(string, "("));
  } else {
    string = strtok(string, " ");
  }
  g_array_append_val(args, string);

  if (is_function) {
  }

  return NULL;
}

// Duplica n caracteres de uma string
char *strndup(const char *s, int n) {
  char *copy = malloc(n + 1);
  int i;

  // TODO usar memcpy ou algo do género: memcpy pode ser compilado como uma
  // única instrução, é consideravelmente mais rápido
  for (i = 0; s[i] && i < n; i++) {
    copy[i] = s[i];
  }

  copy[i] = '\0';

  return copy;
}

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
    dest->text = "=";
    return s + 1;
  } else if (*s == ',') {
    dest->type = TOK_COMMA;
    dest->text = ",";
    return s + 1;
  } else if (*s == '(') {
    dest->type = TOK_OPAREN;
    dest->text = "("; 
    return s + 1;
  } else if (*s == ')') {
    dest->type = TOK_CPAREN;
    dest->text = ")";
    return s + 1;
  } else if (*s == ';') {
    dest->type = TOK_SEMICOLON;
    dest->text = ";";
    return s + 1;
  } else if (*s >= '0' && *s <= '9') {
    // Encontrámos um número. Vamos ler até encontrarmos algo diferente
    // TODO isto tem de lidar com decimais...
    for (i = 0; s[i] && s[i] >= '0' && s[i] <= '9'; i++);
    dest->type = TOK_NUMBER;
    dest->text = strndup(s, i);

    return s + i;
  } else if (*s == '"') {
    dest->type = TOK_STRING;
    
    // Vamos implementar escaping de strings, simplesmente ignorando um \ e adicionando o caracter a seguir
    
    for (i = 1; s[i] && s[i] != '"'; i++) {
      if (s[i] == '\\')
        i++;
    }

    if (s[i] == '"')
      i++;

    dest->text = strndup(s, i);

    return s + i;
  } else {
    dest->type = TOK_NAME;

    // Validação enorme....
    // Com isto emojis são nomes de variáveis válidos, fun fact
    for (i = 0; s[i] && s[i] != '"' && s[i] != ' ' && s[i] != '\t' && s[i] != '\n' && s[i] != '=' && s[i] != '(' && s[i] != ')' && s[i] != ';' && s[i] != ','; i++);

    dest->text = strndup(s, i);
    return s + i;
  }
}

Token *split_line(const char *string) {
  const char *cur_line = string;
  // Porquê 6? É o que uma chamada de função básica vai utilizar: nome, dois parênteses, um argumento, ponto e virgula e o final
  Token *line = malloc(sizeof (Token) * 6);
  int size = 6;
  int i = 0;

  while (1) {
    const char *prev = cur_line;
    cur_line = identify(cur_line, &line[i]);
    line[i].position += prev - string;
    if (cur_line == NULL)
      break;
    i++;
    if (i >= size) {
      size *= 2;
      line = realloc(line, size * sizeof (Token));
    }
  }

  return line;
}

// Devolve um syntax error
SyntaxError *syntax_error(const char *expected, const Token *token) {
  SyntaxError *err = malloc(sizeof(SyntaxError));
  err->expected = expected;
  err->token = token;
  return err;
}

void print_error(SyntaxError *error, const char *line) {
  fprintf(stderr, BOLD FG_RED "Syntax error" RESET_ALL " on position %d. Expected " BOLD "%s" RESET_ALL ", but found " BOLD "'%s'" RESET_ALL ".\n", error->token->position, error->expected, token_text(error->token));
}

GArray *parse_line(const char *string) {
  // 1. Criar parsers diferentes, um que lê uma chamada de função
  // (prioridade 1), outro que lê uma variável (prioridade 2), outro
  // que lê um valor (prioridade 3).

  return NULL;
}

// Devolve o token em que deixou de conseguir ler
SyntaxError *parse_function(const Token *tokens, AST *node, int *consumed) {
  int tok = 0;
  FunctionCall *call = malloc(sizeof(FunctionCall));
  
  if (tokens[tok].type == TOK_NAME) {
    call->function_name = tokens[tok].text;
    tok++;
  } else {
    free(call);
    return syntax_error("a function name", &tokens[tok]);
  }

  if (tokens[tok].type != TOK_OPAREN) {
    free(call);
    return syntax_error("'('", &tokens[tok]);
  }

  tok++;

  call->args = g_array_new(FALSE, FALSE, sizeof (AST));
  
  while (tokens[tok].type != TOK_CPAREN) {
    int consumed = 0;
    AST node;
    SyntaxError *e = parse_expression(&tokens[tok], &node, &consumed);

    if (e) {
      g_array_free(call->args, TRUE);
      free(call);
      return e;
    }

    tok += consumed;

    if (tokens[tok].type != TOK_CPAREN && tokens[tok].type != TOK_COMMA) {
      g_array_free(call->args, TRUE);
      free(call);
      return syntax_error("',' or ')'", &tokens[tok]);
    }

    g_array_append_val(call->args, node);
    if (tokens[tok].type == TOK_COMMA)
      tok++;
  }

  tok++;
  *consumed = tok;
  node->type = AST_FUNCTIONCALL;
  node->value.function = call;

  return NULL;
}

SyntaxError *parse_expression(const Token *tokens, AST *node, int *consumed) {
  if (tokens->type == TOK_NUMBER) {
    node->type = AST_NUMBER;
    node->value.number = atoi(tokens->text);
    *consumed = 1;
    return NULL;
  }

  return syntax_error("a number", tokens);
}

const char *token_text(const Token *token) {
  switch (token->type) {
    case TOK_NAME:
    case TOK_STRING:
    case TOK_NUMBER:
      return token->text;
    case TOK_EQUALS:
      return "=";
    case TOK_COMMA:
      return ",";
    case TOK_OPAREN:
      return "(";
    case TOK_CPAREN:
      return ")";
    case TOK_SEMICOLON:
      return ";";
    default:
      return "";
  }
}

void print_element(Token *e) {
  switch (e->type) {
    case TOK_NAME:
      printf("NAME(%s)", e->text);
      break;
    case TOK_STRING:
      printf("STRING(%s)", e->text);
      break;
    case TOK_NUMBER:
      printf("NUMBER(%s)", e->text);
      break;
    case TOK_EQUALS:
      printf("=");
      break;
    case TOK_COMMA:
      printf(",");
      break;
    case TOK_OPAREN:
      printf("(");
      break;
    case TOK_CPAREN:
      printf(")");
      break;
    case TOK_SEMICOLON:
      printf(";");
      break;
    case TOK_FINISH:
      printf("FINISH");
      break;
  }
}
