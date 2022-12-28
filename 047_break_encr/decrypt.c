#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

int decrypt(FILE * f) {
  int c;
  int temp = -1;
  int max = 0;
  int count[26] = {0};
  while ((c = fgetc(f)) != EOF) {
    if (isalpha(c)) {
      c = tolower(c);
      c -= 'a';
      count[c]++;
    }
  }

  for (int i = 0; i < 26; i++) {
    temp = i;
    if (count[temp] >= count[max])
      max = temp;
  }
  max = max - 4;
  if (max < 0)
    max += 26;
  return max;
}

int main(int argc, char ** argv) {
  if (argc != 2) {
    fprintf(stderr, "Usage: decrypt inputFileName\n");
    return EXIT_FAILURE;
  }

  FILE * f = fopen(argv[1], "r");
  if (f == NULL) {
    perror("Could not open file");
    return EXIT_FAILURE;
  }
  printf("%d\n", decrypt(f));
  if (fclose(f) != 0) {
    perror("Failed to close the input file!");
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}
