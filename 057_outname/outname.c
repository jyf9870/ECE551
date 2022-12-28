#include "outname.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char * computeOutputFileName(const char * inputName) {
  //WRITE ME
  char * res;
  size_t size = strlen(inputName);

  res = strndup(inputName, size);
  res = realloc(res, (size + 8) * sizeof(*res));
  strcpy(res + size, ".counts\0");
  return res;
}
