#include "s21_credit.h"

s21_res* s21_credit_manager(s21_info* info, char* period, char* payment) {
  s21_res* res = calloc(1, sizeof(s21_res));
  if (strncmp(period, "years", 5) == 0) {
    info->months *= 12;
  }
  if (strncmp(payment, "annually", 8) == 0) {
    res = s21_annually(info);
    res->min_pay = 0;
  } else {
    res = s21_diff(info);
  }
  return res;
}

s21_res* s21_annually(s21_info* info) {
  double i = info->interest / 12 / 100;
  double n = pow((1 + i), info->months);
  double coefficient = i * n / (n - 1);
  s21_res* res = calloc(1, sizeof(s21_res));
  double tmp = coefficient * info->sum;
  res->max_pay = round(tmp * 100) / 100;
  res->overpay = res->max_pay * info->months - info->sum;
  res->sum_total = info->sum + res->overpay;
  return res;
}

s21_res* s21_diff(s21_info* info) {
  s21_res* res = calloc(1, sizeof(s21_res));
  double net_int = 0;
  double credit_body = info->sum;
  double month_pay = info->sum / info->months;
  for (int n = 0; n < info->months; n++) {
    net_int = credit_body * info->interest / 100 / 12;
    if (n == 0) res->max_pay = net_int + month_pay;
    credit_body -= month_pay;
    res->overpay += net_int;
  }
  res->min_pay = net_int + month_pay;
  res->sum_total = info->sum + res->overpay;
  return res;
}
