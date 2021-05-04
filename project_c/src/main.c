#include <glib.h>
#include <stdio.h>

#include "controller/commands.h"
#include "model/sgr.h"
#include "model/table.h"
#include "view/cli.h"

int main() {
  // SGR x = load_sgr("../csv/users.csv", "../csv/businesses.csv",
  //                 "../csv/reviews.csv");
  // free_sgr(x);
  TABLE x = from_csv("notas.csv", ";");
  fprintf_table(stdout, x, " | ", " | ");
  char *media = avg(x, "nota");
  printf("Média é :%s\n", media);
}
