#include "controller/exec.h"
#include <glib.h>
#include <gmodule.h>

#include "controller/parsing.h"
#include "model/sgr.h"
#include "model/state.h"
#include "model/table.h"
#include "view/colors.h"

Variable execute(STATE state, AST *ast) {
  Variable ret = NULL;
  VariableValue val;

  switch (ast->type) {
  case AST_VARIABLE:
    ret = find_variable(state, ast->value.variable);
    if (!ret)
      fprintf(stderr,
              BOLD FG_RED "Error: " RESET_ALL "variable %s does not exist.\n",
              ast->value.variable);
    break;
  case AST_NUMBER:
    val.number = ast->value.number;
    ret = init_var(VAR_NUMBER, val, NULL);
    break;
  case AST_STRING:
    // Tenho de retirar as aspas
    val.string = malloc(strlen(ast->value.string) - 1);
    int i = 0, j = 0;

    for (; ast->value.string[j]; j++) {
      if (ast->value.string[j] != '"') {
        if (ast->value.string[j] == '\\')
          j++;
        val.string[i] = ast->value.string[j];
        i++;
      }
    }

    val.string[i] = '\0';

    ret = init_var(VAR_STRING, val, NULL);

    break;
  case AST_ASSIGNMENT:
    // Bug possivel com garbage collection, provavelmente o melhor é ter
    // "names" em vez de name, com um array. Ou então simplesmente
    // fazemos reference counting, algo assim simples.
    ret = execute(state, ast->value.assignment->value);
    if (ret) {
      set_var_name(ret, ast->value.assignment->variable);
      create_variable(state, ret);
    }
    break;
  case AST_ARRAY: {
    GPtrArray *array = g_ptr_array_new();
    GArray *array_ast = ast->value.array;

    for (int i = 0; i < array_ast->len; i++) {
      AST element = g_array_index(array_ast, AST, i);
      Variable result = execute(state, &element);
      if (!result) {
        for (int j = 0; j < i; j++) {
          free_if_possible(state, g_ptr_array_index(array, j));
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
    Variable expr = execute(state, ast->value.index->expression);
    if (expr == NULL) {
      return NULL;
    }
    if (get_var_type(expr) != VAR_ARRAY && get_var_type(expr) != VAR_TABLE) {
      free_if_possible(state, expr);
      fprintf(stderr, BOLD FG_RED "Error: " RESET_ALL
                                  "can only index tables and arrays.\n");
      return NULL;
    }

    Variable index = execute(state, ast->value.index->index);
    if (get_var_type(index) != VAR_NUMBER) {
      free_if_possible(state, expr);
      free_if_possible(state, index);
      fprintf(stderr,
              BOLD FG_RED "Error: " RESET_ALL "index must be a number.\n");
      return NULL;
    }

    int i = get_var_value(index).number;
    free_if_possible(state, index);

    if (get_var_type(expr) == VAR_TABLE) {
      // Temos de converter num array
      TABLE table = get_var_value(expr).table;
      if (i >= get_number_lines_table(table)) {
        free_if_possible(state, expr);
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
        free_if_possible(state, expr);
        fprintf(stderr,
                BOLD FG_RED "Error: " RESET_ALL "array out of bounds.\n");
        return NULL;
      }

      ret = g_ptr_array_index(arr, i);
    }
    break;
  }
  case AST_FUNCTIONCALL: {
    // Dentro de um block para podermos definir variáveis

    ret = find_variable(state, ast->value.function->function_name);
    if (!ret) {
      fprintf(stderr,
              BOLD FG_RED "Error: " RESET_ALL "function %s does not exist.\n",
              ast->value.function->function_name);
      return NULL;
    }

    FunctionVal function = get_var_value(ret).function;
    GArray *args_ast = ast->value.function->args;
    int n_args = get_n_args(function);

    if (args_ast->len != n_args) {
      fprintf(stderr,
              BOLD FG_RED "Error: " RESET_ALL
                          "wrong number of arguments, expected" BOLD
                          " %d" RESET_ALL ", got " BOLD "%d" RESET_ALL ".\n",
              n_args, args_ast->len);
      return NULL;
    }

    Variable *args = malloc(sizeof(Variable) * n_args);
    for (int i = 0; i < n_args; i++) {
      AST arg = g_array_index(args_ast, AST, i);
      args[i] = execute(state, &arg);
      int error = args[i] == NULL;

      if (!error && get_arg_type(function, i) != VAR_ANY) {
        if (get_arg_type(function, i) != get_var_type(args[i])) {
          fprintf(stderr,
                  BOLD FG_RED "Error on argument " FG_YELLOW "%d" FG_RED
                              ": " RESET_ALL "expected type " BOLD
                              "%s" RESET_ALL ", got " BOLD "%s" RESET_ALL ".\n",
                  i + 1, type_name(get_arg_type(function, i)),
                  type_name(get_var_type(args[i])));
          error = 1;
        }
      }

      if (error) {
        for (int j = 0; j <= i; j++) {
          if (args[i])
            free_if_possible(state, args[i]);
        }
        free(args);
        return NULL;
      }
    }

    ret = get_function(function)(args);
  } break;
  }

  return ret;
}

void print_var(Variable var) {
  // TODO
  switch (get_var_type(var)) {
  case VAR_STRING:
    printf("String: %s\n", get_var_value(var).string);
    break;
  case VAR_NUMBER:
    printf("Number: %d\n", get_var_value(var).number);
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
