
#include "rand_story.h"

int main(int argc, char ** argv) {
  if (argc != 2) {
    error("illegal input");
  }
  FILE * f = fopen(argv[1], "r");

  //initialize a pointer of input string, then find the blank and replace it with cat
  storyfile * story = readFile(f);
  for (size_t j = 0; j < story->i; j++) {
    char * temp = replace(story->lines[j], NULL, NULL, 0, 0);
    while (strcmp(temp, story->lines[j]) != 0) {
      free(story->lines[j]);
      story->lines[j] = temp;
      temp = replace(story->lines[j], NULL, NULL, 0, 0);
    }
    printf("%s", temp);
    free(temp);
  }
  free(story->lines);
  free(story);

  return EXIT_SUCCESS;
}
