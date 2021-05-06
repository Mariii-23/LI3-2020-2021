/**
 * @file perfect_hash.h
 * @author Mariana Rodrigues, Matilde Bravo e Pedro Alves
 * @date 4 Maio 2021
 * @brief This Module is responsible to manipulated all information.
 */

#ifndef PERFECT_HASH_H
#define PERFECT_HASH_H
#include <glib.h>
#include <stdbool.h>
typedef struct phf *PerfectHash;
GPtrArray *phf_lookup(PerfectHash phf, char *key);
PerfectHash phf_new();
bool phf_add(PerfectHash phf, char *key, void *value);
void phf_free(PerfectHash phf);
void phf_free_deep(PerfectHash phf, void (*free_fun)(void *));
#endif
