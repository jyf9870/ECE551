#include "rand_story.h"
#define SIGN "-n"
int main(int argc, char ** argv) {
  int sign = -1;
  if (argc != 3 && argc != 4)
    error("illegal input");
  if (argc == 4) {
    if (strcmp(argv[1], SIGN) != 0) {
      error("invaild input --find 3 inputs but without -n");
    }
    sign = 1;
  }
  else if (argc == 3) {
    sign = 0;
  }
  FILE * fcata = fopen(argv[1 + sign], "r");
  FILE * fstory = fopen(argv[2 + sign], "r");
  storyfile * catStruct = readFile(fcata);
  storyfile * story = readFile(fstory);
  catarray_t * catarray = readWords(catStruct);
  char ** record = malloc(sizeof(*record));
  size_t record_sz = 0;
  for (size_t j = 0; j < story->i; j++) {
    record = realloc(record, (record_sz + 1) * sizeof(*record));
    char * temp = replace(story->lines[j], catarray, record, &record_sz, sign);
    while (strcmp(temp, story->lines[j]) != 0) {
      free(story->lines[j]);
      story->lines[j] = temp;
      record = realloc(record, (record_sz + 1) * sizeof(*record));
      temp = replace(story->lines[j], catarray, record, &record_sz, sign);
    }
    printf("%s", temp);
    free(temp);
  }
  for (size_t i = 0; i < record_sz; i++) {
    free(record[i]);
  }
  free(record);
  freecatarray(catarray);
  free(story->lines);
  free(story);

  return EXIT_SUCCESS;
}
