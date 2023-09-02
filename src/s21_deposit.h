#include <math.h>
#include <stdio.h>
#include <stdlib.h>

enum freq_nums { DAILY, MONTHLY, QUARTERLY, HALF_YEAR, YEARLY, END };

typedef struct s21_term {
  double start_sum;
  double interest;
  double tax;
  int frequency;
  int months;
  int days;
} s21_term;

typedef struct s21_result {
  int income;
  int tax;
  int end_sum;
} s21_result;

s21_result* s21_deposit_manager(s21_term* info);
void s21_tax_caclulate(s21_term* info, s21_result* res);
void s21_tax_add(s21_result* res);
