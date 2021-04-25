#include "reviews.h"

#include <glib.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "auxiliary.h"
#include "businesses.h"
#include "users.h"

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

char *get_review_date(Review self) {
  if (self)
    return g_strdup(self->date);
  else
    return NULL;
}

char *get_review_text(Review self) {
  if (self) {
    return g_strdup(self->text);
  } else
    return NULL;
}

static Review clone_review(Review self) {
  Review new_review = (Review)malloc(sizeof(struct review));
  *new_review = (struct review){.review_id = g_strdup(self->review_id),
                                .user_id = g_strdup(self->user_id),
                                .business_id = g_strdup(self->business_id),
                                .stars = self->stars,
                                .useful = self->useful,
                                .funny = self->funny,
                                .cool = self->cool,
                                .date = g_strdup(self->date),
                                .text = g_strdup(self->text)};
  return new_review;
}

static gpointer g_review_copy(gconstpointer src, gpointer data) {
  return clone_review((Review)src);
}

void free_review(Review self) {
  free(self->review_id);
  free(self->user_id);
  free(self->business_id);
  free(self->date);
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
  g_hash_table_insert(collection->by_id, review->review_id, new);

  append_to_value(collection->by_user_id, review->user_id, new);
  append_to_value(collection->by_business_id, review->business_id, new);
  /* g_ptr_array_add(collection->reviews, new); */
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
