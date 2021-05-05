/**
 * @file sgr.c
 * @author Mariana Rodrigues, Matilde Bravo e Pedro Alves
 * @date 4 Maio 2021
 * ????????????????????????????????????????????????????????????????????????
 * @brief This Module is responsible to calculate and interpreted stats.
 * reviews and reviews collections.
 */
#include "model/stats.h"

#include <stdbool.h>
#include <string.h>

#include "glib.h"
#include "model/auxiliary.h"
#include "model/table.h"

typedef struct stars_tuple {
  float current_average; // current start average
  size_t number_reviews; // number of reviews read up to this point
} * StarsTuple;

// Mudar nome
typedef struct stars_node {
  float stars; // current start average
  char *business_id;
  char *name;
} * StarsNode;

struct stats {
  GHashTable *business_id_to_stars; // updated as a new review is read,
                                    // business_id to a StarsTuple
  GHashTable
      *city_to_business_by_star; // linked list of businesse
                                 // ssorted decrescently by stars (stars_node)
  GHashTable *category_to_business_by_star; // linked list of businesse
                                            // ssorted decrescently by
                                            // category (stars_node)
};

void free_stars_node(StarsNode self) {
  if (!self)
    return;
  free(self->business_id);
  free(self->name);
  free(self);
}

void free_g_stars_node(gpointer data) { free_stars_node((StarsNode)data); }

void g_free_ll(gpointer pointer) {
  GSList *ptr_list = (GSList *)pointer;
  g_slist_free_full(ptr_list, free_g_stars_node);
}

/**
 \brief Creates one stats. */
Stats start_statistics() {
  Stats stats = malloc(sizeof(struct stats));
  stats->business_id_to_stars =
      g_hash_table_new_full(g_str_hash, g_str_equal, free, free);
  stats->city_to_business_by_star = g_hash_table_new(g_str_hash, g_str_equal);
  stats->category_to_business_by_star =
      g_hash_table_new(g_str_hash, g_str_equal);
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
  if (tuplo->number_reviews == 0) {
    tuplo->number_reviews++;
    tuplo->current_average = new_star;
  } else {
    tuplo->current_average =
        ((float)((tuplo->current_average * tuplo->number_reviews) + new_star)) /
        (tuplo->number_reviews + 1);
    tuplo->number_reviews++;
  }
}

/**
 \brief Given a stats and a business id, returns his average number stars or -1
 if don't exist. */
float get_average_number_stars(Stats stats, char *business_id) {
  if (!stats || !business_id)
    return (-1);
  StarsTuple tuple = ((StarsTuple)g_hash_table_lookup(
      stats->business_id_to_stars, business_id));
  if (!tuple)
    return (-1);
  return tuple->current_average;
}

void added_number_stars_and_reviews_table(Stats const stats, TABLE table,
                                          char const *business_id) {
  if (!stats || !table || !business_id)
    return;
  StarsTuple tuple = ((StarsTuple)g_hash_table_lookup(
      stats->business_id_to_stars, business_id));

  char *numero_stars = g_strdup_printf("%f", tuple->current_average);
  char *numero_reviews = g_strdup_printf("%ld", tuple->number_reviews);

  add_field(table, numero_stars);
  add_field(table, numero_reviews);

  free(numero_reviews);
  free(numero_stars);
}

/**
 \brief Given a stats, checks if it's empty. */
bool is_empty_stats(Stats stats) {
  int empty = true;
  if (stats)
    empty = false;
  return empty;
}

/**
 \brief Given a stats, checks if the field "business_id_to_stars" is empty. */
bool is_empty_business_id_to_stars(Stats stats) {
  int empty = true;
  if (stats && stats->business_id_to_stars)
    empty = false;
  return empty;
}

void start_table_iter_init_business_id_hash_table(GHashTableIter *iter,
                                                  Stats stats) {
  if (!stats || !iter)
    return;
  g_hash_table_iter_init(iter, stats->business_id_to_stars);
}

/**
 * Creates one StarsNode */
StarsNode init_stars_node(float stars, char *business_id, char *name) {
  StarsNode tuplo = calloc(1, sizeof(struct stars_node));
  tuplo->business_id = g_strdup(business_id);
  tuplo->stars = stars;
  tuplo->name = g_strdup(name);
  return tuplo;
}

/**
 \brief Given a city tuplo, retuns a clone. */
StarsNode copy_stars_node(StarsNode self) {
  StarsNode tuplo = calloc(1, sizeof(struct stars_node));
  tuplo->business_id = g_strdup(self->business_id);
  tuplo->stars = self->stars;
  tuplo->name = g_strdup(self->name);
  return tuplo;
}

