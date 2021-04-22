#ifndef LEITURA_H
#define LEITURA_H

#include <stdio.h>

#include "model/businesses.h"
#include "model/reviews.h"
#include "model/stats.h"
#include "model/users.h"
#include "sgr.h"

GPtrArray* read_to_array(char* line, char* delim);
char* read_line(FILE* fp);
UserCollection collect_users(FILE* fp, Stats stats);
BusinessCollection collect_businesses(FILE* fp, Stats stats);
ReviewCollection collect_reviews(FILE* fp, Stats stats);

#endif

