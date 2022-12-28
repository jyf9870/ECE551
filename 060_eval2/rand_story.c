#include "rand_story.h"

//make a function to print different error messages
void error(char * errorMsg) {
  fprintf(stderr, "%s\n", errorMsg);
  exit(EXIT_FAILURE);
}

//read file line by line
storyfile * readFile(FILE * f) {
  if (f == NULL)
    error("Could not open file");

  storyfile * story = malloc(sizeof(*story));
  story->lines = NULL;
  char * curr = NULL;
  size_t sz;
  story->i = 0;
  while (getline(&curr, &sz, f) >= 0) {
    story->lines = realloc(story->lines, (story->i + 1) * sizeof(*story->lines));
    story->lines[story->i] = curr;
    curr = NULL;
    story->i++;
  }
  free(curr);
  if (fclose(f) != 0) {
    error("Could not close file");
  }
  return story;
}

//replace the "_abc_" to what we want
char * replace(char * previous,
               catarray_t * catarry,
               char ** record,
               size_t * record_sz,
               int sign) {
  char * firstC = strchr(previous, '_');

  //there is no blank
  if (firstC == NULL) {
    return previous;
  }
  size_t first = 0;
  first = firstC - previous;

  char * secondC = strchr(firstC + 1, '_');
  if (secondC == NULL) {
    error("Could not find the second _");
    return NULL;
  }
  char * category = strndup(firstC + 1, strlen(firstC) - strlen(secondC) - 1);
  const char * cat = NULL;
  if (catarry != NULL) {
    /*step3 here
  *to see if the category is a number >= 1
  *flag has 3 conditions:
  *flag = 0: vaild integer
  *flag = 1: invaild
  *flag = 2: vaild name
  */

    //flag == 0 here to ensure if all of the char of category are numbers, cause atoi() will automatically recognize input to num if the first position of the input is num.
    int flag = 0;
    if (*record_sz == 0) {
      for (size_t i = 0; i < catarry->n; i++) {
        if (strcmp(catarry->arr[i].name, category) == 0) {
          flag = 2;
          cat = chooseWord(category, catarry);
          *record_sz += 1;
          record[*record_sz - 1] = strdup(cat);
        }
      }
    }
    else {
      for (size_t i = 0; i < strlen(category); i++) {
        if (category[i] > 57 || category[i] < 48) {
          flag = 1;
          break;
          //not a legal integer
        }
      }
      if (flag == 0) {
        size_t goback = atoi(category);
        if (goback >= 1) {
          if (goback > *record_sz) {
            flag = 1;
          }
          else {
            //return the words which goes back "goback" times
            cat = record[*record_sz - goback];
            *record_sz += 1;
            record[*record_sz - 1] = strdup(cat);
          }
        }
        else {
          flag = 1;
        }
      }

      //flag == 2 if the category is a name we recorded before
      if (flag == 1) {
        for (size_t i = 0; i < catarry->n; i++) {
          if (strcmp(catarry->arr[i].name, category) == 0) {
            flag = 2;
            cat = chooseWord(category, catarry);
            *record_sz += 1;
            record[(*record_sz) - 1] = strdup(cat);
          }
        }
      }
    }
    if (flag == 1) {
      error("could not find this name!");
    }

    /*
   *step4 here
   *we add a sign to make sure if we want to remove ont of the words
   *iff we find a new name and we have the sign==1, which means we checked -n in the input, then we need to delete the word. 
   */
    if (flag == 2 && sign == 1) {
      cat = record[*record_sz - 1];
      size_t i = catarry->n - 1;
      while (strcmp(catarry->arr[i].name, category) != 0) {
        i--;
      }
      //find the position where category is same as name
      for (size_t j = 0; j < catarry->arr[i].n_words; j++) {
        if (strcmp(catarry->arr[i].words[j], record[*record_sz - 1]) == 0) {
          free(catarry->arr[i].words[j]);
          while (j + 1 < catarry->arr[i].n_words) {
            catarry->arr[i].words[j] = catarry->arr[i].words[j + 1];
            j++;
          }
          catarry->arr[i].words[catarry->arr[i].n_words - 1] = NULL;
          catarry->arr[i].n_words--;
          break;
        }
      }
    }
  }
  else {
    cat = chooseWord(category, catarry);
  }
  free(category);

  //continue step1, put together
  size_t sz = 1;
  char * res = malloc(sizeof(*res));
  for (size_t i = 0; i < first; i++) {
    res[i] = previous[i];
    res = realloc(res, sizeof(*res) * sz + 1);
    sz++;
  }
  size_t cat_len = 0;
  if (cat != NULL) {
    cat_len = strlen(cat);
  }
  for (size_t i = first; i < first + cat_len; i++) {
    res[i] = cat[i - first];
    res = realloc(res, sizeof(*res) * sz + 1);
    sz++;
  }
  const char * second = secondC + 1;
  for (size_t i = first + cat_len; i < first + cat_len + strlen(secondC); i++) {
    res[i] = second[i - first - cat_len];
    res = realloc(res, sizeof(*res) * sz + 1);
    sz++;
  }
  res[first + cat_len + strlen(secondC)] = '\0';
  return res;
}

