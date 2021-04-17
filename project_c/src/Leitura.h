#ifndef LEITURA_H
#define LEITURA_H

#include <stdio.h>

#include "model/businesses.h"
#include "model/reviews.h"
#include "model/users.h"
#include "sgr.h"

UserCollection collect_users(FILE* fp);
BusinessCollection collect_businesses(FILE* fp);
ReviewCollection collect_reviews(FILE* fp);
TABLE from_csv(char* filename, char* delim);

#endif

