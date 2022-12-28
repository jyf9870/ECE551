#include "rand_story.h"

int main(int argc, char ** argv) {
  if (argc != 2) {
    error("illegal input");
  }
  FILE * f = fopen(argv[1], "r");
  storyfile * s = readFile(f);
  catarray_t * catarray = readWords(s);
  printWords(catarray);
  freecatarray(catarray);
  return EXIT_SUCCESS;
}
