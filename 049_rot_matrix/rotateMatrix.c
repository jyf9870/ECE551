#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void rotateMatrix(FILE * f, char inputChar[10][12]) {
  char str[12];
  int x = 0;

  while ((fgets(str, 12, f)) != NULL) {
    x++;
    if (x > 10) {
      fprintf(stderr, " x error;\n");
      exit(EXIT_FAILURE);
    }

    if (strchr(str, '\n') == NULL) {
      fprintf(stderr, "y error;\n");
      exit(EXIT_FAILURE);
    }

    for (int i = 0; i < 10; i++) {
      inputChar[x - 1][i] = str[i];
    }
  }

  if (x < 10) {
    fprintf(stderr, "less than 10 rows;\n");
    exit(EXIT_FAILURE);
  }
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
  char inputChar[10][12];
  rotateMatrix(f, inputChar);

  for (int j = 0; j < 10; j++) {
    for (int i = 9; i >= 0; i--) {
      printf("%c", inputChar[i][j]);
    }
    printf("\n");
  }
  if (fclose(f) != 0) {
    perror("Failed to close the input file!");
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}
