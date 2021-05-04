#ifndef REVIEWS_H
#define REVIEWS_H

#include <glib.h>

#include "businesses.h"
#include "table.h"

typedef struct review *Review;
typedef struct review_collection *ReviewCollection;

Review create_review(char *review_id, char *user_id, char *business_id,
                     float stars, int useful, int funny, int cool, char *date,
                     char *text);

void review_id_with_word_in_text(ReviewCollection collection, char *word,
                                 TABLE table);

char *get_review_id(Review self);

char *get_review_user_id(Review self);

char *get_review_business_id(Review self);

float get_review_stars(Review self);

void free_review(Review self);

ReviewCollection create_review_collection();
void add_review(ReviewCollection collection, Review review);

Review get_reviewCollection_review_by_id(ReviewCollection self, char *id);

int get_number_reviews_by_business(ReviewCollection self, char *business_id);

GPtrArray *get_reviewCollection_review_by_user_id(ReviewCollection self,
                                                  char *id);

GPtrArray *get_reviewCollection_review_by_business_id(ReviewCollection self,
                                                      char *id);
void free_reviewCollection(ReviewCollection self);
void aux_international_user(ReviewCollection const review_collection,
                            BusinessCollection const business_collection,
                            TABLE table);
#endif
