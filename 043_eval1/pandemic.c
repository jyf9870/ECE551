#include "pandemic.h"

#include <ctype.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

country_t parseLine(char * line) {
  //WRITE ME
  size_t mark = 0;
  size_t popCount = 0;
  country_t ans;
  char population[32];
  size_t i = 0;
  size_t j = 0;
  int start = 0;

  if (*line == '\0') {
    fprintf(stderr, "no inputs.\n");
    exit(EXIT_FAILURE);
  }

  while (line[i] != '\0') {
    if (i + 1 >= 64) {
      fprintf(stderr, "input too long\n");
      exit(EXIT_FAILURE);
    }
    if (line[i] == ',') {
      mark = i;
      break;
    }
    else {
      ans.name[i] = line[i];
    }
    i++;
  }

  ans.name[mark] = '\0';
  if (line[mark + 1] == '\0') {
    fprintf(stderr, "only name without population.\n");
    exit(EXIT_FAILURE);
  }

  if (mark == 0) {
    fprintf(stderr, "no country name input.\n");
    exit(EXIT_FAILURE);
  }

  j = mark + 1;
  while (start == 0 && line[j] == ' ') {
    j++;
  }
  start = 1;
  while (line[j] != '\0') {
    if (isdigit(line[j])) {
      population[popCount] = line[j];
    }
    else if (line[j] == '\n')
      break;
    else {
      printf("%c", line[j]);
      fprintf(stderr, "cannot recognize the population input.\n");
      exit(EXIT_FAILURE);
    }
    j++;
    popCount++;
    if (popCount == 21) {
      fprintf(stderr, "num too long.\n");
      exit(EXIT_FAILURE);
    }
  }

  population[popCount] = '\0';
  ans.population = atoll(population);
  if (ans.population == ULLONG_MAX) {
    char poptemp[32];
    uint64_t temp = 0;
    size_t numcount = 0;
    while (population[numcount + 1] != '\0') {
      poptemp[numcount] = population[numcount];
      numcount++;
    }
    poptemp[numcount] = '\0';
    temp = atoll(poptemp);
    if (population[19] != '5' || temp != 1844674407370955161) {
      fprintf(stderr, "invaild population.\n");
      exit(EXIT_FAILURE);
    }
  }

  return ans;
}

void calcRunningAvg(unsigned * data, size_t n_days, double * avg) {
  //WRITE ME
  double count = 0;
  for (size_t i = 0; i < n_days - 6; i++) {
    for (size_t j = 0; j < 7; j++) {
      count += data[i + j];
    }
    avg[i] = count / 7;
    count = 0;
  }
}
void calcCumulative(unsigned * data, size_t n_days, uint64_t pop, double * cum) {
  //WRITE ME
  double total = 0;
  for (size_t i = 0; i < n_days; i++) {
    total += data[i];
    cum[i] = total * 100000 / pop;
  }
}

void printCountryWithMax(country_t * countries,
                         size_t n_countries,
                         unsigned ** data,
                         size_t n_days) {
  //WRITE ME]
  unsigned max = 0;
  size_t coutName = 0;
  for (size_t i = 0; i < n_countries; i++) {
    for (size_t j = 0; j < n_days; j++) {
      if (data[i][j] > max) {
        max = data[i][j];
        coutName = i;
      }
    }
  }
  printf("%s has the most daily cases with %u\n", countries[coutName].name, max);
}
