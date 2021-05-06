#ifndef STATE_H
/**
 * @file state.h
 * @author Mariana Rodrigues, Matilde Bravo e Pedro Alves
 * @date 4 Maio 2021
 * @brief This Module is responsible to manipulated all information.
 */

#define STATE_H
#include "controller/commands.h"
#include "model/table.h"
#include "sgr.h"
#include <glib.h>

// Neste ficheiro, definimos dois conceitos importantes para o interpretador -
// variáveis e o estado global.
//
// O estado global é um mapa (implementado com uma binary tree para permitir
// pesquisa eficiente para tab completion) entre o nome de uma variável e o seu
// valor.
//
// Uma variável pode ter vários tipos, definidos no enum variable_type. Estes
// tipos são armazenados numa tagged union - o enum serve para identificar qual
// o tipo de variável e depois, para poupar memória, é utilizada uma union para
// guardar o valor em si.
//
// É importante salientar que no interpretador, tudo são variáveis - até as
// funções.

// Uma variável é qualquer valor no programa - incluindo funções.
typedef enum variable_type {
  VAR_NUMBER,
  VAR_FLOAT,
  VAR_SGR,
  VAR_TABLE,
  VAR_STRING,
  VAR_FUNCTION,
  VAR_ARRAY,
  VAR_OPERATOR,
  VAR_VOID,
  // O tipo ANY nunca é dado a uma variável - serve apenas para especificar que
  // qualquer parâmetro é válido ao definir uma função.
  VAR_ANY
} VariableType;

typedef union {
  int number;
  float float_num;
  SGR sgr;
  TABLE table;
  char *string;
  struct function *function;
  GPtrArray *array;
  OPERATOR operator;
} VariableValue;

// STATE é o estado do programa - contem todas as variáveis e os seus
// valores
typedef GTree *STATE;

typedef struct variable *Variable;
typedef struct function *FunctionVal;

// As funções recebem tanto o estado global como uma lista dos seus argumentos.
// O tamanho desta lista é conhecido, pois é sempre do tamanho do número de
// argumentos esperados por uma função.
typedef Variable (*FunctionPtr)(STATE s, Variable *args);

// Inicializa uma variável. Pode não ter um nome.
Variable init_var(VariableType type, VariableValue val, const char *name);
void free_var(Variable var);
// As variáveis são reference-counted. Estas referências contam o número de
// vezes que ocorrem no estado do programa. Esta função liberta as variáveis se
// já não ocorrem no estado do programa.
void free_if_possible(Variable var);
VariableType get_var_type(Variable var);
VariableValue get_var_value(Variable var);
void set_var_name(Variable var, const char *name);
void set_var_value(Variable var, VariableValue v);
void set_var_type(Variable var, VariableType t);
// Devolve uma variável nova do tipo void
Variable void_var();

// Devolve uma representação textual do tipo de uma variável
const char *type_name(VariableType type);

// Inicializa um estado vazio
STATE init_state();

// Liberta o estado do programa
void free_state(STATE state);

// Regista uma variável no estado do programa, utilizando o nome definido
// dentro da variável
void create_variable(STATE state, Variable var);

// Procura uma variável no estado do programa através do seu nome. Se não for
// encontrada, devolve null.
Variable find_variable(STATE state, const char *name);

// Devolve uma tabela com o nome e tipo de todas as variáveis
TABLE state_table(STATE s);

// Cria uma função para o programa. Em princípio, nunca queremos usar isto
// diretamente, sendo melhor usar a macro define_function
FunctionVal create_function(int n_args, int defaultable,
                            VariableType return_type, FunctionPtr function,
                            const VariableType *args, const char *help);
int get_n_args(FunctionVal func);
// Devolve se é possível ou não chamar a função sem argumentos nenhuns
int get_defaultable(FunctionVal func);
VariableType get_arg_type(FunctionVal func, int i);
FunctionPtr get_function(FunctionVal func);
const char *get_function_help(FunctionVal func);

// Esta macro serve para definir uma função rapidamente, pois é bastante
// tedioso e repetitivo fazê-lo através das funções.
#define define_function(state, name, handler, ret, defaultable, n_args, help,  \
                        ...)                                                   \
  {                                                                            \
    VariableType f_args[] = {__VA_ARGS__};                                     \
    VariableValue val;                                                         \
    val.function =                                                             \
        create_function(n_args, defaultable, ret, handler, f_args, help);      \
    create_variable(state, init_var(VAR_FUNCTION, val, name));                 \
  }

#endif
