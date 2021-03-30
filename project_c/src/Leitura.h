#ifndef LEITURA_H
#define LEITURA_H

#include <stdio.h>

#include "model/businesses.h"
#include "model/reviews.h"
#include "model/users.h"

UserCollection collect_users(FILE* fp);
BusinessCollection collect_businesses(FILE* fp);
ReviewCollection collect_reviews(FILE* fp);

#endif

