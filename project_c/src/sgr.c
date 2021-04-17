#include "sgr.h"

#include <stdio.h>
#include <stdlib.h>

#include "Leitura.h"
#include "model/businesses.h"
#include "model/reviews.h"
#include "model/users.h"
#include "stats.h"
#define QUERY_TWO_FIELDS 1
#define QUERY_THREE_FIELDS 5
#define QUERY_FOUR_FIELDS 2
#define QUERY_SIX_FIELDS 3
#define MAX_BUFFER 100

struct sgr {
  UserCollection catalogo_users;
  BusinessCollection catalogo_businesses;
  ReviewCollection catalogo_reviews;
  Stats estatisticas;
};
struct table {
  GPtrArray *field_names; // Nomes dos fields, no caso de um business são os
                          // campos dos businesses que é cada coluna
  GPtrArray
      *lines; // cada linha, que neste caso seria informação sobre um business
};

// Query 1
SGR load_sgr(char *users, char *businesses, char *reviews) {
  FILE *fp_users = fopen(users, "r");
  FILE *fp_businesses = fopen(businesses, "r");
  FILE *fp_reviews = fopen(reviews, "r");
  SGR sgr = malloc(sizeof(struct sgr));
  *sgr = (struct sgr){.catalogo_users = collect_users(fp_users),
                      .catalogo_businesses = collect_businesses(fp_businesses),
                      .catalogo_reviews = collect_reviews(fp_reviews)};
  // sgr->estatisticas = calcula_estatisticas(sgr);
  fclose(fp_users);
  fclose(fp_businesses);
  fclose(fp_reviews);
  return sgr;
}

// Query 2
TABLE businesses_started_by_letter(SGR sgr, char letter) {

  TABLE table = malloc(sizeof(struct table));
  GPtrArray *field_names = g_ptr_array_sized_new(QUERY_TWO_FIELDS);
  g_ptr_array_add(field_names, "Name");
  table->field_names = field_names;

  GPtrArray *lines = g_ptr_array_sized_new(1);
  GPtrArray *list = get_businessCollection_business_by_letter(
      sgr->catalogo_businesses, &letter);

  int size = list->len;
  for (int i = 0; i < size; i++) {
    char *name = get_business_name(g_ptr_array_index(list, i));
    g_ptr_array_add(lines, name);
  }

  table->lines = lines;

  return table;
}

// Query 3
TABLE business_info(SGR sgr, char *business_id) {
  TABLE table = malloc(sizeof(struct table));
  char *fields[] = {"name", "cidade", "estado", "stars", "numero_reviews"};
  GPtrArray *field_names = g_ptr_array_sized_new(QUERY_THREE_FIELDS);
  for (size_t i = 0; i < QUERY_THREE_FIELDS; i++) {
    g_ptr_array_add(field_names, fields[i]); // literals
  }
  table->field_names = field_names;
  GPtrArray *lines = g_ptr_array_sized_new(1); // apenas um negocio
  // to change, adicao do business
  g_ptr_array_add(lines, get_businessCollection_business_by_id(
                             sgr->catalogo_businesses, business_id));
  table->lines = lines;

  return table;
}

// Query 4
TABLE bussinesses_reviewed(SGR sgr, char *id) {
  TABLE table = malloc(sizeof(struct table));

  char *fields[] = {"id", "nome"};
  GPtrArray *field_names = g_ptr_array_sized_new(QUERY_FOUR_FIELDS);
  for (size_t i = 0; i < QUERY_FOUR_FIELDS; i++) {
    g_ptr_array_add(field_names, fields[i]);
  }
  table->field_names = field_names;

  GPtrArray *lines = g_ptr_array_sized_new(1);

  GPtrArray *reviews_array =
      get_reviewCollection_review_by_user_id(sgr->catalogo_reviews, id);

  int size = reviews_array->len;
  for (int i = 0; i < size; i++) {
    Review review = g_ptr_array_index(reviews_array, i);
    // ??
    Business business = g_ptr_array_index(
        get_businessCollection_business_by_id(sgr->catalogo_businesses,
                                              get_review_business_id(review)),
        1);
    // ??
    GPtrArray *aux = g_ptr_array_sized_new(QUERY_FOUR_FIELDS);
    g_ptr_array_add(aux, get_business_id(business));
    g_ptr_array_add(aux, get_business_name(business));
    g_ptr_array_add(lines, aux);
  }
  table->lines = lines;

  return table;
}

// Query 5
TABLE businesses_with_stars_and_city(SGR sgr, float stars, char *city) {
  TABLE table = malloc(sizeof(struct table));
  GPtrArray *array_by_city =
      get_businessCollection_business_by_city(sgr->catalogo_businesses, city);

  char *fields[] = {"id", "nome", "stars"};
  GPtrArray *field_names = g_ptr_array_sized_new(QUERY_SIX_FIELDS);
  for (size_t i = 0; i < QUERY_SIX_FIELDS; i++) {
    g_ptr_array_add(field_names, fields[i]);
  }
  table->field_names = field_names;

  // ???????
  int size = array_by_city->len; // tamanho do array

  GPtrArray *lines = g_ptr_array_sized_new(0);

  for (int i = 0; i < size; i++) {
    Business business = g_ptr_array_index(array_by_city, i);
    GPtrArray *reviews = get_reviewCollection_review_by_business_id(
        sgr->catalogo_reviews, get_business_id(business));

    int size_reviews = reviews->len; // tamanho do array
    for (int j = 0; j < size_reviews; j++) {
      Review review = g_ptr_array_index(reviews, j);
      if (get_review_stars(review) >= stars) {

        GPtrArray *aux = g_ptr_array_sized_new(QUERY_SIX_FIELDS);
        g_ptr_array_add(aux, get_business_id(business));
        g_ptr_array_add(aux, get_business_name(business));

        char buf[MAX_BUFFER];
        gcvt(get_review_stars(review), MAX_BUFFER, buf);
        g_ptr_array_add(aux, buf);

        g_ptr_array_add(lines, aux);
      }
    }
  }
  table->lines = lines;

  return table;
}

// Query 6
TABLE top_businesses_by_city(SGR sgr, int top);
// Query 7
TABLE international_users(SGR sgr);
// Query 8
TABLE top_businesses_with_category(SGR sgr, int top, char *category);
// Query 9
TABLE reviews_with_word(SGR sgr, int top, char *word);
