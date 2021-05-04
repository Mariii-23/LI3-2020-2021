#include <glib.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "model/auxiliary.h"
#include "model/businesses.h"
#include "model/reviews.h"
#include "model/sgr.h"
#include "model/stats.h"
#include "model/table.h"
#include "model/users.h"
#define LINESIZE 100
#define NUMBER_REVIEW_PARAMS 9
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
    if (!item)
      break;
    array[i] = g_strdup(item);
  }
  if (!item || strtok(NULL, delim)) {
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
static Business parse_business_line(char *str) {
  char *business_id = my_strsep(&str, ";");
  char *name = my_strsep(&str, ";");
  char *city = my_strsep(&str, ";");
  char *state = my_strsep(&str, ";");
  char *categories = my_strsep(&str, ";");
  if (!categories) {
    // nao tem campos suficientes
    return NULL;
  }
  // GPtrArray *categories_array = NULL;
  // char* resto = ;
  // if (strchr(resto, ';')) return NULL;
  // set tiver ainda mais parametros ou o nome tiver ; ?
  GPtrArray *categories_array =
      read_to_ptr_array(categories, ","); // passar o resto da linha
  Business bus =
      create_business(business_id, name, city, state, categories_array);
  free_ptr_array_deep(categories_array);
  return bus;
}

static User parse_user_line(char *str) {
  char *user_id = strtok(str, ";");
  char *name = strtok(NULL, ";");

  if (!strtok(NULL, ";")) // terceiro field, amigos
    return NULL;
  /* GPtrArray *users = read_to_ptr_array(strtok(NULL, ";"), ","); */
  return create_user(user_id, name);
}

static Review parse_review_line(char *str, SGR sgr) {
  // last field may contain ; so we have to change strategy
  char *params[NUMBER_REVIEW_PARAMS] = {0};
  int i = 0;
  char *cursor = NULL;
  for (cursor = str; i < NUMBER_REVIEW_PARAMS - 1; cursor++, i++) {
    char *current = cursor;
    cursor = strchr(cursor, ';');
    if (!cursor)
      return NULL;
    *cursor = 0;
    params[i] = current;
  }
  params[i] = cursor;

  char *review_id = params[0];
  char *user_id = params[1];
  char *business_id = params[2];
  float stars = my_atof(params[3]);
  int useful = my_atoi(params[4]);
  int funny = my_atoi(params[5]);
  int cool = my_atoi(params[6]);
  char *date = params[7];
  char *text = params[8];
  if (stars == -1 || useful == -1 || funny == -1 || cool == -1) {
    return NULL;
  }
  call_update_average_stars(sgr, business_id, stars);
  return create_review(review_id, user_id, business_id, stars, useful, funny,
                       cool, date, text);
}

ReviewCollection collect_reviews(FILE *fp, SGR sgr) {
  char *line;
  ReviewCollection collection = create_review_collection();
  // read header
  read_line(fp);
  while ((line = read_line(fp))) {
    Review review = parse_review_line(line, sgr);
    free(line);
    if (!review || !validate_review(sgr, review)) {
      if (review) {
        free_review(review);
      }
      continue;
    }
    add_review(collection, review);
    // free da review
    free(review);
  }
  return collection;
}

BusinessCollection collect_businesses(FILE *fp) {
  char *line;
  BusinessCollection collection = create_business_collection();

  // read header
  read_line(fp);

  while ((line = read_line(fp))) {
    Business business = parse_business_line(line);
    free(line);
    if (!business)
      continue;
    add_business(collection, business);
    // free do business
    free_business(business);
  }
  return collection;
}

UserCollection collect_users(FILE *fp) {
  char *line;
  UserCollection collection = create_user_collection();
  // read header
  read_line(fp);
  while ((line = read_line(fp))) {
    User user = parse_user_line(line);
    free(line);
    if (!user)
      continue;
    add_user(collection, user);
    // dar free do user
    free_user(user);
  }
  return collection;
}
