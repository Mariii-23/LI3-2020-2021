#include "sgr.h"

#include <stdio.h>
#include <stdlib.h>

#include "Leitura.h"
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
GPtrArray* build_head(char* fields[], int N) {
    GPtrArray* field_names = g_ptr_array_sized_new(N);
    for (size_t i = 0; i < N; i++) {
        g_ptr_array_add(field_names, fields[i]);  // literals
    }
    return field_names;
}
TABLE business_info(SGR sgr, char* business_id) {
    char* query_three_fields[] = {
        "nome", "cidade", "estado", "stars", "numero_reviews"};
    TABLE table =
        new_table(build_head(query_three_fields, QUERY_THREE_FIELDS_N));

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
