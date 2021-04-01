#include "parsing.h"
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

Element *split_line(const char *string) {
  return NULL;
}

// Duplica n caracteres de uma string
char *strndup(const char *s, int n) {
  char *copy = malloc(n + 1);
  int i;

  for (i = 0; s[i] && i < n; i++) {
    copy[i] = s[i];
  }

  copy[i] = '\0';

  return copy;
}

const char *identify(const char *string, Element *dest) {
  const char *s;
  int i;

  // Vamos passar à frente qualquer espaço
  for (s = string; *s && *s == ' '; s++);

  dest->position = s - string;

  if (*s == '\0') {
    dest->type = LE_FINISH;
    dest->text = NULL;
    return NULL;
  } else if (*s == '=') {
    dest->type = LE_EQUALS;
    dest->text = "=";
    return s + 1;
  } else if (*s == ',') {
    dest->type = LE_COMMA;
    dest->text = ",";
    return s + 1;
  } else if (*s == '(') {
    dest->type = LE_OPAREN;
    dest->text = "("; 
    return s + 1;
  } else if (*s == ')') {
    dest->type = LE_CPAREN;
    dest->text = ")";
    return s + 1;
  } else if (*s == ';') {
    dest->type = LE_SEMICOLON;
    dest->text = ";";
    return s + 1;
  } else if (*s >= '0' && *s <= '9') {
    // Encontrámos um número. Vamos ler até encontrarmos algo diferente
    // TODO isto tem de lidar com decimais...
    for (i = 0; s[i] && s[i] >= '0' && s[i] <= '9'; i++);
    dest->type = LE_NUMBER;
    dest->text = strndup(s, i);

    return s + i;
  } else if (*s == '"') {
    dest->type = LE_STRING;
    
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
    dest->type = LE_NAME;

    // Validação enorme....
    // Com isto emojis são nomes de variáveis válidos, fun fact
    for (i = 0; s[i] && s[i] != '"' && s[i] != ' ' && s[i] != '\t' && s[i] != '\n' && s[i] != '=' && s[i] != '(' && s[i] != ')' && s[i] != ';' && s[i] != ','; i++);

    dest->text = strndup(s, i);
    return s + i;
  }
}

void print_element(Element *e) {
  switch (e->type) {
    case LE_NAME:
      printf("NAME(%s)", e->text);
      break;
    case LE_STRING:
      printf("STRING(%s)", e->text);
      break;
    case LE_NUMBER:
      printf("NUMBER(%s)", e->text);
      break;
    case LE_EQUALS:
      printf("=");
      break;
    case LE_COMMA:
      printf(",");
      break;
    case LE_OPAREN:
      printf("(");
      break;
    case LE_CPAREN:
      printf(")");
      break;
    case LE_SEMICOLON:
      printf(";");
      break;
    case LE_FINISH:
      printf("FINISH");
      break;
  }
}
