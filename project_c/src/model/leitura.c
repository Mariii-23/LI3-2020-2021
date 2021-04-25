#include <glib.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "auxiliary.h"
#include "businesses.h"
#include "reviews.h"
#include "sgr.h"
#include "stats.h"
#include "table.h"
#include "users.h"
#define LINESIZE 100
typedef enum { BUSINESS, REVIEW, USER } Type;

char *read_line(FILE *fp) {
  char linha[LINESIZE];
  bool has_new_line = false;
  GString *dynamic_string = g_string_sized_new(LINESIZE);
  while (!has_new_line) {
    if (!fgets(linha, LINESIZE, fp))
      break;
    g_string_append(dynamic_string, linha);
    has_new_line = strchr(linha, '\n') != NULL;
  }
  // remover o new line
  if (has_new_line)
    g_string_truncate(dynamic_string, dynamic_string->len - 1);
  char *final = g_string_free(dynamic_string, FALSE);
  if (*final == '\0') {
    free(final);
    return NULL;
  }
  return final;
}

char **read_to_array(char *line, char *delim, size_t number_fields) {
  // ver se tem campos a mais ou a menos
  char *item = strtok(line, delim);
  if (!item)
    return NULL;
  char **array = malloc(sizeof(char *) * number_fields);
  array[0] = g_strdup(item);
  int i = 1;
  for (; i < number_fields; i++) {
    item = strtok(NULL, delim);
    array[i] = g_strdup(item);
  }
  if (strtok(NULL, delim)) {
    for (int j = 0; j < i; j++) {
      free(array[j]);
    }
    free(array);
    return NULL;
  }
  return array;
}

GPtrArray *read_to_ptr_array(char *line, char *delim) {
  char *item = strtok(line, delim);
  if (!item)
    return NULL;
  GPtrArray *arr = g_ptr_array_new();
  while (item) {
    g_ptr_array_add(arr, g_strdup(item));
    item = strtok(NULL, delim);
  }
  return arr;
}
// read from csv generically
static Business parse_business_line(char *str, Stats stats) {
  char *business_id = strtok(str, ";");
  char *name = strtok(NULL, ";");
  char *city = strtok(NULL, ";");
  char *state = strtok(NULL, ";");
  if (!state) {
    // nao tem campos suficientes
    return NULL;
  }
  GPtrArray *categories = NULL;
  // char* resto = ;
  // if (strchr(resto, ';')) return NULL;
  // set tiver ainda mais parametros ou o nome tiver ; ?
  categories =
      read_to_ptr_array(strtok(NULL, ";"), ","); // passar o resto da linha
  return create_business(business_id, name, city, state, categories);
}

static User parse_user_line(char *str, Stats stats) {
  char *user_id = strtok(str, ";");
  char *name = strtok(NULL, ";");
  if (!name)
    return NULL;
  GPtrArray *users = read_to_ptr_array(strtok(NULL, ";"), ",");
  return create_user(user_id, name, users);
}

static Review parse_review_line(char *str, Stats stats) {
  char *review_id = strtok(str, ";");
  char *user_id = strtok(NULL, ";");
  char *business_id = strtok(NULL, ";");
  float stars = atof(strtok(NULL, ";"));
  int useful = atoi(strtok(NULL, ";"));
  int funny = atoi(strtok(NULL, ";"));
  int cool = atoi(strtok(NULL, ";"));
  char *date = strtok(NULL, ";");
  char *text = strtok(NULL, ";");
  if (!text)
    return NULL;
  update_average_stars(stats, business_id, stars);
  return create_review(review_id, user_id, business_id, stars, useful, funny,
                       cool, date, text);
}

bool validate_review(Review review) {
  if (!review)
    return false;
  // ver se o business e o user da review exisitem
  bool b = false;
  char *bus_id = get_review_business_id(review);
  char *user_id = get_review_user_id(review);
  // ver se este getter verifica s existe ou nao
  // Business bus = get_businessCollection_business_by_id( bus_collection,
  // bus_id); User user = get_user_by_id(user_collection, char* user_id);

  // free_business(bus);
  // free_user(user);
  free(bus_id);
  free(user_id);
  return b;
}

ReviewCollection collect_reviews(FILE *fp, Stats stats) {
  printf("reviewns ca vamos nos\n");
  char *line;
  ReviewCollection collection = create_review_collection();
  // apagar
  int i = 0;
  while ((line = read_line(fp))) {
    Review review = parse_review_line(line, stats);
    free(line);
    if (!review || !validate_review(review)) {
      if (review) {
        free_review(review);
      }
      continue;
    }
    add_review(collection, review);
    // free da review
    free(review);
    printf("Review :%d\n", i++);
  }
  printf("review check\n");
  return collection;
}

BusinessCollection collect_businesses(FILE *fp, Stats stats) {
  char *line;
  BusinessCollection collection = create_business_collection();

  while ((line = read_line(fp))) {
    Business business = parse_business_line(line, stats);
    free(line);
    if (!business)
      continue;
    add_business(collection, business);
    // free do business
    free_business(business);
  }
  // apagar
  printf("business check\n");
  return collection;
}

UserCollection collect_users(FILE *fp, Stats stats) {
  char *line;
  UserCollection collection = create_user_collection();
  while ((line = read_line(fp))) {
    User user = parse_user_line(line, stats);
    free(line);
    if (!user)
      continue;
    add_user(collection, user);
    // dar free do user
    free_user(user);
  }
  // apagar
  printf("users check\n");
  return collection;
}
