#ifndef LEITURA_H
#define LEITURA_H

#include <stdio.h>

#include "businesses.h"
#include "reviews.h"
#include "sgr.h"
#include "stats.h"
#include "users.h"

GPtrArray *read_to_ptr_array(char *line, char *delim);
char **read_to_array(char *line, char *delim, size_t number_fields);
char *read_line(FILE *fp);
UserCollection collect_users(FILE *fp, Stats stats);
BusinessCollection collect_businesses(FILE *fp, Stats stats);
ReviewCollection collect_reviews(FILE *fp, Stats stats, SGR sgr);

#endif

