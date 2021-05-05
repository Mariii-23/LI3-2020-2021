/**
 * @file sgr.c
 * @author Mariana Rodrigues, Matilde Bravo e Pedro Alves
 * @date 4 Maio 2021
 * @brief This Module is responsible to manipulated all information.
 */
#include "model/sgr.h"

#include <stdio.h>
#include <stdlib.h>

#include "model/auxiliary.h"
#include "model/businesses.h"
#include "model/leitura.h"
#include "model/reviews.h"
#include "model/stats.h"
#include "model/table.h"
#include "model/users.h"

#define QUERY_TWO_FIELDS_N 1
#define QUERY_THREE_FIELDS_N 5
#define QUERY_FOUR_FIELDS_N 2
#define QUERY_FIVE_FIELDS_N 2
#define QUERY_SIX_FIELDS_N 3
#define QUERY_SEVEN_FIELDS_N 1
#define QUERY_EIGHT_FIELDS_N 3
#define QUERY_NINE_FIELDS_N 1
#define MAX_BUFFER 100

/**
 \brief Struct that stores one sgr.
 */
struct sgr {
  UserCollection catalogo_users;
  BusinessCollection catalogo_businesses;
  ReviewCollection catalogo_reviews;
  Stats estatisticas;
};

/**
 \brief Free memory nedeed by one sgr.
 * */
void free_sgr(SGR sgr) {
  if (!sgr)
    return;
  free_businessCollection(sgr->catalogo_businesses);
  free_reviewCollection(sgr->catalogo_reviews);
  free_user_collection(sgr->catalogo_users);
  free_stats(sgr->estatisticas);
  free(sgr);
}

/* GPtrArray *build_head(char *fields[], int N) { */
/*   GPtrArray *field_names = g_ptr_array_sized_new(N); */
/*   for (size_t i = 0; i < N; i++) { */
/*     g_ptr_array_add(field_names, fields[i]); // literals */
/*   } */
/*   return field_names; */
/* } */

// TODO
bool validate_review(SGR sgr, Review review) {
  if (!review)
    return false;
  // ver se o business e o user da review exisitem
  bool b = true;
  char *bus_id = get_review_business_id(review);
  char *user_id = get_review_user_id(review);
  // ver se este getter verifica s existe ou nao
  Business bus =
      get_businessCollection_business_by_id(sgr->catalogo_businesses, bus_id);
  User user = get_user_by_id(sgr->catalogo_users, user_id);
  if (!bus || !user)
    b = false;
  free_business(bus);
  free_user(user);
  free(bus_id);
  free(user_id);
  return b;
}

// Query 1
/**
 \brief Given 3 paths to files, converts all valid lines in those files to a
sgr. There will be 3 csv(s) files that must be processed: users.csv,
business.csv and reviews.csv, each line in these files must contain a record
with the information of a user, business and review, respectively.
*/
SGR load_sgr(char *users, char *businesses, char *reviews) {

  FILE *fp_users = fopen(users, "r");
  FILE *fp_businesses = fopen(businesses, "r");
  FILE *fp_reviews = fopen(reviews, "r");
  if (!fp_users || !fp_businesses || !fp_reviews) {
    printf("Invalid file\n");
    return NULL;
  }
  SGR sgr = malloc(sizeof(struct sgr));
  Stats stats = start_statistics();
  *sgr = (struct sgr){.catalogo_users = collect_users(fp_users),
                      .catalogo_businesses = collect_businesses(fp_businesses),
                      .estatisticas = stats};

  sgr->catalogo_reviews = collect_reviews(fp_reviews, sgr),
  build_city_and_category_hash_table(sgr->catalogo_businesses,
                                     sgr->estatisticas);
  fclose(fp_users);
  fclose(fp_businesses);
  fclose(fp_reviews);

  return sgr;
}

void call_update_average_stars(SGR sgr, char *business_id, float stars) {
  update_average_stars(sgr->estatisticas, business_id, stars);
}
// Query 2
/**
 \brief Given a SGR and a letter, returns one table with all of business started
 with that give letter. */
TABLE businesses_started_by_letter(SGR sgr, char letter) {
  char *fields[] = {"Name"};
  TABLE table = new_table(fields, QUERY_TWO_FIELDS_N);
  char new_str[2];
  new_str[0] = letter;
  new_str[1] = 0;

  GPtrArray *list = get_businessCollection_business_by_letter(
      sgr->catalogo_businesses, new_str);
  int size = list->len;

  for (int i = 0; i < size; i++) {
    char *name = get_business_name(g_ptr_array_index(list, i));
    add_field(table, name);
    free(name);
  }
  char *size_str = g_strdup_printf("%d", size);
  add_footer(table, "Número total: ", size_str);
  free(size_str);

  // verificar free da list
  g_ptr_array_set_free_func(list, g_free_business);
  g_ptr_array_free(list, TRUE);
  return table;
}

