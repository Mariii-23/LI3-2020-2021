#ifndef STATS_H
#define STATS_H

#include "glib.h"
typedef struct stats *Stats;
Stats start_statistics();
float get_average_number_stars(Stats stats, char *business_id);
void update_average_stars(Stats stats, char *business_id, float new_star);

int is_empty_business_id_to_stars(Stats stats);
int is_empty_stats(Stats stats);

void start_table_iter_init_city_to_stars(GHashTableIter *iter, Stats stats);
void start_table_iter_init_category_to_stars(GHashTableIter *iter, Stats stats);

int iter_next_table_business_id_to_stars(GHashTableIter *iter, int *stars,
                                         char **business_id);
/* GList *get_glist_by_city(Stats stats, char *city); */
int iter_next_table_business_id_to_stars(GHashTableIter *iter, int *stars,
                                         char **business_id);
void init_city_to_business_by_star(Stats stats);
void init_category_to_business_by_star(Stats stats);
void add_city_to_business_by_star(Stats stats, char *city, char *business_id,
                                  float stars);
void add_category_to_business_by_star(Stats stats, char *category,
                                      char *business_id, float stars);
GSList *n_larger_gs_list(int N, GSList *gs_list);
GSList *n_larger_city_star(Stats stats, char *city, int N);
#endif
