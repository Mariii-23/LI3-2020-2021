#include "stats.h"
#include <string.h>

#include "glib.h"
typedef struct stars_tuple {
  float current_average; // current start average
  size_t number_reviews; // number of reviews read up to this point
} * StarsTuple;

typedef struct city_tuple {
  float stars; // current start average
  char *business_id;
} * CityTuple;

struct stats {
  GHashTable *business_id_to_stars;         // updated as a new review is read,
                                            // business_id to a StarsTuple
  GHashTable *city_to_business_by_star;     // linked list of businesse ssorted
                                            // decrescently by stars
  GHashTable *category_to_business_by_star; // linked list of businesse
                                            // ssorted decrescently by category
};

Stats start_statistics() {
  Stats stats = malloc(sizeof(struct stats));
  stats->business_id_to_stars = g_hash_table_new(g_str_hash, g_str_equal);
  return stats;
}

// when a new review is read this function is called
void update_average_stars(Stats stats, char *business_id, float new_star) {
  GHashTable *business_hash = stats->business_id_to_stars;
  StarsTuple tuplo = g_hash_table_lookup(business_hash, business_id);
  if (!tuplo) {
    tuplo = calloc(1, sizeof(struct stars_tuple));
    g_hash_table_insert(business_hash, g_strdup(business_id), tuplo);
  }
  tuplo->number_reviews++;
  tuplo->current_average =
      ((tuplo->current_average * tuplo->number_reviews) + new_star) /
      tuplo->number_reviews;
}

static void build_category_hash_table(Stats stats) {
  stats->business_id_to_stars = g_hash_table_new(g_str_hash, g_str_equal);
  // TODO
}

static void build_city_hash_table(Stats stats) {
  stats->category_to_business_by_star =
      g_hash_table_new(g_str_hash, g_str_equal);
  // TODO
}
float get_average_number_stars(Stats stats, char *business_id) {
  return *(double *)g_hash_table_lookup(stats->business_id_to_stars,
                                        business_id);
}

int is_empty_stats(Stats stats) {
  int empty = 1;
  if (stats)
    empty = 0;
  return empty;
}

int is_empty_business_id_to_stars(Stats stats) {
  int empty = 1;
  if (stats && stats->business_id_to_stars)
    empty = 0;
  return empty;
}

void start_table_iter_init_business_id_to_stars(GHashTableIter *iter,
                                                Stats stats) {
  if (!stats && !iter)
    return;
  g_hash_table_iter_init(iter, stats->business_id_to_stars);
}

// se der 0 deu null, 1 deu valor
int iter_next_table_business_id_to_stars(GHashTableIter *iter, int *stars,
                                         char **business_id) {
  int empty = 0;
  gpointer *key, *value;

  if (g_hash_table_iter_next(iter, key, value)) {
    *stars = ((StarsTuple)value)->current_average;
    // verificar
    strcpy(*business_id, (char *)key);
    empty = 1;
  } else {
    *stars = 0;
    strcpy("", *business_id);
  }

  return empty;
}

CityTuple init_city_tuple(float stars, char *business_id) {
  CityTuple tuplo = calloc(1, sizeof(struct city_tuple));
  tuplo->business_id = business_id;
  tuplo->stars = stars;
  return tuplo;
}

gint compare_stars(gconstpointer key1, gconstpointer key2, gpointer user_data) {
  return ((CityTuple)key1)->stars - ((CityTuple)key2)->stars;
}

void init_city_to_business_by_star(Stats stats) {
  if (stats)
    stats->business_id_to_stars = g_hash_table_new(g_str_hash, g_str_equal);
}

void add_city_to_business_by_star(Stats stats, char *city, char *business_id,
                                  float stars) {
  if (!stats)
    return;

  if (!stats->business_id_to_stars)
    stats->business_id_to_stars = g_hash_table_new(g_str_hash, g_str_equal);

  GSList *gs_list = g_hash_table_lookup(stats->business_id_to_stars, city);

  if (!gs_list) {
    gs_list = g_slist_alloc();
    gs_list = g_slist_append(gs_list, init_city_tuple(stars, business_id));
  } else
    gs_list = g_slist_insert_sorted_with_data(
        gs_list, init_city_tuple(stars, business_id), compare_stars, NULL);
}

void add_category_to_business_by_star(Stats stats, char *category,
                                      char *business_id, float stars) {
  if (!stats)
    return;

  if (!stats->business_id_to_stars)
    stats->business_id_to_stars = g_hash_table_new(g_str_hash, g_str_equal);

  // isto mudaria
  GSList *gs_list = g_hash_table_lookup(stats->business_id_to_stars, category);
  /* GSList *gs_list = g_hash_table_lookup(stats->categoty_to_stars, category);
   */

  if (!gs_list) {
    gs_list = g_slist_alloc();
    gs_list = g_slist_append(gs_list, init_city_tuple(stars, business_id));
  } else
    gs_list = g_slist_insert_sorted_with_data(
        gs_list, init_city_tuple(stars, business_id), compare_stars, NULL);
}
