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

typedef struct word_text {
  char *palavra;
  size_t len;
} WordText;

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

struct review_collection {
  GHashTable *by_id;
  GHashTable *by_user_id;
  GHashTable *by_business_id;
};

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
/* Review: builder */
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
char *get_review_id(Review self) {
  if (self) {
    return g_strdup(self->review_id);
  } else
    return NULL;
}

char *get_review_user_id(Review self) {
  if (self) {
    return g_strdup(self->user_id);
  } else
    return NULL;
}

char *get_review_business_id(Review self) {
  if (self) {
    return g_strdup(self->business_id);
  } else
    return NULL;
}

float get_review_stars(Review self) {
  if (self) {
    return self->stars;
  } else
    return -1;
}

int get_review_useful(Review self) {
  if (self) {
    return self->useful;
  } else
    return -1;
}

int get_review_funny(Review self) {
  if (self) {
    return self->funny;
  } else
    return (-1);
}

int get_review_cool(Review self) {
  if (self) {
    return self->cool;
  } else
    return -1;
}

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

static gpointer g_review_copy(gconstpointer src, gpointer data) {
  return clone_review((Review)src);
}

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

/* Review Collection */
/* Review Collection: Builder */

ReviewCollection create_review_collection() {
  ReviewCollection new_review_collection =
      (ReviewCollection)malloc(sizeof(struct review_collection));
  *new_review_collection = (struct review_collection){
      .by_id = g_hash_table_new(g_str_hash, g_str_equal),
      .by_user_id = g_hash_table_new(g_str_hash, g_str_equal),
      .by_business_id = g_hash_table_new(g_str_hash, g_str_equal)};
  return new_review_collection;
}

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

Review get_reviewCollection_review_by_id(ReviewCollection self, char *id) {
  Review new = NULL;
  if (!self || !id)
    return new;

  Review aux = g_hash_table_lookup(self->by_id, id);
  if (aux)
    new = clone_review(aux);

  return new;
}

int get_number_reviews_by_business(ReviewCollection self, char *business_id) {
  if (!self || !business_id)
    return -1;
  GPtrArray *array =
      get_reviewCollection_review_by_business_id(self, business_id);
  if (!array)
    return (-1);
  return array->len;
}

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

void free_reviewCollection(ReviewCollection self) {
  if (self) {
    g_hash_table_foreach(self->by_id, free_key, NULL);
    g_hash_table_foreach(self->by_user_id, free_key, NULL);
    g_hash_table_foreach(self->by_business_id, free_key, NULL);
    g_hash_table_destroy(self->by_id);
    g_hash_table_destroy(self->by_user_id);
    g_hash_table_destroy(self->by_business_id);
    free(self);
  }
}

static int g_array_contain(GPtrArray *array, char *string) {
  int fail = 0;
  if (!array)
    return fail;
  int size = array->len;
  for (int i = 0; i < size && !fail; i++)
    fail = strcmp((char *)g_ptr_array_index(array, i), string);
  return fail;
}

void aux_international_user(ReviewCollection review_collection,
                            BusinessCollection business_collection,
                            TABLE table) {
  if (!review_collection || !business_collection || !table)
    return;

  int count = 0;

  GHashTableIter iter;
  gpointer key, value;

  g_hash_table_iter_init(&iter, review_collection->by_user_id);
  while (g_hash_table_iter_next(&iter, &key, &value)) {

    GPtrArray *array = (GPtrArray *)value;
    int size = array->len, count_states = 1;
    if (size <= 1)
      continue;

    GPtrArray *states = g_ptr_array_new();

    Review review = (Review)g_ptr_array_index(array, 0);
    if (!review)
      continue;

    char *business_id = review->business_id;
    char *current_state =
        get_state_by_business_id(business_collection, business_id);

    g_ptr_array_add(states, g_strdup(current_state));
    free(current_state);

    for (int i = 1; i < size && count_states < 2; i++) {
      review = (Review)g_ptr_array_index(array, i);
      business_id = review->business_id;

      current_state =
          get_state_by_business_id(business_collection, business_id);

      if (g_array_contain(states, current_state)) {
        count_states++;
      } else
        g_ptr_array_add(states, current_state);
      free(current_state);
    }
    // dar free do states
    /* g_ptr_array_set_free_func(states, free); */
    g_ptr_array_free(states, TRUE);

    if (count_states >= 2) {
      count++;
      add_field(table, (char *)key);
    }
  }

  char *size_str = g_strdup_printf("%d", count);
  add_footer(table, "Numero Total de de utilizadores:", size_str);
  add_field(table, size_str);
  free(size_str);
}
