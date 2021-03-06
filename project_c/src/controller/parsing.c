/**
 * @file parsing.c
 * @author Mariana Rodrigues, Matilde Bravo e Pedro Alves
 * @date 4 Maio 2021
 * @brief This Module is responsible to manipulated all information.
 */

#include "controller/parsing.h"

#include <glib.h>
#include <stdio.h>
#include <stdlib.h>

#include "model/ast.h"
#include "view/colors.h"

TokenStream split_line(const char *string) {
  const char *cur_line = string;

  // Porquê 6? É o que uma chamada de função básica vai utilizar: nome, dois
  // parênteses, um argumento, ponto e virgula e o final
  TokenStream line = make_token_stream(6);
  int size = 6;
  int i = 0;

  while (1) {
    const char *prev = cur_line;
    Token *t = get_token_stream_token(line, i);
    cur_line = identify(cur_line, t);
    set_token_position(t, get_token_position(t) + prev - string);

    if (cur_line == NULL)
      break;
    i++;
    if (i >= size) {
      size *= 2;
      line = resize_token_stream(line, size);
    }
  }

  return line;
}

// O parsing do programa é feito por recursive descent - funções que se chamam
// umas às outras para completar uma AST. Esta função em particular procura uma
// chamada de uma função numa TokenStream, e devolve um erro, caso exista um,
// ou o número de tokens consumidos pela função
SyntaxError parse_function(const TokenStream tokens, AST node, int *consumed) {
  int tok = 0;
  FunctionCall call;

  if (get_token_type(get_token_stream_token(tokens, tok)) == TOK_NAME) {
    // TODO criar um constructor para isto
    call =
        make_function_call(get_token_text(get_token_stream_token(tokens, tok)));
    tok++;
  } else {
    return syntax_error("a function name", get_token_stream_token(tokens, tok));
  }

  if (get_token_type(get_token_stream_token(tokens, tok)) != TOK_OPAREN) {
    free_function_call(call);
    return syntax_error("'('", get_token_stream_token(tokens, tok));
  }

  tok++;

  while (get_token_type(get_token_stream_token(tokens, tok)) != TOK_CPAREN) {
    Token *token = get_token_stream_token(tokens, tok);
    int consumed = 0;
    AST node = make_empty_ast();
    SyntaxError e = parse_expression(token, node, &consumed);

    if (e) {
      free_function_call(call);
      return e;
    }

    tok += consumed;
    token = get_token_stream_token(tokens, tok);

    if (get_token_type(token) != TOK_CPAREN &&
        get_token_type(token) != TOK_COMMA) {
      free_function_call(call);
      return syntax_error("',' or ')'", token);
    }

    function_call_add_arg(call, node);
    free_ast(node);
    if (get_token_type(token) == TOK_COMMA)
      tok++;
  }

  tok++;
  *consumed = tok;
  set_ast_function(node, call);

  return NULL;
}

// Tenta ler uma declaração de variável, do género
// nome = expressão
SyntaxError parse_assignment(const TokenStream tokens, AST node,
                             int *consumed) {
  int tok = 0;
  VarAssignment assignment;

  if (get_token_type(get_token_stream_token(tokens, tok)) == TOK_NAME) {
    assignment = make_var_assignment(
        get_token_text(get_token_stream_token(tokens, tok)));
    tok++;
  } else {
    return syntax_error("a name", get_token_stream_token(tokens, 1));
  }

  if (get_token_type(get_token_stream_token(tokens, tok)) != TOK_EQUALS) {
    free_var_assignment(assignment);
    return syntax_error("'='", get_token_stream_token(tokens, tok));
  }

  tok++;

  int c = 0;
  AST n = make_empty_ast();
  SyntaxError e = parse_expression(get_token_stream_token(tokens, tok), n, &c);

  if (e) {
    free_var_assignment(assignment);
    free_ast(n);
    return e;
  }

  tok += c;

  *consumed = tok;
  set_var_assignment_value(assignment, n);

  set_ast_var_assignment(node, assignment);

  return NULL;
}