category_t iniCategory(category_t category) {
  category.n_words = 0;
  category.name = NULL;
  return category;
}
catarray_t * addname(catarray_t * catarray, char * lhs, char * rhs) {
  catarray->n++;
  catarray->arr = realloc(catarray->arr, catarray->n * sizeof(*catarray->arr));
  catarray->arr[catarray->n - 1] = iniCategory(catarray->arr[catarray->n - 1]);
  catarray->arr[catarray->n - 1].words =
      malloc(1 * sizeof(*catarray->arr[catarray->n - 1].words));
  catarray->arr[catarray->n - 1].name = strdup(lhs);

  catarray->arr[catarray->n - 1].words[0] = strdup(rhs + 1);
  catarray->arr[catarray->n - 1].n_words++;
  return catarray;
}
catarray_t * readWords(storyfile * s) {
  catarray_t * catarray = malloc(sizeof(*catarray));
  catarray->n = 0;
  catarray->arr = NULL;
  int flag = 0;
  for (size_t j = 0; j < s->i; j++) {
    char * rhsptr = strchr(s->lines[j], ':');
    if (rhsptr == NULL) {
      error("invaild input, could not find (:)");
    }
    char * rhs = strndup(rhsptr, strlen(rhsptr) - 1);
    char * lhs = strndup(s->lines[j], rhsptr - s->lines[j]);
    if (catarray->arr == NULL) {
      //initialize category
      addname(catarray, lhs, rhs);
      free(lhs);
      free(rhs);
      free(s->lines[j]);
      continue;
    }
    for (size_t n = 0; n < catarray->n; n++) {
      if (strcmp(catarray->arr[n].name, lhs) == 0) {
        flag = 1;
        //put the rhs into words
        catarray->arr[n].n_words++;
        catarray->arr[n].words =
            realloc(catarray->arr[n].words,
                    sizeof(*catarray->arr[n].words) * catarray->arr[n].n_words);
        catarray->arr[n].words[catarray->arr[n].n_words - 1] = strdup(rhs + 1);
      }
    }
    if (flag == 0) {
      addname(catarray, lhs, rhs);
      //initialize category, new a name and add lhs into name, add rhs into words
    }
    free(lhs);
    free(rhs);
    flag = 0;
    free(s->lines[j]);
  }
  free(s->lines);
  free(s);
  return (catarray);
}

void freecatarray(catarray_t * catarray) {
  for (size_t i = 0; i < catarray->n; i++) {
    for (size_t j = 0; j < catarray->arr[i].n_words; j++) {
      free(catarray->arr[i].words[j]);
    }
    free(catarray->arr[i].name);
    free(catarray->arr[i].words);
  }
  free(catarray->arr);
  free(catarray);
}