/**
 *TODO */
static void free_all_elems(gpointer key, gpointer value, gpointer user_data) {
  g_free_ll(value);
  free(key);
}

/**
 \brief Free memory nedeed by one stats.
 * */
void free_stats(Stats stats) {
  if (!stats)
    return;
  // calls function passed when created
  g_hash_table_foreach(stats->city_to_business_by_star, free_all_elems, NULL);
  g_hash_table_foreach(stats->category_to_business_by_star, free_all_elems,
                       NULL);

  g_hash_table_destroy(stats->business_id_to_stars);
  g_hash_table_destroy(stats->category_to_business_by_star);
  g_hash_table_destroy(stats->city_to_business_by_star);
  free(stats);
}

/**
 \brief Compare two City Tuplo based on number of stars. */
static gint compare_stars(gconstpointer key1, gconstpointer key2,
                          gpointer user_data) {
  return (((StarsNode)key2)->stars - ((StarsNode)key1)->stars) * 100000000;
}

/**
 \brief Given a stats, initialized the field "business_id_to_stars" */
void init_city_to_business_by_star(Stats stats) {
  if (stats && !stats->business_id_to_stars)
    stats->business_id_to_stars = g_hash_table_new(g_str_hash, g_str_equal);
}

/**
 \brief Given a stats, initialized the field "category_to_business_by_star" */
void init_category_to_business_by_star(Stats stats) {
  if (stats && !stats->category_to_business_by_star)
    stats->category_to_business_by_star =
        g_hash_table_new(g_str_hash, g_str_equal);
}

// debugging prints
void print_node(gpointer data, gpointer user_data) {
  StarsNode x = (StarsNode)data;
  printf("City %s, business : %f\n", x->name, x->stars);
}
// TODO comentario
void print_list(GSList *list) { g_slist_foreach(list, print_node, NULL); }

/**
 \brief Given a stats, information relative to City Tuple and a city, this
 function creates an City tuple with that given information and added this or
 create a new GSList*. Inserting this in our Hash Table
 ("city_to_business_by_stars"), taken in account the city given. */
static void add_city_to_business_by_star(Stats stats, char *city,
                                         char *business_id, float stars,
                                         char *name) {
  if (!stats || !stats->business_id_to_stars)
    return;

  StarsNode value = init_stars_node(stars, business_id, name);

  GSList *aux = g_hash_table_lookup(stats->city_to_business_by_star, city);

  char *key = aux ? city : g_strdup(city);

  // if aux is null,  , append will create
  aux = g_slist_insert_sorted_with_data(aux, value, compare_stars, NULL);
  g_hash_table_insert(stats->city_to_business_by_star, key, aux);
}

/**
 \brief Given a stats, information relative to City Tuple and a category, this
 function creates an City tuple with that given information and added this or
 create a new GSList*. Inserting this in our Hash Table
 ("category_to_business_by_star"), taken in account the category given. */
static void add_category_to_business_by_star(Stats stats, char *category,
                                             char *business_id, float stars,
                                             char *name) {
  if (!stats || !stats->business_id_to_stars) {
    return;
  }

  StarsNode value = init_stars_node(stars, business_id, name);

  GSList *aux =
      g_hash_table_lookup(stats->category_to_business_by_star, category);

  char *key = aux ? category : g_strdup(category);
  aux = g_slist_insert_sorted_with_data(aux, value, compare_stars, NULL);

  g_hash_table_insert(stats->category_to_business_by_star, key, aux);
}

/**
 \brief Given a business collection and a stats, this function build the fields
 named "category_to_business_by_star" and "city_to_business_by_star" on stats
 with the data on business collection. */
void build_city_and_category_hash_table(BusinessCollection const businesses,
                                        Stats stats) {
  if (!businesses || !stats || !stats->business_id_to_stars)
    return;

  GHashTableIter iter;
  char *key = NULL;
  StarsTuple value = NULL;

  g_hash_table_iter_init(&iter, stats->business_id_to_stars);
  while (g_hash_table_iter_next(&iter, (gpointer *)&key, (gpointer *)&value)) {

    if (!key)
      continue;
    char *business_id = g_strdup(key);
    float current_average = value->current_average;
    Business business =
        get_businessCollection_business_by_id(businesses, business_id);

    if (!business) {
      free(business_id);
      continue;
    }

    char *city = get_business_city(business);
    char *name = get_business_name(business);
    if (!city || !name) {
      if (city)
        free(city);
      if (name)
        free(name);
      continue;
    }

    GPtrArray *categories = get_business_categories(business);
    add_city_to_business_by_star(stats, city, business_id, current_average,
                                 name);

    int size = categories ? categories->len : 0;
    for (int i = 0; i < size; i++)
      add_category_to_business_by_star(stats, g_ptr_array_index(categories, i),
                                       business_id, current_average, name);
    free(city);
    free(name);
    free(business_id);
    free_business(business);
    if (categories) {
      if (categories->len >= 1)
        g_ptr_array_set_free_func(categories, free);
      g_ptr_array_free(categories, TRUE);
    }
  }
}

