#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "counts.h"
#include "kv.h"
#include "outname.h"

counts_t * countFile(const char * filename, kvarray_t * kvPairs) {
  //WRITE ME
  FILE * f = fopen(filename, "r");
  if (f == NULL) {
    fprintf(stderr, "Error in opening file");
    exit(EXIT_FAILURE);
  }
  counts_t * counts = createCounts();
  char * line = NULL;
  size_t sz = 0;
  while (getline(&line, &sz, f) >= 0) {
    char * position = strchr(line, '\n');
    if (position != NULL) {
      *position = '\0';
    }
    char * value = lookupValue(kvPairs, line);
    addCount(counts, value);
    free(line);
    line = NULL;
  }
  free(line);

  if (fclose(f) != 0) {
    fprintf(stderr, "Error in closing file");
    exit(EXIT_FAILURE);
  }

  return counts;
}

int main(int argc, char ** argv) {
  //WRITE ME (plus add appropriate error checking!)
  //read the key/value pairs from the file named by argv[1] (call the result kv)
  if (argc <= 2) {
    fprintf(stderr, "Please input file.\n");
    return EXIT_FAILURE;
  }

  char * fileName = argv[1];
  kvarray_t * kv = readKVs(fileName);

  //count from 2 to argc (call the number you count i)
  for (int i = 2; i < argc; i++) {
    counts_t * c = countFile(argv[i], kv);

    //count the values that appear in the file named by argv[i], using kv as the key/value pair
    //   (call this result c)

    //compute the output file name from argv[i] (call this outName)
    char * outName = computeOutputFileName(argv[i]);

    //open the file named by outName (call that f)
    FILE * f = fopen(outName, "w");
    if (f == NULL) {
      fprintf(stderr, "Error in opening file");
      exit(EXIT_FAILURE);
    }
    //print the counts from c into the FILE f
    printCounts(c, f);
    //close f
    if (fclose(f) != 0) {
      fprintf(stderr, "Error in closing file");
      exit(EXIT_FAILURE);
    }
    //free the memory for outName and c
    free(outName);
    freeCounts(c);
    //free the memory for kv
  }
  freeKVs(kv);
  return EXIT_SUCCESS;
}
