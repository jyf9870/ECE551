#include <stdio.h>
#include <stdlib.h>

size_t maxSeq(int * array, size_t n) {
  size_t sum = 0;
  size_t total = 1;
  if (n == 0)
    return 0;

  if (n == 1)
    return 1;
  for (size_t i = 0; i < n - 1; i++) {
    if (array[i] < array[i + 1]) {
      total++;
    }
    else {
      total = 1;
    }
    if (total > sum)
      sum = total;
  }
  return sum;
}
