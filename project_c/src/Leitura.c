#include <glib.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "auxiliary.h"
#include "model/businesses.h"
#include "model/reviews.h"
#include "model/stats.h"
#include "model/table.h"
#include "model/users.h"
#include "perfect_hash.h"
#include "sgr.h"
#define LINESIZE 100
typedef enum { BUSINESS, REVIEW, USER } Type;

char* read_line(FILE* fp) {
    char linha[LINESIZE];
    bool has_new_line = false;
    GString* dynamic_string = g_string_sized_new(LINESIZE);
    while (!has_new_line) {
        if (!fgets(linha, LINESIZE, fp)) break;
        g_string_append(dynamic_string, linha);
        has_new_line = strchr(linha, '\n') != NULL;
    }
    // remover o new line
    if (has_new_line)
        g_string_truncate(dynamic_string, dynamic_string->len - 1);
    char* final = g_string_free(dynamic_string, FALSE);
    if (*final == '\0') {
        free(final);
        return NULL;
    }
    return final;
}

GPtrArray* read_to_array(char* line, char* delim) {
    char* item = strtok(line, delim);
    if (!item) return NULL;
    GPtrArray* arr = g_ptr_array_new();
    while (item) {
        g_ptr_array_add(arr, g_strdup(item));
        item = strtok(NULL, delim);
    }
    return arr;
}
// read from csv generically
static Business parse_business_line(char* str, Stats stats) {
    char* business_id = strtok(str, ";");
    char* name = strtok(NULL, ";");
    char* city = strtok(NULL, ";");
    char* state = strtok(NULL, ";");
    if (!business_id || !name || !city || !state) {
        return NULL;
    }
    GPtrArray* categories = NULL;
    // char* resto = ;
    // if (strchr(resto, ';')) return NULL;
    // set tiver ainda mais parametros ou o nome tiver ; ?
    categories =
        read_to_array(strtok(NULL, ";"), ",");  // passar o resto da linha
    return create_business(business_id, name, city, state, categories);
}

static User parse_user_line(char* str, Stats stats) {
    char* user_id = strtok(str, ";");
    char* name = strtok(NULL, ";");
    if (!user_id || !name) return NULL;
    GPtrArray* users = read_to_array(strtok(NULL, ";"), ",");
    return create_user(user_id, name, users);
}

static Review parse_review_line(char* str, Stats stats) {
    char* review_id = strtok(str, ";");
    char* user_id = strtok(NULL, ";");
    char* business_id = strtok(NULL, ";");
    float stars = atof(strtok(NULL, ";"));
    int useful = atoi(strtok(NULL, ";"));
    int funny = atoi(strtok(NULL, ";"));
    int cool = atoi(strtok(NULL, ";"));
    char* date = strtok(NULL, ";");
    char* text = strtok(NULL, ";");
    if (!review_id || !user_id || !business_id || !stars || !useful || !funny ||
        !cool || !date || !text)
        return NULL;
    update_average_stars(stats, business_id, stars);
    return create_review(
        review_id,
        user_id,
        business_id,
        stars,
        useful,
        funny,
        cool,
        date,
        text);
}

ReviewCollection collect_reviews(FILE* fp, Stats stats) {
    char* line;
    char* header = read_line(fp);
    ReviewCollection collection = create_review_collection();
    while ((line = read_line(fp))) {
        Review review = parse_review_line(line, stats);
        free(line);
        if (!review) continue;
        add_review(collection, review);
    }
    return collection;
}

BusinessCollection collect_businesses(FILE* fp, Stats stats) {
    char* line;
    char* header = read_line(fp);
    BusinessCollection collection = create_business_collection();
    while ((line = read_line(fp))) {
        Business business = parse_business_line(line, stats);
        free(line);
        if (!business) continue;
        add_business(collection, business);
    }
    return collection;
}

UserCollection collect_users(FILE* fp, Stats stats) {
    char* line;
    char* header = read_line(fp);
    UserCollection collection = create_user_collection();
    while ((line = read_line(fp))) {
        User user = parse_user_line(line, stats);
        free(line);
        if (!user) continue;
        add_user(collection, user);
    }
    return collection;
}