/**
 \brief Given a stats, a city, a number N and a table, this function added to
the table, the name, the business id and the stars of the N first elems on
"city_to_business_by_star" corresponding to that given city.
Note that our data struct on "city_to_business_by_star" is store in descending
order. */
void n_larger_city_star(Stats stats, char *city, int const N, TABLE table) {
  if (!stats || !stats->city_to_business_by_star) {
    return;
  }

  GSList *list = g_hash_table_lookup(stats->city_to_business_by_star, city);

  if (!list)
    return;

  StarsNode value;
  int size = g_slist_length(list);

  for (int i = 0; i < size && i < N; i++) {
    value = (StarsNode)g_slist_nth_data(list, i);

    char *id = value->business_id;
    char *name = value->name;
    char *stars = g_strdup_printf("%f", value->stars);

    add_field(table, city);
    add_field(table, id);
    add_field(table, name);
    add_field(table, stars);

    free(stars);
  }
}

/**
 \brief Given a stats, a number N and a table, this function added to
the table, the name, the business id and the stars of the N first elems on all
fields of "city_to_business_by_stars". Note that our data struct on
"city_to_business_by_star" is store in descending order. */
void all_n_larger_city_star(Stats stats, int const N, TABLE table) {
  if (!stats || !stats->city_to_business_by_star) {
    return;
  }

  GList *all_keys = g_hash_table_get_keys(stats->city_to_business_by_star);

  if (!all_keys)
    return;

  int size = g_list_length(all_keys);

  for (int i = 0; i < size; i++) {
    char *city = g_strdup(g_list_nth_data(all_keys, i));
    n_larger_city_star(stats, city, N, table);
    free(city);
  }
  g_list_free(all_keys);
}

/**
 \brief Given a stats, a category, a number N and a table, this function added
to the table, the name, the business id and the stars of all elems that have
more than N stars on that category. Note that our data struct on
"category_to_business_by_star" is store in descending order. */
void n_larger_category_star(Stats stats, char *category, int const N,
                            TABLE table) {
  if (!stats || !stats->city_to_business_by_star) {
    return;
  }

  GSList *list =
      g_hash_table_lookup(stats->category_to_business_by_star, category);

  if (!list || g_slist_length(list) < 1) {
    return;
  }

  int size = g_slist_length(list);

  StarsNode value;
  int i = 0;
  for (i = 0; i < size && i < N; i++) {

    value = (StarsNode)g_slist_nth_data(list, i);

    char *id = value->business_id;
    char *name = value->name;
    char *stars = g_strdup_printf("%f", value->stars);

    add_field(table, id);
    add_field(table, name);
    add_field(table, stars);
    free(stars);
  }

  char *size_str = g_strdup_printf("%d", i);
  add_footer(table, "Número total: ", size_str);
  // apagar
  add_field(table, size_str);
  free(size_str);
}

/**
 \brief Given a stats, a city, a number N and a table, this function added
to the table, the name, the business id and the stars of all elems that have
more than N stars on that city. Note that our data struct on
"city_to_business_by_star" is store in descending order. */
void n_larger_than_city_star(Stats stats, char *city, int const N,
                             TABLE table) {
  if (!stats || !stats->city_to_business_by_star) {
    return;
  }

  GSList *list = g_hash_table_lookup(stats->city_to_business_by_star, city);

  if (!list || g_slist_length(list) < 1) {
    return;
  }

  int size = g_slist_length(list);

  StarsNode value;
  int i, stop = 0;
  for (i = 0; i < size && !stop; i++) {

    value = (StarsNode)g_slist_nth_data(list, i);

    if (value->stars < N) {
      stop = 1;
      continue;
    }

    char *id = value->business_id;
    char *name = value->name;
    char *stars = g_strdup_printf("%f", value->stars);

    add_field(table, id);
    add_field(table, name);
    add_field(table, stars);
    free(stars);
  }

  char *size_str = g_strdup_printf("%d", i);
  add_footer(table, "Número total: ", size_str);
  // apagar
  add_field(table, size_str);
  free(size_str);
}
