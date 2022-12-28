#include <cmath>
#include <cstdio>
#include <cstdlib>

#include "function.h"

class CountedIntFn : public Function<int, int> {
 protected:
  unsigned remaining;
  Function<int, int> * f;
  const char * mesg;

 public:
  CountedIntFn(unsigned n, Function<int, int> * fn, const char * m) :
      remaining(n), f(fn), mesg(m) {}
  virtual int invoke(int arg) {
    if (remaining == 0) {
      fprintf(stderr, "Too many function invocations in %s\n", mesg);
      exit(EXIT_FAILURE);
    }
    remaining--;
    return f->invoke(arg);
  }
};

int binarySearchForZero(Function<int, int> * f, int low, int high);

void check(Function<int, int> * f,
           int low,
           int high,
           int expected_ans,
           const char * mesg) {
  int n = high > low ? log2(high - low) + 1 : 1;
  CountedIntFn * count_f = new CountedIntFn(n, f, mesg);
  int res = binarySearchForZero(count_f, low, high);
  if (res != expected_ans) {
    fprintf(stderr, "Answers don't match!\n");
    exit(EXIT_FAILURE);
  }
}

class SinFunction : public Function<int, int> {
 public:
  //  int arg;
  // SinFunction(int arg) : arg(arg){}
  virtual int invoke(int arg) { return 10000000 * (sin(arg / 100000.0) - 0.5); }
};

class LinearFunction : public Function<int, int> {
 public:
  virtual int invoke(int arg) { return 2 * arg + 4; }
};

class QuadraticFunction : public Function<int, int> {
 public:
  virtual int invoke(int arg) { return 2 * arg * arg - 4; }
};
int main() {
  SinFunction sin_f;
  LinearFunction lf;
  QuadraticFunction qf;
  check(&sin_f, 0, 150000, 52359, "Testing sine function");
  check(&lf, -10000, -10, -11, "LF, negative range");
  check(&lf, 0, 10, 0, "LF, positive samll");
  check(&lf, 0, 1000000, 0, "positive big");
  check(&lf, 1000, 1000000, 1000, "positive biger");
  check(&lf, -100, 1000000, -2, "positive and negative");
  check(&qf, -100, 100, 1, "QuadraticFunction");
}
