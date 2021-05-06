/**
 * @file exec.c
 * @author Mariana Rodrigues, Matilde Bravo e Pedro Alves
 * @date 4 Maio 2021
 * @brief This Module is responsible of manipulating all information.
 */

#include "controller/exec.h"
#include <glib.h>
#include <gmodule.h>

#include "controller/parsing.h"
#include "model/sgr.h"
#include "model/state.h"
#include "model/table.h"
#include "view/colors.h"

// Dado um estado do programa e uma AST, esta função executa-a e devolve uma
// variável (o seu resultado).
Variable execute(STATE state, AST ast) {
  Variable ret = NULL;
  VariableValue val;

  switch (get_ast_type(ast)) {
  case AST_NONE:
    return NULL;
  case AST_VARIABLE:
    // Se recebemos uma referência a uma variável, vamos procurá-la no estado
    ret = find_variable(state, get_ast_variable(ast));
    if (!ret)
      fprintf(stderr,
              BOLD FG_RED "Error: " RESET_ALL "variable %s does not exist.\n",
              get_ast_variable(ast));
    break;
  case AST_NUMBER:
    // Tanto com números como com floats, criamos uma variável simples (que não
    // fica no estrado) com o seu valor
    val.number = get_ast_number(ast);
    ret = init_var(VAR_NUMBER, val, NULL);
    break;
  case AST_FLOAT:
    val.float_num = get_ast_float(ast);
    ret = init_var(VAR_FLOAT, val, NULL);
    break;
  case AST_STRING: {
    const char *str = get_ast_string(ast);
    val.string = malloc(strlen(str) - 1);
    int i = 0, j = 0;

    // Temos de retirar as aspas e fazer escaping da string
    for (; str[j]; j++) {
      if (str[j] != '"') {
        if (str[j] == '\\')
          j++;
        val.string[i] = str[j];
        i++;
      }
    }

    val.string[i] = '\0';

    ret = init_var(VAR_STRING, val, NULL);

    break;
  }
  case AST_ASSIGNMENT:
    // No caso de assignment de uma variável, executamos o lado direito para
    // termos o seu valor e, se for bem sucedido, críamos a variável no estado
    ret = execute(state, get_var_assignment_value(get_ast_assignment(ast)));
    if (ret) {
      set_var_name(ret, get_var_assignment_variable(get_ast_assignment(ast)));
      create_variable(state, ret);
    }
    break;
  case AST_ARRAY: {
    // Quando temos um array, temos de interpretar individualmente todos os
    // membros do array e criar depois um array com eles todos
    GPtrArray *array = g_ptr_array_new();
    const GPtrArray *array_ast = get_ast_array(ast);

    for (int i = 0; i < array_ast->len; i++) {
      AST element = g_ptr_array_index(array_ast, i);
      Variable result = execute(state, element);
      if (!result) {
        for (int j = 0; j < i; j++) {
          free_if_possible(g_ptr_array_index(array, j));
        }
        return NULL;
      }

      g_ptr_array_add(array, result);
    }

    val.array = array;
    ret = init_var(VAR_ARRAY, val, NULL);
    break;
  }
  case AST_INDEX: {
    // Ao indexarmos uma variável, temos de verificar se esta é dos tipos c
    // rretos. Executamos tanto a expressão a ser indexada e a expressão do í
    // dice
    Variable expr = execute(state, get_indexed_expression(get_ast_index(ast)));
    if (expr == NULL) {
      return NULL;
    }
    if (get_var_type(expr) != VAR_ARRAY && get_var_type(expr) != VAR_TABLE) {
      free_if_possible(expr);
      fprintf(stderr, BOLD FG_RED "Error: " RESET_ALL
                                  "can only index tables and arrays.\n");
      return NULL;
    }

    Variable index = execute(state, get_indexed_index(get_ast_index(ast)));
    if (get_var_type(index) != VAR_NUMBER) {
      free_if_possible(expr);
      free_if_possible(index);
      fprintf(stderr,
              BOLD FG_RED "Error: " RESET_ALL "index must be a number.\n");
      return NULL;
    }

    // Já temos o valor do índice, por isso podemos libertar a memória
    int i = get_var_value(index).number;
    free_if_possible(index);

    if (get_var_type(expr) == VAR_TABLE) {
      // Se for uma tabela, temos de a converter num array
      TABLE table = get_var_value(expr).table;
      if (i >= get_number_lines_table(table)) {
        free_if_possible(expr);
        fprintf(stderr,
                BOLD FG_RED "Error: " RESET_ALL "table out of bounds.\n");
        return NULL;
      }

      int w = get_number_fields_table(table);
      GPtrArray *array = g_ptr_array_sized_new(w);
      VariableValue val;
      for (int j = 0; j < w; j++) {
        val.string = table_index(table, i, j);
        g_ptr_array_add(array, init_var(VAR_STRING, val, NULL));
      }
      val.array = array;
      ret = init_var(VAR_ARRAY, val, NULL);
    } else {
      GPtrArray *arr = get_var_value(expr).array;

      if (i >= arr->len) {
        free_if_possible(expr);
        fprintf(stderr,
                BOLD FG_RED "Error: " RESET_ALL "array out of bounds.\n");
        return NULL;
      }

      ret = g_ptr_array_index(arr, i);
    }
    break;
  }
  case AST_FUNCTIONCALL: {
    // Ao chamarmos uma função, temos de ir buscar a variável referente à
    // função
    ret = find_variable(state, get_function_name(get_ast_function_call(ast)));
    if (!ret) {
      fprintf(stderr,
              BOLD FG_RED "Error: " RESET_ALL "function %s does not exist.\n",
              get_function_name(get_ast_function_call(ast)));
      return NULL;
    }

    FunctionVal function = get_var_value(ret).function;
    const GPtrArray *args_ast = get_function_args(get_ast_function_call(ast));
    int n_args = get_n_args(function);

    Variable *args = malloc(sizeof(Variable) * n_args);

    // Agora verificamos se tem o número certo de argumentos. Se a função for
    // defaultable, pode ter 0 argumentos
    if (get_defaultable(function) && args_ast->len == 0) {
      // Vamos passar sempre void caso sejam os argumentos default
      for (int i = 0; i < n_args; i++) {
        args[i] = void_var();
      }
    } else {
      if (args_ast->len != n_args) {
        free(args);
        fprintf(stderr,
                BOLD FG_RED "Error: " RESET_ALL
                            "wrong number of arguments, expected" BOLD
                            " %d" RESET_ALL ", got " BOLD "%d" RESET_ALL ".\n",
                n_args, args_ast->len);
        return NULL;
      }

      // Verificar os tipos dos argumentos
      for (int i = 0; i < n_args; i++) {
        AST arg = g_ptr_array_index(args_ast, i);
        args[i] = execute(state, arg);
        int error = args[i] == NULL;

        if (!error && get_arg_type(function, i) != VAR_ANY) {
          if (get_arg_type(function, i) != get_var_type(args[i])) {
            if (get_arg_type(function, i) == VAR_FLOAT &&
                get_var_type(args[i]) == VAR_NUMBER) {
              // Promoção de ints a floats
              set_var_type(args[i], VAR_FLOAT);
              VariableValue v = get_var_value(args[i]);
              v.float_num = v.number;
              set_var_value(args[i], v);
            } else {
              fprintf(stderr,
                      BOLD FG_RED "Error on argument " FG_YELLOW "%d" FG_RED
                                  ": " RESET_ALL "expected type " BOLD
                                  "%s" RESET_ALL ", got " BOLD "%s" RESET_ALL
                                  ".\n",
                      i + 1, type_name(get_arg_type(function, i)),
                      type_name(get_var_type(args[i])));
              error = 1;
            }
          }
        }

        if (error) {
          for (int j = 0; j <= i; j++) {
            if (args[i])
              free_if_possible(args[i]);
          }
          free(args);
          return NULL;
        }
      }
    }

    // Agora chamamos a função com os seus argumentos e devolvemos o seu
    // resultado
    ret = get_function(function)(state, args);
  } break;
  }

  return ret;
}

// Imprimimos o valor de uma variável
void print_var(Variable var) {
  switch (get_var_type(var)) {
  case VAR_STRING:
    printf("String: %s\n", get_var_value(var).string);
    break;
  case VAR_NUMBER:
    printf("Number: %d\n", get_var_value(var).number);
    break;
  case VAR_FLOAT:
    printf("Float: %f\n", get_var_value(var).float_num);
    break;
  case VAR_FUNCTION:
    printf("Function\n");
    break;
  case VAR_ARRAY:
    printf("Array: %d elements\n", get_var_value(var).array->len);
    break;
  case VAR_OPERATOR:
    printf("Operator: %d\n", get_var_value(var).operator);
    break;
  case VAR_SGR:
    printf("SGR\n");
    break; // TODO!
  case VAR_TABLE:
    printf("Table\n");
    break;
  case VAR_VOID:
    printf("Void\n");
    break;
  case VAR_ANY:
    printf("Unknown type\n");
    break;
  }
}
