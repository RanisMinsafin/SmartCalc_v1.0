#include "s21_deposit.h"

s21_result* s21_deposit_manager(s21_term* info) {
  s21_result* res = calloc(1, sizeof(s21_result));
  res->income = 0;
  if (info->frequency == DAILY) {
    res->end_sum = info->start_sum * pow(1 + info->interest / 365, info->days);
  } else if (info->frequency == MONTHLY) {
    res->end_sum = info->start_sum * pow(1 + info->interest / 12, info->months);
  } else if (info->frequency == QUARTERLY) {
    double quarters = info->months / 3;
    res->end_sum = info->start_sum * pow(1 + info->interest / 4, quarters);
  } else if (info->frequency == HALF_YEAR) {
    double half_year = info->months / 6;
    res->end_sum = info->start_sum * pow(1 + info->interest / 2, half_year);
  } else if (info->frequency == YEARLY) {
    double years = info->months / 12;
    res->end_sum = info->start_sum * pow(1 + info->interest, years);
  } else {
    res->income = (info->start_sum * info->interest * info->days / 365);
    res->end_sum = info->start_sum + res->income;
  }
  if (!res->income) res->income = res->end_sum - info->start_sum;
  s21_tax_caclulate(info, res);
  return res;
}

void s21_tax_caclulate(s21_term* info, s21_result* res) {
  if (info->interest > 0.125) {
    info->interest = 0.125;
    s21_result* clone = s21_deposit_manager(info);
    double tax_sum = res->income - clone->income;
    res->tax = tax_sum * info->tax;
    free(clone);
  } else {
    res->tax = 0;
  }
  s21_tax_add(res);
}

void s21_tax_add(s21_result* res) {
  res->end_sum -= res->income;
  res->income -= res->tax;
  res->end_sum += res->income;
}