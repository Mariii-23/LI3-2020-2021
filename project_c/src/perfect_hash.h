#ifndef PERFECT_HASH_H
#define PERFECT_HASH_H
#include <glib.h>
#include <stdbool.h>
typedef struct phf* PerfectHash;
GPtrArray* phf_lookup(PerfectHash phf, char* key);
PerfectHash phf_new();
bool phf_add(PerfectHash phf, char* key, void* value);
void phf_free(PerfectHash phf);
#endif
