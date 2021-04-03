#include <glib.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "auxiliary.h"
#include "model/businesses.h"
#include "model/reviews.h"
#include "model/users.h"
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
        add_to_hash_arr(by_id, get_review_id(review), review);
        add_to_hash_arr(by_user, get_review_user_id(review), review);
        add_to_hash_arr(by_business_id, get_review_business_id(review), review);
        g_ptr_array_add(reviews, review);
    }
    return create_review_collection(reviews, by_id, by_user, by_business_id);
}

BusinessCollection collect_businesses(FILE* fp) {
    char* line;
    GPtrArray* businesses = g_ptr_array_new();
    GHashTable* by_id = g_hash_table_new(g_str_hash, g_str_equal);
    GHashTable* by_city = g_hash_table_new(g_str_hash, g_str_equal);
    /* GHashTable* by_name = g_hash_table_new(g_str_hash, g_str_equal); */
    GTree* by_name = g_tree_new((GCompareFunc) g_ascii_strcasecmp);
    while ((line = read_line(fp))) {
        Business business = parse_business_line(line);
        g_ptr_array_add(businesses, business);
        add_to_hash_arr(by_id, get_business_id(business), business);
        add_to_hash_arr(by_city, get_business_city(business), business);
        /* g_hash_table_insert(by_name, get_business_name(business), business);
         */
        g_tree_insert(by_name, get_business_name(business), business);
    }
    return create_business_collection(businesses, by_id, by_city, by_name);
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
