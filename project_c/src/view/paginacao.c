/**
 * @file paginacao.c
 * @author Mariana Rodrigues, Matilde Bravo e Pedro Alves
 * @date 4 Maio 2021
 * @brief Mostra uma vista paginada de uma tabela
 */

#include "view/paginacao.h"
#include "model/auxiliary.h"
#include "model/table.h"
#include "view/colors.h"
#include <stdio.h>
#include <sys/ioctl.h>
#include <termios.h>
#include <unistd.h>

// Utiliza ioctl para determinar o tamanho do terminal, em linhas e colunas
void get_terminal_size(int *width, int *height) {
  struct winsize w;
  ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);

  *width = w.ws_col;
  *height = w.ws_row;
}

// Coloca o cursor na coluna especificada, através de sequências de controlo do
// terminal
// https://en.wikipedia.org/wiki/ANSI_escape_code
void move_cursor_to_x(int x) { printf("\e[%dG", x); }

// Utiliza sequências de controlo de terminal para perguntar ao terminal qual é
// a posição atual do cursor.
// https://www2.ccs.neu.edu/research/gpc/MSim/vona/terminal/vtansi.htm
void get_cursor(int *x, int *y) {
  printf("\e[6n");
  // A resposta chega pelo stdin, por isso utilizamos scanf para a interpretar
  if (scanf("\e[%d;%dR", x, y) != 2) {
    *x = 0;
    *y = 0;
  }
}

// Utiliza sequências de controlo de terminal para colocar o cursor numa
// posição especificada
void set_cursor(int x, int y) { printf("\e[%d;%df", x, y); }

// Utiliza sequências de controlo de terminal para mover o cursor para cima
void cursor_up(int x) {
  if (x != 0)
    printf("\e[%dA", x);
}

