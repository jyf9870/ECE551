#include "rand_story.h"
int main(int argc, char ** argv) {
  if (argc != 3) {
    error("illegal input");
  }
  FILE * fcata = fopen(argv[1], "r");
  FILE * fstory = fopen(argv[2], "r");
  storyfile * catStruct = readFile(fcata);
  storyfile * story = readFile(fstory);
  catarray_t * catarray = readWords(catStruct);
  char ** record = malloc(sizeof(*record));
  size_t record_sz = 0;
  for (size_t j = 0; j < story->i; j++) {
    record = realloc(record, (record_sz + 1) * sizeof(*record));
    char * temp = replace(story->lines[j], catarray, record, &record_sz, 0);
    while (strcmp(temp, story->lines[j]) != 0) {
      free(story->lines[j]);
      story->lines[j] = temp;
      record = realloc(record, (record_sz + 1) * sizeof(*record));
      temp = replace(story->lines[j], catarray, record, &record_sz, 0);
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
