#include "sgr.h"

#include <stdio.h>
#include <stdlib.h>

#include "Leitura.h"
#include "model/businesses.h"
#include "model/reviews.h"
#include "model/users.h"
#include "stats.h"

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
    char* fields[] = {"name", "cidade", "estado", "stars", "numero_reviews"};
    size_t n_fields = sizeof(fields);
    GPtrArray* field_names = g_ptr_array_sized_new(n_fields);
    for (size_t i = 0; i < n_fields; i++) {
        g_ptr_array_add(field_names, fields[i]);  // literals
    }
    table->field_names = field_names;
    GPtrArray* lines = g_ptr_array_sized_new(1);  // apenas um negocio
    // to change, adicao do business
    g_ptr_array_add(
        lines,
        get_businessCollection_business_by_id(
            sgr->catalogo_businesses, business_id));
    table->lines = lines;

    return table;
}

