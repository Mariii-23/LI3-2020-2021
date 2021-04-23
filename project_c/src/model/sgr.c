#include "sgr.h"

#include <stdio.h>
#include <stdlib.h>

#include "auxiliary.h"
#include "businesses.h"
#include "leitura.h"
#include "reviews.h"
#include "stats.h"
#include "table.h"
#include "users.h"

#define QUERY_TWO_FIELDS_N 1
#define QUERY_THREE_FIELDS_N 5
#define QUERY_FOUR_FIELDS_N 2
#define QUERY_FIVE_FIELDS_N 3
#define QUERY_SIX_FIELDS_N 3
#define QUERY_SEVEN_FIELDS_N 1
#define QUERY_EIGHT_FIELDS_N 3
#define MAX_BUFFER 100

struct sgr {
    BusinessCollection catalogo_businesses;
    ReviewCollection catalogo_reviews;
    UserCollection catalogo_users;
    Stats estatisticas;
};

GPtrArray* build_head(char* fields[], int N) {
    GPtrArray* field_names = g_ptr_array_sized_new(N);
    for (size_t i = 0; i < N; i++) {
        g_ptr_array_add(field_names, fields[i]);  // literals
    }
    return field_names;
}

// Query 1
SGR load_sgr(char* users, char* businesses, char* reviews) {
    FILE* fp_users = fopen(users, "r");
    FILE* fp_businesses = fopen(businesses, "r");
    FILE* fp_reviews = fopen(reviews, "r");
    SGR sgr = malloc(sizeof(struct sgr));
    Stats stats = start_statistics();
    *sgr = (struct sgr){
        .catalogo_businesses = collect_businesses(fp_businesses, stats),
        .catalogo_reviews = collect_reviews(fp_reviews, stats),
        .catalogo_users = collect_users(fp_users, stats),
        .estatisticas = stats};
    fclose(fp_users);
    fclose(fp_businesses);
    fclose(fp_reviews);
    return sgr;
}

// Query 2
TABLE businesses_started_by_letter(SGR sgr, char letter) {

    char* fields[] = {"Name"};
    TABLE table = new_table(build_ptr_array(fields, QUERY_TWO_FIELDS_N));
    char new_str[2];
    new_str[0] = letter;
    new_str[1] = 0;
    GPtrArray* list = get_businessCollection_business_by_letter(
        sgr->catalogo_businesses, new_str);
    int size = list->len;
    for (int i = 0; i < size; i++) {
        char* name = get_business_name(g_ptr_array_index(list, i));
        add_field(table, name);
        free(name);
    }
    // falta apresentar o size
    char* size_str = g_strdup_printf("%d", size);
    add_field(table, size_str);
    free(size_str);
    return table;
}

// Query 3
TABLE business_info(SGR sgr, char* business_id) {
    char* query_three_fields[] = {
        "nome", "cidade", "estado", "stars", "numero_reviews"};
    TABLE table =
        new_table(build_ptr_array(query_three_fields, QUERY_THREE_FIELDS_N));
    Business business = get_businessCollection_business_by_id(
        sgr->catalogo_businesses, business_id);
    char* numero_stars = g_strdup_printf(
        "%f", get_average_number_stars(sgr->estatisticas, business_id));
    char* numero_reviews = g_strdup_printf(
        "%d",
        get_number_reviews_by_business(sgr->catalogo_reviews, business_id));
    // new_line(table);
    char* business_name = get_business_name(business);
    char* business_city = get_business_city(business);
    char* business_state = get_business_state(business);
    add_field(table, business_name);
    add_field(table, business_city);
    add_field(table, business_state);
    add_field(table, numero_stars);
    add_field(table, numero_reviews);
    free(numero_reviews);
    free(numero_stars);
    free(business_city);
    free(business_name);
    free(business_state);
    return table;
}

// Query 4
TABLE bussinesses_reviewed(SGR sgr, char* id) {

    char* fields[] = {"id", "nome"};
    TABLE table = new_table(build_ptr_array(fields, QUERY_FOUR_FIELDS_N));

    GPtrArray* reviews_array =
        get_reviewCollection_review_by_user_id(sgr->catalogo_reviews, id);

    int size = reviews_array->len;
    for (int i = 0; i < size; i++) {
        Review review = g_ptr_array_index(reviews_array, i);
        char* business_id = get_review_business_id(review);
        Business business = get_businessCollection_business_by_id(
            sgr->catalogo_businesses, business_id);
        char* business_name = get_business_name(business);
        add_field(table, business_id);
        add_field(table, business_name);
        free(business_id);
        free(business_name);
        // free business quando a mariana alterar as cenas
    }

    return table;
}

// Query 5
TABLE businesses_with_stars_and_city(SGR sgr, float stars, char* city) {
    char* fields[] = {"id", "name", "stars"};
    TABLE table = new_table(build_ptr_array(fields, QUERY_FIVE_FIELDS_N));

    return table;
}

// Query 6
TABLE top_businesses_by_city(SGR sgr, int top);
// Query 7
TABLE international_users(SGR sgr);
// Query 8
TABLE top_businesses_with_category(SGR sgr, int top, char* category);
// Query 9
TABLE reviews_with_word(SGR sgr, int top, char* word);

static void build_city_hash_table(SGR sgr) {

    if (!sgr && !is_empty_stats(sgr->estatisticas) &&
        !is_empty_business_id_to_stars(sgr->estatisticas))
        return;

    init_city_to_business_by_star(sgr->estatisticas);

    GHashTableIter iter;

    start_table_iter_init_business_id_hash_table(&iter, sgr->estatisticas);

    int current_average;
    char* business_id;

    while (iter_next_table_business_id_to_stars(
        &iter, &current_average, &business_id)) {
        char* city = get_business_city(get_businessCollection_business_by_id(
            sgr->catalogo_businesses, business_id));

        add_city_to_business_by_star(
            sgr->estatisticas, city, business_id, current_average);
    }
}

static void build_category_hash_table(SGR sgr) {

    if (!sgr && !is_empty_stats(sgr->estatisticas) &&
        !is_empty_business_id_to_stars(sgr->estatisticas))
        return;

    init_category_to_business_by_star(sgr->estatisticas);

    GHashTableIter iter;
    start_table_iter_init_business_id_hash_table(&iter, sgr->estatisticas);

    int current_average;
    char* business_id;

    while (iter_next_table_business_id_to_stars(
        &iter, &current_average, &business_id)) {

        GPtrArray* categories =
            get_business_categories(get_businessCollection_business_by_id(
                sgr->catalogo_businesses, business_id));

        gint size = categories->len;
        for (int i = 0; i < size; i++)
            add_category_to_business_by_star(
                sgr->estatisticas,
                g_ptr_array_index(categories, i),
                business_id,
                current_average);
    }
}
