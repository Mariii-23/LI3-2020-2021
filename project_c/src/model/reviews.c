/**
 * @file reviews.c
 * @author Mariana Rodrigues, Matilde Bravo e Pedro Alves
 * @date 4 Maio 2021
 * @brief This Module is responsible to manipulated all information relative a
 * reviews and reviews collections.
 */
#include "model/reviews.h"

#include <ctype.h>
#include <glib.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

#include "model/auxiliary.h"
#include "model/businesses.h"
#include "model/table.h"
#include "model/users.h"

// TODO
typedef struct word_text {
  char *palavra;
  size_t len;
} WordText;

/**
 \brief Struct that stores one review.
 */
struct review {
  char *review_id;
  char *user_id;
  char *business_id;

  float stars;
  int useful;
  int funny;
  int cool;

  char *date;
  char *text;
};

/**
 \brief Struct that stores several reviews.
 */
struct review_collection {
  GHashTable *by_id;
  GHashTable *by_user_id;
  GHashTable *by_business_id;
};

// TODO comentario
bool find_word(char *text, char *query_word) {
  // o que pode ter pontuacao é a token, a query_word nao
  // case sensitive ou nao?
  bool can_be_equal = true;
  char a = text[0];
  char b = query_word[0];
  int i = 0, j = 0;
  for (; a; i++) {
    a = text[i];
    b = query_word[j];
    // so pode ser true quando !b
    if (!b && can_be_equal && (!a || ispunct(a) || isspace(a) || a < 0))
      return true;
    else if (!a) {
      return false;
    }
    if ((!ispunct(a) && !isspace(a) && a > 0) && tolower(a) != tolower(b)) {
      can_be_equal = false;
    } else if (ispunct(a) || isspace(a) || a < 0) {
      j = 0;
      can_be_equal = true;
    } else {
      j++;
    }
  }
  return can_be_equal && !b;
}

// TODO comentario
void review_id_with_word_in_text(ReviewCollection collection, char *word,
                                 TABLE table) {
  // apagar counter
  int counter = 0;

  GHashTableIter iter;
  char *id = NULL;
  Review review = NULL;
  g_hash_table_iter_init(&iter, collection->by_id);
  while (g_hash_table_iter_next(&iter, (gpointer *)&id, (gpointer *)&review)) {
    if (find_word(review->text, word)) {
      add_field(table, id);
      // apagar
      counter++;
    }
  }

  // apagar counter
  char *size_str = g_strdup_printf("%d", counter);
  add_field(table, size_str);
  free(size_str);
}

// static gint compare_text(gconstpointer a, gconstpointer b) {
//  // dar true se tiver pontuacao no fim
//  size_t len_a = ((WordText *)a)->len;
//  size_t len_b = ((WordText *)b)->len;
//  char *max_word;
//  size_t max_len, min_len;
//  if (len_a > len_b) {
//    max_word = ((WordText *)a)->palavra;
//    max_len = len_a;
//    min_len = len_b;
//  } else {
//    max_word = ((WordText *)b)->palavra;
//    max_len = len_b;
//    min_len = len_a;
//  }
//
//  if (max_len - min_len > 1 ||
//      (max_len != min_len && !ispunct(max_word[max_len - 1])))
//    return false;
//  else {
//    return !strncasecmp(((WordText *)a)->palavra, ((WordText *)b)->palavra,
//                        min_len);
//  }
//}

// determinar a lista de ids de reviews que referem a dada palavra no campo text
// static void add_key_append_value_tree(GTree *tree, WordText *w, int index) {
//  GPtrArray *arr = g_tree_search(tree, compare_text, w);
//  int *num = malloc(sizeof(int));
//  *num = index;
//  if (!arr) {
//    // create new node
//    arr = g_ptr_array_new();
//    g_tree_insert_node(tree, w, arr);
//  } else {
//    free(w);
//  }
//  g_ptr_array_add(arr, num);
//}

// static GTree *create_tree_text(char *text) {
//  GTree *tree = g_tree_new(compare_text);
//  char *token = strtok(text, " ");
//  for (int i = 0; token; i++) {
//    WordText *w = malloc(sizeof(struct word_text));
//    *w = (WordText){.palavra = token, .len = strlen(token)};
//    add_key_append_value_tree(tree, w, i);
//    token = strtok(NULL, " ");
//  }
//
//  return tree;
//}

/**
 \brief Creates one review.
 * */
Review create_review(char *review_id, char *user_id, char *business_id,
                     float stars, int useful, int funny, int cool, char *date,
                     char *text) {
  Review new_review = (Review)malloc(sizeof(struct review));
  *new_review = (struct review){.review_id = g_strdup(review_id),
                                .user_id = g_strdup(user_id),
                                .business_id = g_strdup(business_id),
                                .stars = stars,
                                .useful = useful,
                                .funny = funny,
                                .cool = cool,
                                .date = g_strdup(date),
                                .text = g_strdup(text)};
  return new_review;
}

/* Review: getters and setters */

/**
 \brief Given a user, returns his id.
 * */
char *get_review_id(Review self) {
  if (self) {
    return g_strdup(self->review_id);
  } else
    return NULL;
}

/**
 \brief Given a user, returns his user id.
 * */
char *get_review_user_id(Review self) {
  if (self) {
    return g_strdup(self->user_id);
  } else
    return NULL;
}

/**
 \brief Given a user, returns his business id.
 * */
char *get_review_business_id(Review self) {
  if (self) {
    return g_strdup(self->business_id);
  } else
    return NULL;
}

/**
 \brief Given a user, returns his stars.
 * */
float get_review_stars(Review self) {
  if (self) {
    return self->stars;
  } else
    return -1;
}

