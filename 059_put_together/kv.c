
#include "kv.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void savePair(kvpair_t * pair, char * line) {
  char * e = strchr(line, '=');
  if (e == NULL) {
    fprintf(stderr, "Error!");
    exit(EXIT_FAILURE);
  }
  size_t key_len = e - line;
  pair->key = strndup(line, key_len);
  char * next = strchr(e + 1, '\n');
  if (next != NULL) {
    size_t value_len = next - e - 1;
    pair->value = strndup(e + 1, value_len);
  }
  else {
    pair->value = strdup(e + 1);
  }
}

kvarray_t * readKVs(const char * fname) {
  //WRITE ME
  kvarray_t * results = malloc(sizeof(*results));
  if (results == NULL) {
    fprintf(stderr, "Error in malloc!");
    exit(EXIT_FAILURE);
  }
  results->hm = malloc(sizeof(*results->hm));
  if (results->hm == NULL) {
    fprintf(stderr, "Error in malloc!");
    exit(EXIT_FAILURE);
  }
  results->size = 0;
  char * line = NULL;
  size_t sz = 0;
  FILE * f = fopen(fname, "r");
  if (f == NULL) {
    fprintf(stderr, "Error in opening file!");
    exit(EXIT_FAILURE);
  }

  while (getline(&line, &sz, f) >= 0) {
    results->size++;
    results->hm = realloc(results->hm, results->size * sizeof(*results->hm));
    savePair(&results->hm[results->size - 1], line);
    free(line);
    line = NULL;
  }
  free(line);
  if (fclose(f) != 0) {
    fprintf(stderr, "Error in closing file!");
  }
  return results;
}

void freeKVs(kvarray_t * pairs) {
  //WRITE ME
  for (size_t i = 0; i < pairs->size; i++) {
    free((pairs->hm + i)->key);
    free((pairs->hm + i)->value);
  }
  free(pairs->hm);
  free(pairs);
}

void printKVs(kvarray_t * pairs) {
  for (size_t i = 0; i < pairs->size; i++) {
    printf("key = '%s' value = '%s'\n", pairs->hm[i].key, pairs->hm[i].value);
  }
  //WRITE ME
}

char * lookupValue(kvarray_t * pairs, const char * key) {
  //WRITE ME
  for (size_t i = 0; i < pairs->size; i++) {
    if (strcmp(key, pairs->hm[i].key) == 0) {
      return pairs->hm[i].value;
    }
  }
  return NULL;
}
