#ifndef SGR_H
#define SGR_H

#include "glib.h"
#include "model/table.h"
typedef struct sgr* SGR;

SGR init_sgr();
void free_sgr(SGR sgr);
// Query 1
SGR load_sgr(char* users, char* businesses, char* reviews);
// Query 2
TABLE businesses_started_by_letter(SGR sgr, char letter);
// Query 3
TABLE business_info(SGR sgr, char* business_id);
// Query 4
TABLE businesses_reviewed(SGR sgr, char* user_id);
// Query 5
TABLE businesses_with_stars_and_city(SGR sgr, float stars, char* city);
// Query 6
TABLE top_businesses_by_city(SGR sgr, int top);
// Query 7
TABLE international_users(SGR sgr);
// Query 8
TABLE top_businesses_with_category(SGR sgr, int top, char* category);
// Query 9
TABLE reviews_with_word(SGR sgr, int top, char* word);

#endif
