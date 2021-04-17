#ifndef REVIEWS_H
#define REVIEWS_H

#include <glib.h>

#include "businesses.h"

typedef struct review *Review;
typedef struct review_collection *ReviewCollection;

Review create_review(char *review_id, char *user_id, char *business_id,
                     float stars, int useful, int funny, int cool, char *date,
                     char *text);

char *get_review_id(Review self);
void set_review_id(Review self, char *review_id);

char *get_review_user_id(Review self);
void set_review_user_id(Review self, char *user_id);

char *get_review_business_id(Review self);
void set_review_business_id(Review self, char *business_id);

float get_review_stars(Review self);
void set_review_stars(Review self, float stars);

int get_review_useful(Review self);
void set_review_useful(Review self, int useful);

int get_review_funny(Review self);
void set_review_funny(Review self, int funny);

int get_review_cool(Review self);
void set_review_cool(Review self, int cool);

char *get_review_date(Review self);
void set_review_date(Review self, char *date);

char *get_review_text(Review self);
void set_review_text(Review self, char *text);

void free_review(Review self);

ReviewCollection create_review_collection();
void add_review(ReviewCollection collection, Review review);

void set_reviewCollection_reviews(ReviewCollection self, GPtrArray *reviews);

GPtrArray *get_reviewCollection_review_by_id(ReviewCollection self, char *id);
void set_reviewCollection_by_id(ReviewCollection self, GHashTable *by_id);

GPtrArray *get_reviewCollection_review_by_user_id(ReviewCollection self,
                                                  char *id);
void set_reviewCollection_by_user(ReviewCollection self, GHashTable *by_user);

GPtrArray *get_reviewCollection_review_by_business_id(ReviewCollection self,
                                                      char *id);
void set_reviewCollection_by_business(ReviewCollection self,
                                      GHashTable *by_business);
void free_reviewCollection(ReviewCollection self);
#endif
