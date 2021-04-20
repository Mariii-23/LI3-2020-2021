#include "stats.h"

#include "glib.h"
struct stats {
    GHashTable* business_id_to_stars;
};

Stats start_statistics() {
    Stats stats = malloc(sizeof(struct stats));
    stats->business_id_to_stars = g_hash_table_new(g_str_hash, g_str_equal);
    return stats;
}
double get_average_number_stars(Stats stats, char* business_id) {
    return *(double*) g_hash_table_lookup(
        stats->business_id_to_stars, business_id);
}
