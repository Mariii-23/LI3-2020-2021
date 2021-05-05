#ifndef STATS_H
#define STATS_H

#include "businesses.h"
#include "glib.h"
#include "table.h"
#include <stdbool.h>
typedef struct stats *Stats;
Stats start_statistics();
float get_average_number_stars(Stats stats, char *business_id);
void update_average_stars(Stats stats, char *business_id, float new_star);

void added_number_stars_and_reviews_table(Stats const stats, TABLE table,
                                          char const *business_id);
bool is_empty_business_id_to_stars(Stats stats);
bool is_empty_stats(Stats stats);

void init_city_to_business_by_star(Stats stats);
void init_category_to_business_by_star(Stats stats);

void build_city_and_category_hash_table(BusinessCollection const businesses,
                                        Stats stats);

void all_n_larger_city_star(Stats stats, int const N, TABLE table);
void n_larger_category_star(Stats stats, char *category, int const N,
                            TABLE table);
void n_larger_city_star(Stats stats, char *category, float N, TABLE table);

void n_larger_than_city_star(Stats stats, char *city, float N, TABLE table);
void free_stats(Stats stats);
#endif
