#ifndef PERFECT_HASH_H
#define PERFECT_HASH_H
#include <glib.h>
#include <stdbool.h>
typedef struct phf* PerfectHash;
GPtrArray* phf_lookup(PerfectHash phf, char* key);
bool phf_add(PerfectHash phf, char* key, char* value);
void free_phf(PerfectHash phf);
#endif
