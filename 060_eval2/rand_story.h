#ifndef __RAND_STORY_H__
#define __RAND_STORY_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "provided.h"
//any functions you want your main to use
struct storyFile {
  char ** lines;
  size_t i;
};
typedef struct storyFile storyfile;
void error(char * errorMsg);
storyfile * readFile(FILE * f);
char * replace(char * previous,
               catarray_t * catarray,
               char ** record,
               size_t * record_sz,
               int sign);
category_t iniCategory(category_t category);
catarray_t * addname(catarray_t * catarray, char * lhs, char * rhs);
catarray_t * readWords(storyfile * s);
void freecatarray(catarray_t * catarray);
#endif
