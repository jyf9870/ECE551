#include <stdio.h>
#include <stdlib.h>

struct _retire_info {
  int months;
  double contribution;
  double rate_of_return;
};

typedef struct _retire_info retire_info;

void printline(int startAge, int month, double initial);
double monthInc(double initial, retire_info information);
void retirement(int startAge, double initial, retire_info working, retire_info retired);

void printline(int startAge, int month, double initial) {
  int ageYear = (startAge + month) / 12;
  int ageMonth = (startAge + month) % 12;
  printf("Age %3d month %2d you have $%.2f\n", ageYear, ageMonth, initial);
}

double monthInc(double initial, retire_info information) {
  initial = initial + initial * information.rate_of_return + information.contribution;
  return initial;
}

void retirement(int startAge, double initial, retire_info working, retire_info retired) {
  for (int i = 0; i < working.months; i++) {
    printline(startAge, i, initial);
    initial = monthInc(initial, working);
  }
  for (int i = 0; i < retired.months; i++) {
    printline(startAge + working.months, i, initial);
    initial = monthInc(initial, retired);
  }
}
int main() {
  retire_info working;
  retire_info retired;
  working.contribution = 1000;
  working.months = 489;
  working.rate_of_return = 0.045 / 12;
  retired.contribution = -4000;
  retired.months = 384;
  retired.rate_of_return = 0.01 / 12;
  retirement(327, 21345, working, retired);
  return 0;
}
