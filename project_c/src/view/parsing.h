#ifndef PARSING_H
#define PARSING_H
#include <glib.h>

int is_variable_reference(const char *string);
GArray *split_args(char *string);

// Um elemento pode ser um nome, um igual, uma virgula, um número, parênteses ou um ponto e virgula
typedef enum lexical_element_type {
  LE_NAME,        // e.g. x, avg, fromCSV
  LE_STRING,      // e.g. "business.csv"
  LE_NUMBER,      // e.g. 0, 15
  LE_EQUALS,      // =
  LE_COMMA,       // ,
  LE_OPAREN,      // (
  LE_CPAREN,      // )
  LE_SEMICOLON,   // ;
  LE_FINISH       // Não temos mais elementos
} ElementType;

typedef struct lexical_element {
  ElementType type;
  char *text;
  unsigned int position;
} Element;

// Com isto podemos converter e.g. data = fromCSV("reviews.csv"); em:
// { LE_NAME("data"), LE_EQUALS, LE_NAME("fromCSV"), LE_OPAREN, LE_STRING("reviews.csv"), LE_CPAREN, LE_SEMICOLON, LE_FINISH }

Element *split_line(const char *string);
char *strndup(const char *s, int n);
const char *identify(const char *string, Element *dest);

void print_element(Element *e);

#endif
