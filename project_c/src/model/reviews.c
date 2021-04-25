#include "reviews.h"

#include <ctype.h>
#include <glib.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

#include "auxiliary.h"
#include "businesses.h"
#include "table.h"
#include "users.h"

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
  GTree *text; // nodo(WordText *word_text, GPtrArray* indices);
};

struct review_collection {
  GHashTable *by_id;
  GHashTable *by_user_id;
  GHashTable *by_business_id;
};

bool word_in_text_review(Review review, char *word) {
  return (bool)g_tree_lookup(review->text, word);
}

void review_id_with_word_in_text(ReviewCollection collection, char *word,
                                 TABLE table) {
  GHashTableIter iter;
  gpointer id = NULL;
  gpointer review = NULL;
  g_hash_table_iter_init(&iter, collection->by_id);
  while (g_hash_table_iter_next(&iter, &id, &review)) {
    if (word_in_text_review(review, word)) {
      add_field(table, id);
    }
  }
}

static gint compare_text(gconstpointer a, gconstpointer b) {
  // dar true se tiver pontuacao no fim
  size_t len_a = ((WordText *)a)->len;
  size_t len_b = ((WordText *)b)->len;
  char *max_word;
  size_t max_len, min_len;
  if (len_a > len_b) {
    max_word = ((WordText *)a)->palavra;
    max_len = len_a;
    min_len = len_b;
  } else {
    max_word = ((WordText *)b)->palavra;
    max_len = len_b;
    min_len = len_a;
  }

  if (max_len - min_len > 1 ||
      (max_len != min_len && !ispunct(max_word[max_len - 1])))
    return false;
  else {
    return !strncasecmp(((WordText *)a)->palavra, ((WordText *)b)->palavra,
                        min_len);
  }
}

// determinar a lista de ids de reviews que referem a dada palavra no campo text
static void add_key_append_value_tree(GTree *tree, WordText *w, int index) {
  GPtrArray *arr = g_tree_search(tree, compare_text, NULL);
  int *num = malloc(sizeof(int));
  *num = index;
  if (!arr) {
    // create new node
    arr = g_ptr_array_new();
    g_tree_insert_node(tree, w, arr);
  } else {
    free(w);
  }
  g_ptr_array_add(arr, num);
}

static GTree *create_tree_text(char *text) {
  GTree *tree = g_tree_new(compare_text);
  char *token = strtok(text, " ");
  for (int i = 0; token; i++) {
    WordText *w = malloc(sizeof(struct word_text));
    *w = (WordText){.palavra = token, .len = strlen(token)};
    add_key_append_value_tree(tree, w, i);
    token = strtok(NULL, " ");
  }

  return tree;
}
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
                                .text = create_tree_text(text)};
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

  if (self->text)
    free(self->text);

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

  g_hash_table_insert(collection->by_id, review->review_id, new);
  append_to_value(collection->by_user_id, review->user_id, new);
  append_to_value(collection->by_business_id, review->business_id, new);
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
  return get_reviewCollection_review_by_business_id(self, business_id)->len;
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
