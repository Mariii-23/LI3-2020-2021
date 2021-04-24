#include "stats.h"

#include "auxiliary.h"
#include "table.h"
#include <string.h>

#include "glib.h"

typedef struct stars_tuple {
  float current_average; // current start average
  size_t number_reviews; // number of reviews read up to this point
} * StarsTuple;

// Mudar nome
typedef struct city_tuple {
  float stars; // current start average
  char *business_id;
  char *name;
} * CityTuple;

struct stats {
  GHashTable *business_id_to_stars; // updated as a new review is read,
                                    // business_id to a StarsTuple
  GHashTable
      *city_to_business_by_star; // linked list of businesse
                                 // ssorted decrescently by stars (city_tuple)
  GHashTable *category_to_business_by_star; // linked list of businesse
                                            // ssorted decrescently by category
                                            // (city_tuple)
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

/* static void build_category_hash_table(Stats stats) { */
/*   stats->business_id_to_stars = g_hash_table_new(g_str_hash,
 * g_str_equal); */
/*   // TODO */
/* } */

/* static void build_city_hash_table(Stats stats) { */
/*   stats->category_to_business_by_star = */
/*       g_hash_table_new(g_str_hash, g_str_equal); */
/*   // TODO */
/* } */

float get_average_number_stars(Stats stats, char *business_id) {
  return ((StarsTuple)g_hash_table_lookup(stats->business_id_to_stars,
                                          business_id))
      ->current_average;
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

void start_table_iter_init_business_id_hash_table(GHashTableIter *iter,
                                                  Stats stats) {
  if (!stats && !iter)
    return;
  g_hash_table_iter_init(iter, stats->business_id_to_stars);
}

// se der 0 deu null, 1 deu valor
int iter_next_table_business_id_to_stars(GHashTableIter *iter, int *stars,
                                         char **business_id) {
  int empty = 0;
  char *key = NULL;
  StarsTuple value = NULL;

  if (!stars && !business_id)
    return empty;

  if (g_hash_table_iter_next(iter, (gpointer *)&key, (gpointer *)&value)) {
    *stars = value->current_average;
    strcpy(*business_id, g_strdup(key));
    empty = 1;
  } else {
    *stars = 0;
    strcpy(*business_id, "");
  }

  return empty;
}

CityTuple init_city_tuple(float stars, char *business_id, char *name) {
  CityTuple tuplo = calloc(1, sizeof(struct city_tuple));
  tuplo->business_id = g_strdup(business_id);
  tuplo->stars = stars;
  tuplo->name = g_strdup(name);
  return tuplo;
}

CityTuple copy_city_tuple(CityTuple self) {
  CityTuple tuplo = calloc(1, sizeof(struct city_tuple));
  tuplo->business_id = g_strdup(self->business_id);
  tuplo->stars = self->stars;
  tuplo->name = g_strdup(self->name);
  return tuplo;
}

void free_city_tuple(CityTuple self) {
  free(self->business_id);
  free(self->name);
  free(self);
}

void free_g_city_tuple(gpointer data) { free_city_tuple((CityTuple)data); }

gint compare_stars(gconstpointer key1, gconstpointer key2, gpointer user_data) {
  return ((CityTuple)key1)->stars - ((CityTuple)key2)->stars;
}

void init_city_to_business_by_star(Stats stats) {
  if (stats && !stats->business_id_to_stars)
    stats->business_id_to_stars = g_hash_table_new(g_str_hash, g_str_equal);
}

void init_category_to_business_by_star(Stats stats) {
  if (stats && !stats->category_to_business_by_star)
    stats->category_to_business_by_star =
        g_hash_table_new(g_str_hash, g_str_equal);
}

void add_city_to_business_by_star(Stats stats, char *city, char *business_id,
                                  float stars, char *name) {
  if (!stats && !stats->business_id_to_stars)
    return;

  if (!stats->city_to_business_by_star)
    stats->city_to_business_by_star = g_hash_table_new(g_str_hash, g_str_equal);

  CityTuple value = init_city_tuple(stars, business_id, name);

  append_to_value(stats->city_to_business_by_star, city, value);
}

void add_category_to_business_by_star(Stats stats, char *category,
                                      char *business_id, float stars,
                                      char *name) {
  if (!stats && !stats->business_id_to_stars)
    return;

  if (!stats->category_to_business_by_star)
    stats->category_to_business_by_star =
        g_hash_table_new(g_str_hash, g_str_equal);

  CityTuple value = init_city_tuple(stars, business_id, name);
  append_to_value(stats->city_to_business_by_star, category, value);
}

static GSList *n_larger_gs_list(int N, GSList *gs_list) {
  GSList *new = gs_list = g_slist_alloc();
  int size = g_slist_length(gs_list);

  for (int i = 0; i < size && i < N; i++)
    new = g_slist_append(new, copy_city_tuple(g_slist_nth_data(gs_list, i)));

  return new;
}

static GSList *n_larger_than_gs_list(int N, GSList *gs_list) {
  GSList *new = gs_list = g_slist_alloc();
  int stop = 0;
  int size = g_slist_length(gs_list);

  for (int i = 0; !stop && i < size; i++) {
    CityTuple cont = g_slist_nth_data(gs_list, i);

    if (cont->stars < N) {
      stop = 1;
      continue;
    }
    new = g_slist_append(new, copy_city_tuple(cont));
  }
  return new;
}

void n_larger_city_star(Stats stats, char *city, int N, TABLE table,
                        int larger_than) {
  if (!stats && !stats->city_to_business_by_star)
    return;

  GSList *list =
      larger_than
          ? n_larger_than_gs_list(
                N, g_hash_table_lookup(stats->city_to_business_by_star, city))
          : n_larger_gs_list(
                N, g_hash_table_lookup(stats->city_to_business_by_star, city));

  if (!list)
    return;

  CityTuple value;
  int i = 0;

  while ((value = g_slist_nth_data(list, i)) != NULL) {
    char *id = g_strdup(value->business_id);
    char *name = value->name;
    char *stars = g_strdup_printf("%f", value->stars);

    add_field(table, id);
    add_field(table, name);
    if (larger_than == 0)
      add_field(table, stars);
    free(id);
    free(stars);
    i++;
  }
  // free do list
  g_slist_free_full(list, free_g_city_tuple);
  if (list)
    g_slist_free(list);
}

void all_n_larger_than_city_star(Stats stats, int N, TABLE table) {

  GList *all_keys = g_hash_table_get_keys(stats->city_to_business_by_star);

  int size = g_list_length(all_keys);

  for (int i = 0; i < size; i++) {
    char *city = g_strdup(g_list_nth_data(all_keys, i));
    n_larger_city_star(stats, city, N, table, 0);
    free(city);
  }
  // free all_key??
}

void n_larger_category_star(Stats stats, char *category, int N, TABLE table) {
  if (!stats && !stats->city_to_business_by_star)
    return;

  GSList *list = n_larger_gs_list(
      N, g_hash_table_lookup(stats->category_to_business_by_star, category));

  if (!list)
    return;

  CityTuple value;
  int i = 0;

  while ((value = g_slist_nth_data(list, i)) != NULL) {
    char *id = g_strdup(value->business_id);
    char *name = value->name;
    char *stars = g_strdup_printf("%f", value->stars);

    add_field(table, id);
    add_field(table, name);
    add_field(table, stars);
    free(id);
    free(stars);
    i++;
  }
  // free do list
  g_slist_free_full(list, free_g_city_tuple);
  if (list)
    g_slist_free(list);
}
