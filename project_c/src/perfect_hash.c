#include "perfect_hash.h"

#include <glib.h>
#include <stdbool.h>
#define NUMBER_LETTERS 26

struct phf {
    GPtrArray** phf;
};

PerfectHash phf_new() {
    PerfectHash phf = malloc(sizeof(struct phf));
    phf->phf = calloc(NUMBER_LETTERS, sizeof(GPtrArray*));
    return phf;
}

void free_phf(PerfectHash phf) {
    for (int i = 0; i < NUMBER_LETTERS; i++) {
        g_ptr_array_free(phf->phf[i], TRUE);
    }
    free(phf);
}

static size_t hash(char* word) {
    char first = word[0];
    size_t other_chars = ('Z' % 'A') + 1;
    return (first >= 'A' && first <= 'Z') || (first >= 'a' && first <= 'z')
               ? (first % 'a') % 'A'
               : other_chars;
}

GPtrArray* phf_lookup(PerfectHash phf, char* key) {
    size_t index = hash(key);
    return phf->phf[index];
}

bool phf_add(PerfectHash phf, char* key, char* value) {
    size_t index = hash(key);
    bool is_new = false;
    GPtrArray* elem = phf->phf[index];
    if (!elem) {
        elem = g_ptr_array_new();
        phf->phf[index] = elem;
        is_new = true;
    }
    g_ptr_array_add(elem, value);
    return is_new;
}
