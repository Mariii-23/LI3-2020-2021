/**
 * @file leitura.h
 * @author Mariana Rodrigues, Matilde Bravo e Pedro Alves
 * @date 4 Maio 2021
 * @brief This Module is responsible to manipulated all information.
 */

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
UserCollection collect_users(FILE *fp);
BusinessCollection collect_businesses(FILE *fp);
ReviewCollection collect_reviews(FILE *fp, SGR sgr);

#endif

