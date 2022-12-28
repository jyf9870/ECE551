#include "function.h"

int binarySearchForZero(Function<int, int> * f, int low, int high) {
  if (low + 1 >= high)
    return low;
  int mid = (high - low) / 2 + low;

  int y = f->invoke(mid);
  if (y > 0) {
    return binarySearchForZero(f, low, mid);
  }
  else if (y < 0) {
    return binarySearchForZero(f, mid, high);
  }
  else {
    return mid;
  }
}