// Query 3
/**
 \brief Given a SGR and a business id, returns a table with information about
 that given business. Sice we have one hash table with all business stored by
 they id, we just need to get it. After that, we just need to go get the stars
 saved in stats. */
TABLE business_info(SGR sgr, char *business_id) {
  char *query_three_fields[] = {"nome", "cidade", "estado", "stars",
                                "numero_reviews"};
  TABLE table = new_table(query_three_fields, QUERY_THREE_FIELDS_N);

  Business business = get_businessCollection_business_by_id(
      sgr->catalogo_businesses, business_id);
  if (!business)
    return table;
  char *business_name = get_business_name(business);
  char *business_city = get_business_city(business);
  char *business_state = get_business_state(business);
  add_field(table, business_name);
  add_field(table, business_city);
  add_field(table, business_state);

  added_number_stars_and_reviews_table(sgr->estatisticas, table, business_id);

  free(business_city);
  free(business_name);
  free(business_state);
  free_business(business);
  return table;
}

// Query 4
/**
 \brief Given a SGR and a user id, returns a table with information about
 all the businesses the user has reviewed.
 */
TABLE businesses_reviewed(SGR sgr, char *id) {
  char *fields[] = {"id", "nome"};
  TABLE table = new_table(fields, QUERY_FOUR_FIELDS_N);

  GPtrArray *reviews_array =
      get_reviewCollection_review_by_user_id(sgr->catalogo_reviews, id);

  if (!reviews_array) {
    add_footer(table, "Numero total de businesses:", "0");
    return table;
  }

  int size = reviews_array->len;
  for (int i = 0; i < size; i++) {
    Review review = g_ptr_array_index(reviews_array, i);
    char *business_id = get_review_business_id(review);
    Business business = get_businessCollection_business_by_id(
        sgr->catalogo_businesses, business_id);
    char *business_name = get_business_name(business);
    add_field(table, business_id);
    add_field(table, business_name);
    free(business_id);
    free(business_name);
    free_business(business);
  }

  char *size_str = g_strdup_printf("%d", size);
  add_footer(table, "Numero total de businesses:", size_str);
  free(size_str);

  g_ptr_array_set_free_func(reviews_array, (void *)free_review);
  g_ptr_array_free(reviews_array, TRUE);
  return table;
}

// Query 5
/** Creates  a table with information about all the businesses in that city
 * which have an average number of stars above the provided one.*/
TABLE businesses_with_stars_and_city(SGR sgr, float stars, char *city) {
  char *fields[] = {"id", "name", "stars"};
  TABLE table = new_table(fields, QUERY_FIVE_FIELDS_N + 1);
  n_larger_than_city_star(sgr->estatisticas, city, stars, table);
  return table;
}

// Query 6
/** Creates a table with information about the n businesses with the most stars
 * in all city.*/
TABLE top_businesses_by_city(SGR sgr, int top) {
  // tirar a cidade
  char *fields[] = {"city", "id", "name", "stars"};
  TABLE table = new_table(fields, QUERY_SIX_FIELDS_N + 1);
  all_n_larger_city_star(sgr->estatisticas, top, table);
  return table;
}

// Query 7
/** Creates a table with information with all the users that have visited more
 * than one state.*/
TABLE international_users(SGR sgr) {
  char *fields[] = {"id"};
  TABLE table = new_table(fields, QUERY_SEVEN_FIELDS_N);
  aux_international_user(sgr->catalogo_reviews, sgr->catalogo_businesses,
                         table);
  return table;
}

// Query 8
/**Creates a table with information about the n businesses with the most stars
 * in that category.*/
TABLE top_businesses_with_category(SGR sgr, int top, char *category) {
  char *fields[] = {"id", "name", "stars"};
  TABLE table = new_table(fields, QUERY_EIGHT_FIELDS_N);
  n_larger_category_star(sgr->estatisticas, category, top, table);
  return table;
}

// Query 9
/**
Creates a table with the id of all reviews which contain the given word on its
field text.*/
TABLE reviews_with_word(SGR sgr, char *word) {
  char *fields[] = {"id"};
  TABLE table = new_table(fields, QUERY_NINE_FIELDS_N);
  review_id_with_word_in_text(sgr->catalogo_reviews, word, table);
  char *size_str = g_strdup_printf("%zu", get_number_lines_table(table));
  add_footer(table, "Número total de palavras:", size_str);
  free(size_str);
  return table;
}
