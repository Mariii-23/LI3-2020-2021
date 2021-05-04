#include "model/config.h"
#include "controller/commands.h"
#include "model/table.h"
#include <glib.h>
#include <stdio.h>
#include <stdlib.h>

struct config {
  char *user_csv;
  char *businesses_csv;
  char *reviews_csv;
};

CONFIG read_config(char *path_to_config) {
  CONFIG config = malloc(sizeof(struct config));
  if (!path_to_config) {
    *config = (struct config){.user_csv = g_strdup("users.csv"),
                              .businesses_csv = g_strdup("businesses.csv"),
                              .reviews_csv = g_strdup("reviews.csv")};
  } else {
    // parse csv
    TABLE t = from_csv(path_to_config, ";");
    *config = (struct config){
        .user_csv = table_index(t, 0, 1),
        .businesses_csv = table_index(t, 1, 1),
        .reviews_csv = table_index(t, 2, 1),
    };
    free_table(t);
  }
  return config;
}
