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

static char* read_line(FILE* fp) {
    char linha[LINESIZE];
    bool has_new_line = false;
    GString* dynamic_string = g_string_sized_new(LINESIZE);
    while (!has_new_line) {
        if (!fgets(linha, LINESIZE, fp)) return NULL;
        g_string_append(dynamic_string, linha);
        has_new_line = strchr(linha, '\n') != NULL;
    }
    g_string_append_unichar(dynamic_string, 0);  // to change
    return g_string_free(dynamic_string, FALSE);
}

static GPtrArray* read_to_array(char* line) {
    GPtrArray* arr = g_ptr_array_new();
    char* item = strtok(line, ",");
    while (item) {
        g_ptr_array_add(arr, g_strdup(item));
        item = strtok(NULL, ",");
    }
    return arr;
}

static Business parse_business_line(char* str) {
    char* business_id = strtok(str, ";");
    char* name = strtok(NULL, ";");
    char* city = strtok(NULL, ";");
    char* state = strtok(NULL, ";");
    GPtrArray* categories =
        read_to_array(strtok(NULL, ";"));  // passar o resto da linha
    return create_business(business_id, name, city, state, categories);
}

static User parse_user_line(char* str) {
    char* user_id = strtok(str, ";");
    char* name = strtok(NULL, ";");
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
        printf("%s", line);
        Review review = parse_review_line(line);
        append_to_value(by_id, get_review_id(review), review);
        append_to_value(by_user, get_review_user_id(review), review);
        append_to_value(by_business_id, get_review_business_id(review), review);
        g_ptr_array_add(reviews, review);
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
        g_ptr_array_add(businesses, business);
        g_hash_table_insert(by_id, get_business_id(business), business);
        append_to_value(by_city, get_business_city(business), business);
        phf_add(by_letter, get_business_name(business), business);
    }
    return create_business_collection(businesses, by_id, by_city, by_letter);
}

UserCollection collect_users(FILE* fp) {
    char* line;
    GHashTable* by_id = g_hash_table_new(g_str_hash, g_str_equal);
    while ((line = read_line(fp))) {
        User usr = parse_user_line(line);
        g_hash_table_insert(by_id, get_user_id(usr), usr);
    }
    return create_user_collection(by_id);
}