// Tenta ler uma expressão, que pode ser uma chamada de uma função, um valor
// simples (e.g. um número ou uma string) ou uma referência a uma variável
SyntaxError parse_expression(const TokenStream tokens, AST node,
                             int *consumed) {
  *consumed = 0;
  do {
    int consumed_now = 0;
    Token *tok = get_token_stream_token(tokens, *consumed);
    TokenType type = get_token_type(get_token_stream_token(tokens, *consumed));
    if (type == TOK_NUMBER) {
      set_ast_number(node, atoi(get_token_text(tok)));
      consumed_now = 1;
    } else if (type == TOK_FLOAT) {
      set_ast_float(node, atof(get_token_text(tok)));
      consumed_now = 1;
    } else if (type == TOK_NAME) {
      // Vamos tentar ler uma função, se não é uma variável
      SyntaxError e = parse_function(tokens, node, &consumed_now);

      if (e) {
        free_syntax_error(e);
        set_ast_variable(node, get_token_text(tok));
        consumed_now = 1;
      }
    } else if (type == TOK_OBRACKET) {
      SyntaxError e = parse_array(tokens, node, &consumed_now);
      if (e) {
        return e;
      }
    } else if (type == TOK_STRING) {
      set_ast_string(node, get_token_text(tok));
      consumed_now = 1;
    } else if (type == TOK_OSQ) {
      AST index = make_empty_ast();
      int c = 0;
      consumed_now += 1;
      SyntaxError e = parse_expression(
          get_token_stream_token(tokens, *consumed + consumed_now), index, &c);
      if (e) {
        free_ast(index);
        return e;
      }
      consumed_now += c;

      if (get_token_type(get_token_stream_token(
              tokens, *consumed + consumed_now)) != TOK_CSQ) {
        free_ast(index);
        return syntax_error("']'", get_token_stream_token(tokens, *consumed));
      }

      consumed_now += 1;

      index_expression(node, index);
    } else {
      return syntax_error("an expression", tokens);
    }
    *consumed += consumed_now;
  } while (get_token_type(get_token_stream_token(tokens, *consumed)) ==
           TOK_OSQ);
  return NULL;
}

// Lê um statement, que é ou uma chamada de uma função seguida de um ponto e
// vírgula ou uma declaração de variável seguida de um ponto e vírgula.
SyntaxError parse_statement(const TokenStream tokens, AST node, int *consumed) {
  SyntaxError e = parse_function(tokens, node, consumed);

  if (e) {
    free_syntax_error(e);
    e = parse_assignment(tokens, node, consumed);

    if (e) {
      free(e);
      return syntax_error("a statement", tokens);
    }
  }

  if (get_token_type(get_token_stream_token(tokens, *consumed)) !=
      TOK_SEMICOLON) {
    free(e);
    return syntax_error("';'", get_token_stream_token(tokens, *consumed));
  }

  *consumed += 1;

  return NULL;
}

// Lê um array, que é uma lista de expressões, separadas por vírgulas, dentro
// de chavetas
SyntaxError parse_array(const TokenStream tokens, AST node, int *consumed) {
  int tok = 0;

  if (get_token_type(get_token_stream_token(tokens, 0)) != TOK_OBRACKET) {
    return syntax_error("'{'", get_token_stream_token(tokens, 0));
  }

  tok += 1;
  GPtrArray *array = g_ptr_array_new_with_free_func((GDestroyNotify)free_ast);

  while (get_token_type(get_token_stream_token(tokens, tok)) != TOK_CBRACKET) {
    int consumed = 0;
    AST node = make_empty_ast();
    SyntaxError e = parse_expression(
        get_token_stream_token(tokens, tok + consumed), node, &consumed);

    if (e) {
      g_ptr_array_free(array, TRUE);
      return e;
    }

    tok += consumed;

    if (get_token_type(get_token_stream_token(tokens, tok)) != TOK_CBRACKET &&
        get_token_type(get_token_stream_token(tokens, tok)) != TOK_COMMA) {
      g_ptr_array_free(array, TRUE);
      return syntax_error("',' or '}'", get_token_stream_token(tokens, tok));
    }

    g_ptr_array_add(array, node);
    if (get_token_type(get_token_stream_token(tokens, tok)) == TOK_COMMA)
      tok++;
  }

  set_ast_array(node, array);
  *consumed = tok + 1;

  return NULL;
}