/**
 \brief Given a review, returns a clone of him self.
 * */
static Review clone_review(Review self) {
  if (!self)
    return NULL;
  Review new_review = (Review)malloc(sizeof(struct review));
  *new_review = (struct review){.review_id = g_strdup(self->review_id),
                                .user_id = g_strdup(self->user_id),
                                .business_id = g_strdup(self->business_id),
                                .stars = self->stars,
                                .useful = self->useful,
                                .funny = self->funny,
                                .cool = self->cool,
                                .date = g_strdup(self->date),
                                .text = self->text};
  return new_review;
}

/**
 \brief Given a review, returns a clone of him self.
 * */
static gpointer g_review_copy(gconstpointer src, gpointer data) {
  return clone_review((Review)src);
}

/**
 \brief Free memory nedeed by one review.
 * */
void free_review(Review self) {
  if (!self)
    return;

  if (self->review_id)
    free(self->review_id);

  if (self->user_id)
    free(self->user_id);

  if (self->business_id)
    free(self->business_id);

  if (self->date)
    free(self->date);

  // TODO mudar
  /* if (self->text) */
  /*   free(self->text); */

  free(self);
}

/**
 \brief Free memory nedeed by one review.
 * */
void g_free_review(gpointer data) { free_review((Review)data); }

/* Review Collection */
/* Review Collection: Builder */

/**
 \brief Creates one review collection.
 * */
ReviewCollection create_review_collection() {
  ReviewCollection new_review_collection =
      (ReviewCollection)malloc(sizeof(struct review_collection));
  *new_review_collection = (struct review_collection){
      .by_id =
          g_hash_table_new_full(g_str_hash, g_str_equal, NULL, g_free_review),
      .by_user_id = g_hash_table_new(g_str_hash, g_str_equal),
      .by_business_id = g_hash_table_new(g_str_hash, g_str_equal)};
  return new_review_collection;
}

/**
 \brief Added one given review to a review collection.
 * */
void add_review(ReviewCollection collection, Review review) {
  if (!collection || !review)
    return;

  Review new = clone_review(review);
  if (!new)
    return;

  g_hash_table_insert(collection->by_id, new->review_id, new);
  append_to_value(collection->by_user_id, new->user_id, new);
  append_to_value(collection->by_business_id, new->business_id, new);
}

/**
 \brief Given a review collection and one review id, return a clone of this
 users or null in case don exists.
*/
Review get_reviewCollection_review_by_id(ReviewCollection self, char *id) {
  Review new = NULL;
  if (!self || !id)
    return new;

  Review aux = g_hash_table_lookup(self->by_id, id);
  if (aux)
    new = clone_review(aux);

  return new;
}

/**
 \brief Given a review collection and one business id, returns the number of all
 reviews made by this business.
*/
int get_number_reviews_by_business(ReviewCollection self, char *business_id) {
  if (!self || !business_id)
    return -1;
  GPtrArray *array =
      get_reviewCollection_review_by_business_id(self, business_id);
  if (!array)
    return (-1);
  return array->len;
}

/**
 \brief Given a review collection and one user id, returns a clone of all
 reviews made by this user (GPtrArray*).
*/
GPtrArray *get_reviewCollection_review_by_user_id(ReviewCollection self,
                                                  char *id) {
  GPtrArray *new = NULL;
  if (!self || !id)
    return new;

  GPtrArray *aux = g_hash_table_lookup(self->by_user_id, id);
  if (aux)
    new = g_ptr_array_copy(aux, g_review_copy, NULL);
  return new;
}

/**
 \brief Given a review collection and one business id, returns a clone of all
 reviews made by this business (GPtrArray*).
*/
GPtrArray *get_reviewCollection_review_by_business_id(ReviewCollection self,
                                                      char *id) {
  GPtrArray *new = NULL;
  if (!self || !id)
    return new;

  GPtrArray *aux = g_hash_table_lookup(self->by_business_id, id);
  if (aux)
    new = g_ptr_array_copy(aux, g_review_copy, NULL);
  return new;
}

/**
 \brief Free memory nedeed by one review collection.
 * */
void free_reviewCollection(ReviewCollection self) {
  if (self) {
    g_hash_table_destroy(self->by_id);
    g_hash_table_destroy(self->by_user_id);
    g_hash_table_destroy(self->by_business_id);
    free(self);
  }
}

/**
 \brief Given a review and a business collection and a table, added to table,
 all users id that have visited more than one state.
 */
void aux_international_user(ReviewCollection const review_collection,
                            BusinessCollection const business_collection,
                            TABLE table) {
  if (!review_collection || !business_collection || !table)
    return;

  int international_users = 0;

  GHashTableIter iter;
  gpointer key, value;

  g_hash_table_iter_init(&iter, review_collection->by_user_id);
  while (g_hash_table_iter_next(&iter, &key, &value)) {

    GPtrArray *all_reviews = (GPtrArray *)value;
    int size = all_reviews->len, count_states = 0;
    if (size <= 1)
      continue;

    char *visited_state = NULL;

    for (int i = 0; i < size && count_states < 2; i++) {
      Review review = (Review)g_ptr_array_index(all_reviews, i);
      char *business_id = review->business_id;
      char *current_state =
          get_state_by_business_id(business_collection, business_id);

      if (!visited_state || strcmp(current_state, visited_state) != 0) {
        count_states++;
      }
      free(visited_state);
      visited_state = current_state;
    }
    free(visited_state);
    if (count_states >= 2) {
      international_users++;
      add_field(table, (char *)key);
    }
  }
  char *size_str = g_strdup_printf("%d", international_users);
  add_footer(table, "Numero Total de de utilizadores:", size_str);
  free(size_str);
}