// Desenha uma borda horizontal para uma tabela, utilizando os caracteres
// Unicode para desennho de caixas.
//
// O tipo indica se esta linha é a primeira (-1), uma do meio (0), ou a última
// (1)
//
// https://en.wikipedia.org/wiki/Box-drawing_character
void draw_hborder(int type, int cols, int *widths) {
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

// Desenha uma tabela, com um pager se a tabela não couber no ecrã.
void show_table(TABLE t) {
  int width, height;
  get_terminal_size(&width, &height);

  int table_lines = get_number_lines_table(t);
  int footer_lines = get_number_footers_table(t);

  // Aqui calculamos quanttas linhas podemos mostrar no ecrã.
  int lines_to_show =
      min(table_lines, max(5, min(height / 2 - 4, table_lines)));
  int cols = get_number_fields_table(t);
  int widths[cols];
  int footer_widths[2] = {0, 0};

  // Determinar o tamanho das colunas
  for (int i = 0; i < cols; i++) {
    char *field = field_index(t, i);
    widths[i] = strlen(field);
    free(field);
  }

  // Por defeito, o stdin é buffered até encontrar um EOF ou um
  // newline. Nós não queremos isso para ler setas, por isso vamos
  // temporariamente alterar as definições do terminal para que não
  // faça buffering.
  struct termios oldt, newt;
  int c = 0;
  tcgetattr(STDIN_FILENO, &oldt);
  newt = oldt;

  // Desativamos a visualização do que foi escrito e o line buffering.
  newt.c_lflag = ~(ICANON | ECHO);
  tcsetattr(STDIN_FILENO, TCSANOW, &newt);

  int start = 0;
  int start_x = 5;

  // Vamos usar escape codes para configurar certas coisas no terminal,
  // nomeadamente, queremos esconder o cursor e desativar wrapping
  // https://github.com/dylanaraps/writing-a-tui-in-bash
  printf("\e[?7l\e[?25l");

  int lines = 0;

  do {
    // Agora restauramos a posição sempre que vamos desenhar a tabela!
    cursor_up(lines);
    printf("\e[J"); // Limpar o ecrã

    // Ao carregar numa seta, a sequência de caracteres recebida pelo terminal
    // é \e[A, onde A pode ser A, B, C ou D
    if (c == '\e') {
      if (getchar() == '[') {
        c = getchar();
        switch (c) {
        case 'A':
          start = max(0, start - 1);
          break;
        case 'B':
          start = min(table_lines - lines_to_show, start + 1);
          break;
        case 'C':
          start = min(table_lines - lines_to_show, start + lines_to_show - 1);
          break;
        case 'D':
          start = max(0, start - (lines_to_show - 1));
          break;
        }
      }
    }

    // Determinamos outra vez as larguras das colunas, desta vez tendo em conta
    // o conteúdo das linhas em si
    for (int i = start; i < lines_to_show + start; i++) {
      for (int j = 0; j < cols; j++) {
        char *value = table_index(t, i, j);
        widths[j] = max(widths[j], strlen(value));
        free(value);
      }
    }

    // Aqui determinamos o tamanho das linhas do footer
    for (int i = 0; i < footer_lines; i++) {
      footer_widths[0] = max(footer_widths[0], strlen(get_footer_name(t, i)));
      footer_widths[1] = max(footer_widths[1], strlen(get_footer_value(t, i)));
    }

    // Vamos desenhar a caixa
    move_cursor_to_x(start_x);
    draw_hborder(-1, cols, widths);

    // Desenhar o cabeçalho
    for (int j = 0, start_col = start_x; j < cols; j++) {
      move_cursor_to_x(start_col);
      printf("│ ");
      char *field = field_index(t, j);
      printf(BOLD FG_CYAN "%s" RESET_ALL, field);
      free(field);
      move_cursor_to_x(start_col);
      start_col += widths[j] + 3;

      if (j == cols - 1) {
        move_cursor_to_x(start_col);
        printf("│\n");
      }
    }

    move_cursor_to_x(start_x);
    draw_hborder(0, cols, widths);

    // Desenhar as linhas
    for (int i = start; i < lines_to_show + start; i++) {
      int start_col = start_x;
      for (int j = 0; j < cols; j++) {
        move_cursor_to_x(start_col);
        printf("│ ");
        char *value = table_index(t, i, j);
        printf("%s", value);
        free(value);
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

    lines = lines_to_show * 2 + 3;

    // Se houverem mais linhas, mostramos um indicador a dizer isso
    if (lines_to_show < table_lines) {
      move_cursor_to_x(start_x);
      printf(BOLD BG_WHITE FG_BLACK "%d-%d/%d" RESET_ALL "\n", start + 1,
             start + lines_to_show, table_lines);
      lines += 1;
    }

    // Vamos desenhar o footer
    if (footer_lines > 0) {
      int cursor_x, cursor_y;
      get_cursor(&cursor_x, &cursor_y);

      int table_width = 4;
      for (int i = 0; i < cols; i++) {
        table_width += widths[i];
        if (i != cols - 1)
          table_width += 3;
      }

      // O footer aparece à direita da tabela
      int start_at = start_x + table_width + 1;
      cursor_up(lines);
      move_cursor_to_x(start_at);
      draw_hborder(-1, 2, footer_widths);

      for (int i = 0; i < footer_lines; i++) {
        move_cursor_to_x(start_at);
        printf("│ " BOLD FG_CYAN "%s" RESET_ALL, get_footer_name(t, i));
        move_cursor_to_x(start_at + footer_widths[0] + 3);
        printf("│ %s", get_footer_value(t, i));
        move_cursor_to_x(start_at + footer_widths[0] + 3 + footer_widths[1] +
                         3);
        printf("│\n");
        move_cursor_to_x(start_at);

        if (i == footer_lines - 1) {
          draw_hborder(1, 2, footer_widths);
        } else {
          draw_hborder(0, 2, footer_widths);
        }
      }

      set_cursor(cursor_x, cursor_y);
    }
  } while (lines_to_show < table_lines && (c = getchar()) != 'q');

  // Vamos desfazer todas as configurações que fizemos no início
  tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
  // Voltamos a ativar line wrapping e o cursor
  printf("\e[?25h\e[7h");
}
