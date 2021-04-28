#include <sys/ioctl.h>
#include <stdio.h>
#include <unistd.h>
#include "paginacao.h"
#include "colors.h"
#include "model/table.h"

void get_terminal_size(int* width, int* height) {
  struct winsize w;
  ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);

  *width = w.ws_col;
  *height = w.ws_row;
}

int min(int a, int b) {
  if (a < b) return a;
  return b;
}

int max(int a, int b) {
  if (a > b) return a;
  return b;
}

void move_cursor_to_x(int x) {
  /* https://en.wikipedia.org/wiki/ANSI_escape_code */
  printf("\e[%dG", x);
}

void draw_hborder(int type, int cols, int *widths) {
  // type pode ser -1 para a primeira linha, 0 para uma do meio e 1 para a última
  if (type == -1) {
    printf("┌");
  } else if (type == 1) {
    printf("└");
  } else if (type == 0) {
    printf("├");
  }

  for (int i = 0; i < cols; i++) {
    for (int j = 0; j < widths[i] + 2; j++) {
      printf("─");
    }
    if (type == 0) {
      if (i != cols - 1)
        printf("┼");
      else
        printf("┤");
    } else {
      if (i != cols - 1) {
        if (type == -1)
          printf("┬");
        else
          printf("┴");
      } else {
        if (type == -1) {
          printf("┐");
        } else {
          printf("┘");
        }
      }
    }
  }

  printf("\n");
}

void show_table(TABLE t) {
  int width, height;
  get_terminal_size(&width, &height);

  // 1. Calcular quantas linhas podemos mostrar, em principio max(5, min(20, lines)) + 1, ou algo parecido. Depende do tamanho do terminal.
  // 2. Calcular o tamanho dessas linhas
  // Utilizar a maior para desenhar a caixa
  // Fazer padding com espaços
  // Usar os caracteres de desenho de caixa em vez de |, +, etc
  // Colorizar as coisas, provavelmente usar o ciano para o header tambem
  // Fazer um loop, enquanto não se carregar no 'q' ou não acabar a tabela, esperamos por uma seta para os lados! Mostramos tbm essa indicação
  int table_lines = get_number_lines_table(t);

  // TODO lógica de wrapping.... :/
  int lines_to_show = min(table_lines, max(5, min(height / 2 - 4, table_lines)));
  int cols = get_number_fields_table(t);
  int widths[cols];

  for (int i = 0; i < cols; i++) {
    widths[i] = strlen(table_index(t, 0, i));
  }

  int start = 1;
  for (int i = start; i < lines_to_show + start; i++) {
    for (int j = 0; j < cols; j++) {
      widths[j] = max(widths[j], strlen(table_index(t, i, j)));
    }
  }

  // TODO calcular
  int start_x = 5;
  // Vamos desenhar a caixa
  move_cursor_to_x(start_x);
  
  draw_hborder(-1, cols, widths);
  for (int j = 0, start_col = start_x; j < cols; j++) {
    move_cursor_to_x(start_col);
    printf("│ ");
    printf(BOLD FG_CYAN "%s" RESET_ALL, table_index(t, 0, j));
    move_cursor_to_x(start_col);
    start_col += widths[j] + 3;

    if (j == cols - 1) {
      move_cursor_to_x(start_col);
      printf("│\n");
    }
  }

  move_cursor_to_x(start_x);
  draw_hborder(0, cols, widths);

  for (int i = start; i < lines_to_show + start; i++) {
    int start_col = start_x;
    for (int j = 0; j < cols; j++) {
      move_cursor_to_x(start_col);
      printf("│ ");
      printf("%s", table_index(t, i, j));
      start_col += widths[j] + 3;
    }

    move_cursor_to_x(start_col);
    printf("│\n");
    if (i != lines_to_show + start - 1) {
      move_cursor_to_x(start_x);
      draw_hborder(0, cols, widths);
    }
  }
  move_cursor_to_x(start_x);
  draw_hborder(1, cols, widths);
}
