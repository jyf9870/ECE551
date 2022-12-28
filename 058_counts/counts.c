#include "counts.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
counts_t * createCounts(void) {
  //WRITE ME
  counts_t * count = malloc(sizeof(*count));
  if (count == NULL) {
    fprintf(stderr, "Error in mallocing");
    exit(EXIT_FAILURE);
  }
  count->count_unkonwn = 0;
  count->len = 0;
  count->pairs = NULL;
  // count->pairs[0].count_num = 0;
  // count->pairs[0].str = NULL;
  return count;
}
void addCount(counts_t * c, const char * name) {
  //WRITE ME
  int flag = 0;
  if (name == NULL) {
    c->count_unkonwn++;
    return;
  }
  for (size_t i = 0; i < c->len; i++) {
    if (strcmp(c->pairs[i].str, name) == 0) {
      //if equal, return 0;
      c->pairs[i].count_num++;
      flag = 1;
      break;
    }
  }
  if (flag == 0) {
    c->len++;
    c->pairs = realloc(c->pairs, sizeof(*c->pairs) * c->len);
    one_count_t one_count;
    one_count.count_num = 1;
    one_count.str = strdup(name);

    c->pairs[c->len - 1] = one_count;
  }
}
void printCounts(counts_t * c, FILE * outFile) {
  //WRITE ME
  for (size_t i = 0; i < c->len; i++) {
    fprintf(outFile, "%s: %zu\n", c->pairs[i].str, c->pairs[i].count_num);
  }
  if (c->count_unkonwn != 0) {
    fprintf(outFile, "<unknown> : %zu\n", c->count_unkonwn);
  }
}

void freeCounts(counts_t * c) {
  //WRITE ME
  for (size_t i = 0; i < c->len; i++) {
    free(c->pairs[i].str);
  }
  free(c->pairs);
  free(c);
}
