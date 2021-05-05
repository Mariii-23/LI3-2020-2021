#include "view/paginacao.h"
#include "model/auxiliary.h"
#include "model/table.h"
#include "view/colors.h"
#include <stdio.h>
#include <sys/ioctl.h>
#include <termios.h>
#include <unistd.h>

void get_terminal_size(int *width, int *height) {
  struct winsize w;
  ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);

  *width = w.ws_col;
  *height = w.ws_row;
}

void move_cursor_to_x(int x) {
  /* https://en.wikipedia.org/wiki/ANSI_escape_code */
  printf("\e[%dG", x);
}

void get_cursor(int *x, int *y) {
  // https://www2.ccs.neu.edu/research/gpc/MSim/vona/terminal/vtansi.htm
  // Código para receber a posição atual
  printf("\e[6n");
  if (scanf("\e[%d;%dR", x, y) != 2) {
    *x = 0;
    *y = 0;
  }
}

void set_cursor(int x, int y) { printf("\e[%d;%df", x, y); }

void cursor_up(int x) {
  if (x != 0)
    printf("\e[%dA", x);
}

void draw_hborder(int type, int cols, int *widths) {
  // type pode ser -1 para a primeira linha, 0 para uma do meio e 1 para a
  // última
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

  // 1. Calcular quantas linhas podemos mostrar, em principio max(5, min(20,
  // lines)) + 1, ou algo parecido. Depende do tamanho do terminal.
  // 2. Calcular o tamanho dessas linhas
  // Utilizar a maior para desenhar a caixa
  // Fazer padding com espaços
  // Usar os caracteres de desenho de caixa em vez de |, +, etc
  // Colorizar as coisas, provavelmente usar o ciano para o header tambem
  // Fazer um loop, enquanto não se carregar no 'q' ou não acabar a tabela,
  // esperamos por uma seta para os lados! Mostramos tbm essa indicação
  int table_lines = get_number_lines_table(t);
  int footer_lines = get_number_footers_table(t);

  // TODO lógica de wrapping.... :/
  int lines_to_show =
      min(table_lines, max(5, min(height / 2 - 4, table_lines)));
  int cols = get_number_fields_table(t);
  int widths[cols];
  int footer_widths[2] = {0, 0};

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

    // Somehow desliguei ctrl+c para matar o programa...
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

    for (int i = start; i < lines_to_show + start; i++) {
      for (int j = 0; j < cols; j++) {
        char *value = table_index(t, i, j);
        widths[j] = max(widths[j], strlen(value));
        free(value);
      }
    }

    for (int i = 0; i < footer_lines; i++) {
      footer_widths[0] = max(footer_widths[0], strlen(get_footer_name(t, i)));
      footer_widths[1] = max(footer_widths[1], strlen(get_footer_value(t, i)));
    }

    // Vamos desenhar a caixa
    move_cursor_to_x(start_x);

    draw_hborder(-1, cols, widths);
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

    if (lines_to_show < table_lines) {
      move_cursor_to_x(start_x);
      printf(BOLD BG_WHITE FG_BLACK "%d-%d/%d" RESET_ALL "\n", start + 1,
             start + lines_to_show, table_lines);
    }

    lines = lines_to_show * 2 + 4;

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
  // Por algum motivo, o line wrapping não está a ficar ativo...
  printf("\e[?25h\e[7h");
}
