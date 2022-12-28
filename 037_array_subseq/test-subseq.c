#include <stdio.h>
#include <stdlib.h>

size_t maxSeq(int * array, size_t n);
int main() {
  int a[5] = {5, 2, 3, 4, 5};
  if (maxSeq(a, 5) != 4) {
    printf("errora");
    exit(EXIT_FAILURE);
  }
  int b[5] = {5, 4, 3, 2, 1};
  if (maxSeq(b, 5) != 1) {
    printf("errorb");
    exit(EXIT_FAILURE);
  }
  int c[1] = {0};
  if (maxSeq(c, 1) != 1) {
    printf("errorc");
    exit(EXIT_FAILURE);
  }
  int d[5] = {1, 2, 2, 3, 4};
  if (maxSeq(d, 5) != 3) {
    printf("errord");
    exit(EXIT_FAILURE);
  }
  int e[8] = {3, 3, 4, 5, 6, 6, 7, 8};
  if (maxSeq(e, 8) != 4) {
    printf("errore");
    exit(EXIT_FAILURE);
  }
  int f[7] = {1, 5, 6, -3, -1, 6, 10};
  if (maxSeq(f, 7) != 4) {
    printf("errorf");
    exit(EXIT_FAILURE);
  }
  int g[2] = {1, 2};
  if (maxSeq(g, 2) != 2) {
    printf("errorg");
    exit(EXIT_FAILURE);
  }
  int h[5];
  if (maxSeq(h, 0) != 0) {
    printf("errorh");
    exit(EXIT_FAILURE);
  }
  int i[10] = {1, 2, 1, 3, 5, 7, 2, 4, 6, 9};
  if (maxSeq(i, 10) != 4) {
    printf("errori");
    exit(EXIT_FAILURE);
  }
  exit(EXIT_SUCCESS);
}
