#include <glib.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "auxiliary.h"
#include "model/businesses.h"
#include "model/reviews.h"
#include "model/users.h"
#include "perfect_hash.h"
#define LINESIZE 100

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
    if (*final == '\0') return NULL;
    return final;
}

static GPtrArray* read_to_array(char* line) {
    char* item = strtok(line, ",");
    if (!item) return NULL;
    GPtrArray* arr = g_ptr_array_new();
    while (item) {
        g_ptr_array_add(arr, g_strdup(item));
        item = strtok(NULL, ",");
    }
    return arr;
}

Business parse_business_line(char* str) {
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
    categories = read_to_array(strtok(NULL, ";"));  // passar o resto da linha
    return create_business(business_id, name, city, state, categories);
}

User parse_user_line(char* str) {
    char* user_id = strtok(str, ";");
    char* name = strtok(NULL, ";");
    if (!user_id || !name) return NULL;
    GPtrArray* users = read_to_array(strtok(NULL, ";"));
    return create_user(user_id, name, users);
}

static Review parse_review_line(char* str) {
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

ReviewCollection collect_reviews(FILE* fp) {
    char* line;
    GPtrArray* reviews = g_ptr_array_new();
    GHashTable* by_id = g_hash_table_new(g_str_hash, g_str_equal);
    GHashTable* by_user = g_hash_table_new(g_str_hash, g_str_equal);
    GHashTable* by_business_id = g_hash_table_new(g_str_hash, g_str_equal);
    while ((line = read_line(fp))) {
        Review review = parse_review_line(line);
        if (!review) continue;
        append_to_value(by_id, get_review_id(review), review);
        append_to_value(by_user, get_review_user_id(review), review);
        append_to_value(by_business_id, get_review_business_id(review), review);
        g_ptr_array_add(reviews, review);
        free(line);
    }
    return create_review_collection(reviews, by_id, by_user, by_business_id);
}

BusinessCollection collect_businesses(FILE* fp) {
    char* line;
    GPtrArray* businesses = g_ptr_array_new();
    GHashTable* by_id = g_hash_table_new(g_str_hash, g_str_equal);
    GHashTable* by_city = g_hash_table_new(g_str_hash, g_str_equal);
    PerfectHash by_letter = phf_new();
    while ((line = read_line(fp))) {
        Business business = parse_business_line(line);
        if (!business) continue;
        g_ptr_array_add(businesses, business);
        g_hash_table_insert(by_id, get_business_id(business), business);
        append_to_value(by_city, get_business_city(business), business);
        phf_add(by_letter, get_business_name(business), business);
        free(line);
    }
    return create_business_collection(businesses, by_id, by_city, by_letter);
}

UserCollection collect_users(FILE* fp) {
    char* line;
    GHashTable* by_id = g_hash_table_new(g_str_hash, g_str_equal);
    while ((line = read_line(fp))) {
        User user = parse_user_line(line);
        if (!user) continue;
        g_hash_table_insert(by_id, get_user_id(user), user);
        free(line);
    }
    return create_user_collection(by_id);
}
