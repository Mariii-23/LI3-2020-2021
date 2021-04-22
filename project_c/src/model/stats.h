#ifndef STATS_H
#define STATS_H

typedef struct stats* Stats;
Stats start_statistics();
float get_average_number_stars(Stats stats, char* business_id);
void update_average_stars(Stats stats, char* business_id, float new_star);
#endif

