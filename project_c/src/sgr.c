#include "sgr.h"

#include <stdio.h>
#include <stdlib.h>

#include "Leitura.h"
#include "auxiliary.h"
#include "model/businesses.h"
#include "model/reviews.h"
#include "model/stats.h"
#include "model/table.h"
#include "model/users.h"
#define QUERY_THREE_FIELDS_N 5

struct sgr {
    UserCollection catalogo_users;
    BusinessCollection catalogo_businesses;
    ReviewCollection catalogo_reviews;
    Stats estatisticas;
};

// Query 1
SGR load_sgr(char* users, char* businesses, char* reviews) {
    FILE* fp_users = fopen(users, "r");
    FILE* fp_businesses = fopen(businesses, "r");
    FILE* fp_reviews = fopen(reviews, "r");
    SGR sgr = malloc(sizeof(struct sgr));
    *sgr = (struct sgr){
        .catalogo_users = collect_users(fp_users),
        .catalogo_businesses = collect_businesses(fp_businesses),
        .catalogo_reviews = collect_reviews(fp_reviews)};
    // sgr->estatisticas = calcula_estatisticas(sgr);
    fclose(fp_users);
    fclose(fp_businesses);
    fclose(fp_reviews);
    return sgr;
}

// Query 3
TABLE business_info(SGR sgr, char* business_id) {
    char* query_three_fields[] = {
        "nome", "cidade", "estado", "stars", "numero_reviews"};
    TABLE table =
        new_table(build_ptr_array(query_three_fields, QUERY_THREE_FIELDS_N));
    Business business = get_businessCollection_business_by_id(
        sgr->catalogo_businesses, business_id);
    new_line(table);
    add_to_last_line(table, get_business_name(business));
    add_to_last_line(table, get_business_city(business));
    add_to_last_line(table, get_business_state(business));
    // get_average_number_stars(business_id);
    int numero_stars = 0;
    add_to_last_line(table, g_strdup_printf("%d", numero_stars));
    int numero_reviews =
        get_number_reviews_by_business(sgr->catalogo_reviews, business_id);
    add_to_last_line(table, g_strdup_printf("%d", numero_reviews));
    return table;
}
