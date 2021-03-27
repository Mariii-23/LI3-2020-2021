#include "reviews.h"
#include "businesses.h"
#include "users.h"

#include <glib.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct review {
  char *review_id;
  char *user_id;
  char *business_id;

  float stars;
  int useful;
  int funny;
  int cool;

  GDateTime *date;
  char *text;
};

struct review_collection {
  GArray *reviews;
  GHashTable *by_id;
  GHashTable *by_user;
  GHashTable *by_business;
};

/* Review: builder */
Review create_review(char *review_id, char *user_id, char *business_id,
                     float stars, int useful, int funny, int cool,
                     GDateTime *date, char *text) {
  Review new_review = (Review)malloc(sizeof(struct review));
  *new_review = (struct review){.review_id = g_strdup(review_id),
                                .user_id = g_strdup(user_id),
                                .business_id = g_strdup(business_id),
                                .stars = stars,
                                .useful = useful,
                                .funny = funny,
                                .cool = cool,
                                .date = date,
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
  if (self) {
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
  if (self) {
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
  if (self) {
    self->business_id = g_strdup(business_id);
  }
}

float get_review_stars(Review self) {
  if (self) {
    return self->stars;
  } else
    return (-1);
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
    return (-1);
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
    return (-1);
}

void set_review_cool(Review self, int cool) {
  if (self) {
    self->cool = cool;
  }
}

GDateTime *get_review_date(Review self) {
  if (self)
    return self->date;
  else
    return NULL;
}

void set_review_date(Review self, GDateTime *date) {
  if (self)
    self->date = date;
}

char *get_review_text(Review self) {
  if (self) {
    return self->text;
  } else
    return NULL;
}

void set_review_text(Review self, char *text) {
  if (self) {
    self->text = g_strdup(text);
  }
}

void free_review(Review self) {
  free(self->review_id);
  free(self->user_id);
  free(self->business_id);

  // ???
  /* g_date_free(self->date); */
  free(self->date);

  free(self->text);
}

/* Review Collection */
/* Review Collection: Builder */

ReviewCollection create_review_collection(GArray *reviews, GHashTable *by_id,
                                          GHashTable *by_user,
                                          GHashTable *by_business) {
  ReviewCollection new_review_collection =
      (ReviewCollection)malloc(sizeof(struct review_collection));
  *new_review_collection =
      (struct review_collection){.reviews = reviews,
                                 .by_id = by_id,
                                 .by_user = by_user,
                                 .by_business = by_business};
  return new_review_collection;
}

/* Review Collection: Getters and setters */

GArray *get_reviewCollection_reviews(ReviewCollection self) {
  if (self)
    return self->reviews;
  else
    return NULL;
}

void set_reviewCollection_reviews(ReviewCollection self, GArray *reviews) {
  if (self)
    self->reviews = reviews;
}

GHashTable *get_reviewCollection_by_id(ReviewCollection self) {
  if (self)
    return self->by_id;
  else
    return NULL;
}

User get_reviewCollection_user_by_id(ReviewCollection self, char *id) {
  if (self)
    return g_hash_table_lookup(self->by_id, id);
  else
    return NULL;
}

void set_reviewCollection_by_id(ReviewCollection self, GHashTable *by_id) {
  if (self)
    self->by_id = by_id;
}

GHashTable *get_reviewCollection_by_user(ReviewCollection self) {
  if (self)
    return self->by_user;
  else
    return NULL;
}

// ???
User get_reviewCollection_user_by_user(ReviewCollection self, char *id) {
  if (self)
    return g_hash_table_lookup(self->by_id, id);
  else
    return NULL;
}

void set_reviewCollection_by_user(ReviewCollection self, GHashTable *by_user) {
  if (self)
    self->by_user = by_user;
}

GHashTable *get_reviewCollection_by_business(ReviewCollection self) {
  if (self)
    return self->by_business;
  else
    return NULL;
}

Business get_reviewCollection_business_by_business(ReviewCollection self,
                                                   char *id) {
  if (self)
    return g_hash_table_lookup(self->by_id, id);
  else
    return NULL;
}

void set_reviewCollection_by_business(ReviewCollection self,
                                      GHashTable *by_business) {
  if (self)
    self->by_business = by_business;
}

void free_reviewCollection(ReviewCollection self) {
  if (self) {
    g_array_free(self->reviews, TRUE);
    g_hash_table_destroy(self->by_id);
    g_hash_table_destroy(self->by_user);
    g_hash_table_destroy(self->by_business);

    //???
    free(self);
  }
}
