#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct s21_info {
  double sum;
  double months;
  double interest;
} s21_info;

typedef struct s21_res {
  double max_pay;
  double min_pay;
  double overpay;
  double sum_total;
} s21_res;

// void s21_output(s21_res* s21_res);
s21_res* s21_annually(s21_info* info);
s21_res* s21_diff(s21_info* info);
s21_res* s21_credit_manager(s21_info* s21_info, char* period, char* payment);