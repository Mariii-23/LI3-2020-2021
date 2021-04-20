#include "stats.h"

#include "glib.h"
typedef struct stars_tuple {
    float current_average;  // current start average
    size_t number_reviews;  // number of reviews read up to this point
} * StarsTuple;

struct stats {
    GHashTable* business_id_to_stars;      // updated as a new review is read,
                                           // business_id to a StarsTuple
    GHashTable* city_to_business_by_star;  // linked list of businesse ssorted
                                           // decrescently by stars
    GHashTable*
        category_to_business_by_star;  // linked list of businesse
                                       // ssorted decrescently by category
};

Stats start_statistics() {
    Stats stats = malloc(sizeof(struct stats));
    stats->business_id_to_stars = g_hash_table_new(g_str_hash, g_str_equal);
    return stats;
}

// when a new review is read this function is called
void update_average_stars(Stats stats, char* business_id, float new_star) {
    GHashTable* business_hash = stats->business_id_to_stars;
    StarsTuple tuplo = g_hash_table_lookup(business_hash, business_id);
    if (!tuplo) {
        tuplo = calloc(1, sizeof(struct stars_tuple));
        g_hash_table_insert(business_hash, g_strdup(business_id), tuplo);
    }
    tuplo->number_reviews++;
    tuplo->current_average =
        ((tuplo->current_average * tuplo->number_reviews) + new_star) /
        tuplo->number_reviews;
}

static void build_category_hash_table(Stats stats) {
    stats->business_id_to_stars = g_hash_table_new(g_str_hash, g_str_equal);
    // TODO
}

static void build_city_hash_table(Stats stats) {
    stats->category_to_business_by_star =
        g_hash_table_new(g_str_hash, g_str_equal);
    // TODO
}
float get_average_number_stars(Stats stats, char* business_id) {
    return *(double*) g_hash_table_lookup(
        stats->business_id_to_stars, business_id);
}
