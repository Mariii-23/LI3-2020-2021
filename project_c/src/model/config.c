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

Config read_config(char *path_to_config) {
  Config config = malloc(sizeof(struct config));
  if (!path_to_config) {
    *config = (struct config){.user_csv = g_strdup("users.csv"),
                              .businesses_csv = g_strdup("businesses.csv"),
                              .reviews_csv = g_strdup("reviews.csv")};
  } else {
    TABLE t = from_csv(path_to_config, ";");
    if (!t) {
      *config = (struct config){.user_csv = g_strdup("users.csv"),
                                .businesses_csv = g_strdup("businesses.csv"),
                                .reviews_csv = g_strdup("reviews.csv")};
    } else {
      *config = (struct config){
          .user_csv = table_index(t, 0, 1),
          .businesses_csv = table_index(t, 1, 1),
          .reviews_csv = table_index(t, 2, 1),
      };
      free_table(t);
    }
  }
  return config;
}

void free_config(Config config) {
  if (config) {
    free(config->businesses_csv);
    free(config->user_csv);
    free(config->reviews_csv);
    free(config);
  }
}
