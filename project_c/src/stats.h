#ifndef STATS_H
#define STATS_H

typedef struct stats* Stats;
Stats start_statistics();
double get_average_number_stars(Stats stats, char* business_id);
#endif

