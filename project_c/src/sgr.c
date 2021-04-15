#include "sgr.h"

#include <stdio.h>
#include <stdlib.h>

#include "Leitura.h"
#include "model/businesses.h"
#include "model/reviews.h"
#include "model/stats.h"
#include "model/users.h"
#define QUERY_THREE_FIELDS 5

struct sgr {
    UserCollection catalogo_users;
    BusinessCollection catalogo_businesses;
    ReviewCollection catalogo_reviews;
    Stats estatisticas;
};
struct table {
    GPtrArray* field_names;  // Nomes dos fields, no caso de um business são os
                             // campos dos businesses que é cada coluna
    GPtrArray*
        lines;  // cada linha, que neste caso seria informação sobre um business
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
    TABLE table = malloc(sizeof(struct table));
    char* fields[] = {"nome", "cidade", "estado", "stars", "numero_reviews"};
    GPtrArray* field_names = g_ptr_array_sized_new(QUERY_THREE_FIELDS);
    for (size_t i = 0; i < QUERY_THREE_FIELDS; i++) {
        g_ptr_array_add(field_names, fields[i]);  // literals
    }
    table->field_names = field_names;
    GPtrArray* lines = g_ptr_array_sized_new(QUERY_THREE_FIELDS);
    Business business = get_businessCollection_business_by_id(
        sgr->catalogo_businesses, business_id);
    g_ptr_array_add(lines, get_business_name(business));
    g_ptr_array_add(lines, get_business_city(business));
    g_ptr_array_add(lines, get_business_state(business));
    // g_ptr_array_add(lines, get_average_number_stars(business_id));
    int numero_reviews =
        get_number_reviews_by_business(sgr->catalogo_reviews, business_id);
    g_ptr_array_add(lines, g_strdup_printf("%d", numero_reviews));
    table->lines = lines;
    return table;
}
