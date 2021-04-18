#include "reviews.h"

#include <glib.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../auxiliary.h"
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
  GPtrArray *reviews;
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
    return self->review_id;
  } else
    return NULL;
}

void set_review_id(Review self, char *review_id) {
  if (self && review_id) {
    self->review_id = g_strdup(review_id);
  }
}

char *get_review_user_id(Review self) {
  if (self) {
    return self->user_id;
  } else
    return NULL;
}

void set_review_user_id(Review self, char *user_id) {
  if (self && user_id) {
    self->user_id = g_strdup(user_id);
  }
}

char *get_review_business_id(Review self) {
  if (self) {
    return self->business_id;
  } else
    return NULL;
}

void set_review_business_id(Review self, char *business_id) {
  if (self && business_id) {
    self->business_id = g_strdup(business_id);
  }
}

float get_review_stars(Review self) {
  if (self) {
    return self->stars;
  } else
    return -1;
}

void set_review_stars(Review self, float stars) {
  if (self) {
    self->stars = stars;
  }
}

int get_review_useful(Review self) {
  if (self) {
    return self->useful;
  } else
    return -1;
}

void set_review_useful(Review self, int useful) {
  if (self) {
    self->useful = useful;
  }
}

int get_review_funny(Review self) {
  if (self) {
    return self->funny;
  } else
    return (-1);
}

void set_review_funny(Review self, int funny) {
  if (self) {
    self->funny = funny;
  }
}

int get_review_cool(Review self) {
  if (self) {
    return self->cool;
  } else
    return -1;
}

void set_review_cool(Review self, int cool) {
  if (self) {
    self->cool = cool;
  }
}

char *get_review_date(Review self) {
  if (self)
    return self->date;
  else
    return NULL;
}

void set_review_date(Review self, char *date) {
  if (self && date)
    self->date = g_strdup(date);
}

char *get_review_text(Review self) {
  if (self) {
    return self->text;
  } else
    return NULL;
}

void set_review_text(Review self, char *text) {
  if (self && text) {
    self->text = g_strdup(text);
  }
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
      .reviews = g_ptr_array_new(),
      .by_id = g_hash_table_new(g_str_hash, g_str_equal),
      .by_user_id = g_hash_table_new(g_str_hash, g_str_equal),
      .by_business_id = g_hash_table_new(g_str_hash, g_str_equal)};
  return new_review_collection;
}

void add_review(ReviewCollection collection, Review review) {
  g_hash_table_insert(collection->by_id, get_review_id(review), review);

  append_to_value(collection->by_user_id, get_review_user_id(review), review);
  append_to_value(collection->by_business_id, get_review_business_id(review),
                  review);
  g_ptr_array_add(collection->reviews, review);
}

void set_reviewCollection_reviews(ReviewCollection self, GPtrArray *reviews) {
  if (self && reviews)
    self->reviews = reviews;
}

Review get_reviewCollection_review_by_id(ReviewCollection self, char *id) {
  if (self && id)
    return g_hash_table_lookup(self->by_id, id);
  else
    return NULL;
}

void set_reviewCollection_by_id(ReviewCollection self, GHashTable *by_id) {
  if (self && by_id)
    self->by_id = by_id;
}

GPtrArray *get_reviewCollection_review_by_user_id(ReviewCollection self,
                                                  char *id) {
  if (self && id)
    return g_hash_table_lookup(self->by_user_id, id);
  else
    return NULL;
}

void set_reviewCollection_by_user(ReviewCollection self, GHashTable *by_user) {
  if (self && by_user)
    self->by_user_id = by_user;
}

GPtrArray *get_reviewCollection_review_by_business_id(ReviewCollection self,
                                                      char *id) {
  if (self && id)
    return g_hash_table_lookup(self->by_business_id, id);
  else
    return NULL;
}

void set_reviewCollection_by_business(ReviewCollection self,
                                      GHashTable *by_business) {
  if (self && by_business)
    self->by_business_id = by_business;
}

void free_reviewCollection(ReviewCollection self) {
  if (self) {
    g_ptr_array_set_free_func(self->reviews, (void *)free_review);
    g_ptr_array_free(self->reviews, TRUE);
    g_hash_table_foreach(self->by_id, free_key, NULL);
    g_hash_table_foreach(self->by_user_id, free_key, NULL);
    g_hash_table_foreach(self->by_business_id, free_key, NULL);
    g_hash_table_destroy(self->by_id);
    g_hash_table_destroy(self->by_user_id);
    g_hash_table_destroy(self->by_business_id);
    free(self);
  }
}
