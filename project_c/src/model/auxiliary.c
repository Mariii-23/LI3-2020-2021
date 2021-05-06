/**
 * @file auxiliary.c
 * @author Mariana Rodrigues, Matilde Bravo e Pedro Alves
 * @date 4 Maio 2021
 * @brief This Module is responsible to manipulated all information.
 */

#include <assert.h>
#include <ctype.h>
#include <glib.h>
#include <stdio.h>
#include <stdlib.h>

#include "model/reviews.h"

void *assert_return(void *ptr) {
  assert(ptr);
  return ptr;
}
void free_key(gpointer key, gpointer value, gpointer user_data) { free(key); }

void free_key_value(gpointer key, gpointer value, gpointer user_data) {
  if (user_data) {
    g_ptr_array_free(value, TRUE);
  }
  free(key);
  free(value);
}

void append_to_value(GHashTable *hash_table, gpointer key,
                     gpointer value_to_add) {
  GPtrArray *curr = g_hash_table_lookup(hash_table, key);
  if (!curr) {
    GPtrArray *new_array = g_ptr_array_new();
    g_ptr_array_add(new_array, value_to_add);
    g_hash_table_insert(hash_table, key, new_array);
    return;
  }
  g_ptr_array_add(curr, value_to_add);
}

void *get_last_ptr(GPtrArray *array) {
  int len = array->len;
  return array->pdata[len - 1];
}

gboolean compare_first_letter(gconstpointer key1, gconstpointer key2) {
  return ((char *)key1)[0] == ((char *)key2)[0];
}

guint business_name_hash(gconstpointer word) {
  char first = ((char *)word)[0];
  size_t other_chars = ('Z' % 'A') + 1;
  return first >= 'A' && first <= 'z' ? (first % 'a') % 'A' : other_chars;
}

gpointer strdup_copy(gconstpointer src, gpointer data) { return g_strdup(src); }

GPtrArray *build_ptr_array(char *ptr_array[], int N) {
  GPtrArray *new_array = g_ptr_array_sized_new(N);
  for (size_t i = 0; i < N; i++) {
    g_ptr_array_add(new_array, g_strdup(ptr_array[i]));
  }
  return new_array;
}

char **copy_char_array(char **array, size_t n_fields) {
  char **x = malloc(sizeof(char *) * n_fields);
  for (int i = 0; i < n_fields; i++) {
    x[i] = g_strdup(array[i]);
  }
  return x;
}

void fprint_str_array(FILE *stream, GPtrArray *arr, size_t n_fields,
                      char *delim) {
  for (int i = 0; i < arr->len; i++) {
    char c[2] = "";
    char *d = delim;
    if (((i + 1) % n_fields) == 0) {
      d = "";
      c[0] = '\n';
    }
    fprintf(stream, "%s%s%s", (char *)arr->pdata[i], d, c);
  }
  if (stream != stdout && stream != stdin && stream != stderr) {
    fclose(stream);
  }
}
void free_ptr_array_deep(GPtrArray *arr) {
  if (arr) {
    g_ptr_array_set_free_func(arr, free);
    g_ptr_array_free(arr, TRUE);
  }
}

char *my_strsep(char **str, const char *delim) {
  char *begin, *end;
  begin = *str;
  if (begin == NULL)
    return NULL;
  end = begin + strcspn(begin, delim);
  if (*end) {
    *end++ = '\0';
    *str = end;
  } else
    *str = NULL;
  return begin;
}
bool is_number(char *value) {
  char *aux = value;
  bool dot = false;
  for (; *aux; aux++) {
    if (*aux == '.') {
      if (!dot && aux[1] != '\0') {
        dot = true;
      } else {
        return false;
      }
    } else {
      if (!isdigit(*aux))
        return false;
    }
  }
  return true;
}
int my_atoi(char *str) {
  if (!strcmp(str, "0")) {
    return 0;
  }
  int r = atoi(str);
  if (!r)
    return -1;
  else
    return r;
}
float my_atof(char *str) {
  if (!strcmp(str, "0.0")) {
    return 0;
  }
  int r = atoi(str);
  if (!r)
    return -1;
  else
    return r;
}

int min(int a, int b) {
  if (a < b)
    return a;
  return b;
}

int max(int a, int b) {
  if (a > b)
    return a;
  return b;
}

float min_float(float a, float b) {
  if (a < b)
    return a;
  return b;
}

float max_float(float a, float b) {
  if (a > b)
    return a;
  return b;
}

