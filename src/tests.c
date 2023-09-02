#include <check.h>
#include <stdio.h>
#include <string.h>

#include "s21_smartcalc.h"

START_TEST(Test_1) {
  char string[100] = "(2+3)*5^2\0";
  char letter[20] = "0\0";
  s21_list_t *list = s21_smartcalc_manager(string, letter);
  int error_target = list->type;
  long double result = list->value;
  ck_assert_float_eq(result, 125.0);
  ck_assert_int_eq(error_target, 0);
  while (list) s21_pop_from(&list);
}
END_TEST

START_TEST(Test_2) {
  char string[100] = "1/2+(2+3)/(sin(9-2)^2-6/7)";
  char letter[20] = "0";
  s21_list_t *list = s21_smartcalc_manager(string, letter);
  int error_target = list->type;
  long double result = list->value;
  ck_assert_float_eq(result, -11.250565);
  ck_assert_int_eq(error_target, 0);
  while (list) s21_pop_from(&list);
}
END_TEST

START_TEST(Test_3) {
  char string[100] = "(-12.3)+4";
  char letter[20] = "0";
  s21_list_t *list = s21_smartcalc_manager(string, letter);
  int error_target = list->type;
  long double result = list->value;
  ck_assert_float_eq(result, -8.3);
  ck_assert_int_eq(error_target, 0);
  while (list) s21_pop_from(&list);
}
END_TEST

START_TEST(Test_4) {
  char string[100] = "(12)+(-12.00006)";
  char letter[20] = "0";
  s21_list_t *list = s21_smartcalc_manager(string, letter);
  int error_target = list->type;
  long double result = list->value;
  ck_assert_float_eq(result, -0.00006);
  ck_assert_int_eq(error_target, 0);
  while (list) s21_pop_from(&list);
}
END_TEST

START_TEST(Test_5) {
  char string[100] = "(-(-(-10)))-(-(-10))";
  char letter[20] = "0";
  s21_list_t *list = s21_smartcalc_manager(string, letter);
  int error_target = list->type;
  long double result = list->value;
  ck_assert_float_eq(result, -20);
  ck_assert_int_eq(error_target, 0);
  while (list) s21_pop_from(&list);
}
END_TEST

START_TEST(Test_6) {
  char string[100] = "(-1.2)-1.2-2.4-4.8";
  char letter[20] = "0";
  s21_list_t *list = s21_smartcalc_manager(string, letter);
  int error_target = list->type;
  long double result = list->value;
  ck_assert_float_eq(result, -9.6);
  ck_assert_int_eq(error_target, 0);
  while (list) s21_pop_from(&list);
}
END_TEST

START_TEST(Test_7) {
  char string[100] = "(12)*(-1.0006)";
  char letter[20] = "0";
  s21_list_t *list = s21_smartcalc_manager(string, letter);
  int error_target = list->type;
  long double result = list->value;
  ck_assert_float_eq(result, -12.0072);
  ck_assert_int_eq(error_target, 0);
  while (list) s21_pop_from(&list);
}
END_TEST

START_TEST(Test_8) {
  char string[100] = "(-(-(-10)))*(-(-10))";
  char letter[20] = "0";
  s21_list_t *list = s21_smartcalc_manager(string, letter);
  int error_target = list->type;
  long double result = list->value;
  ck_assert_float_eq(result, -100);
  ck_assert_int_eq(error_target, 0);
  while (list) s21_pop_from(&list);
}
END_TEST

START_TEST(Test_9) {
  char string[100] = "(-1.3)/4";
  char letter[20] = "0";
  s21_list_t *list = s21_smartcalc_manager(string, letter);
  int error_target = list->type;
  long double result = list->value;
  ck_assert_float_eq(result, -0.325);
  ck_assert_int_eq(error_target, 0);
  while (list) s21_pop_from(&list);
}
END_TEST

START_TEST(Test_10) {
  char string[100] = "(12)/(-1.0006)";
  char letter[20] = "0";
  s21_list_t *list = s21_smartcalc_manager(string, letter);
  int error_target = list->type;
  long double result = list->value;
  ck_assert_float_eq(result, -11.9928043);
  ck_assert_int_eq(error_target, 0);
  while (list) s21_pop_from(&list);
}
END_TEST

START_TEST(Test_11) {
  char string[100] = "(-(-(-10)))/(-(-10))";
  char letter[20] = "0";
  s21_list_t *list = s21_smartcalc_manager(string, letter);
  int error_target = list->type;
  long double result = list->value;
  ck_assert_float_eq(result, -1);
  ck_assert_int_eq(error_target, 0);
  while (list) s21_pop_from(&list);
}
END_TEST

START_TEST(Test_12) {
  char string_1[100] = "(1.3) mod 4";
  char letter[20] = "0";
  s21_list_t *list = s21_smartcalc_manager(string_1, letter);
  int error_target = list->type;
  long double result = list->value;
  ck_assert_float_eq(result, 1.3);
  ck_assert_int_eq(error_target, 0);
  while (list) s21_pop_from(&list);
  list = NULL;

  char string_2[100] = "12 mod 1.0006";
  list = s21_smartcalc_manager(string_2, letter);
  result = list->value;
  ck_assert_float_eq(result, 0.993400);
  ck_assert_int_eq(error_target, 0);
  while (list) s21_pop_from(&list);
  list = NULL;
  char string_3[100] = "(12.2) mod 12.02";
  list = s21_smartcalc_manager(string_3, letter);
  result = list->value;
  ck_assert_float_eq(result, 0.18);
  ck_assert_int_eq(error_target, 0);
  while (list) s21_pop_from(&list);
  list = NULL;
  char string_4[100] = "(-(-(-10))) mod (-(-10))";
  list = s21_smartcalc_manager(string_4, letter);
  result = list->value;
  ck_assert_float_eq(result, 0);
  ck_assert_int_eq(error_target, 0);
  while (list) s21_pop_from(&list);
}
END_TEST

START_TEST(Test_13) {
  char string_1[100] = "(-1.3)^4";
  char letter[20] = "0";
  s21_list_t *list = s21_smartcalc_manager(string_1, letter);
  int error_target = list->type;
  long double result = list->value;
  ck_assert_float_eq(result, 2.8561);
  ck_assert_int_eq(error_target, 0);
  while (list) s21_pop_from(&list);
  list = NULL;
  char string_2[100] = "(12)^(-1.0006)";
  list = s21_smartcalc_manager(string_2, letter);
  result = list->value;
  ck_assert_float_eq(result, 0.08320918057);
  ck_assert_int_eq(error_target, 0);
  while (list) s21_pop_from(&list);
  list = NULL;
  char string_3[100] = "(12.2)^2.02";
  list = s21_smartcalc_manager(string_3, letter);
  result = list->value;
  ck_assert_float_eq(result, 156.475683751);
  ck_assert_int_eq(error_target, 0);
  while (list) s21_pop_from(&list);
  list = NULL;
  char string_4[100] = "2^2^3";
  list = s21_smartcalc_manager(string_4, letter);
  result = list->value;
  ck_assert_float_eq(result, 256);
  ck_assert_int_eq(error_target, 0);
  while (list) s21_pop_from(&list);
}
END_TEST

START_TEST(Test_14) {
  char string_1[100] = "sqrt(4)";
  char letter[20] = "0";
  s21_list_t *list = s21_smartcalc_manager(string_1, letter);
  int error_target = list->type;
  long double result = list->value;
  ck_assert_float_eq(result, 2);
  ck_assert_int_eq(error_target, 0);
  while (list) s21_pop_from(&list);
  list = NULL;
  char string_2[100] = "sqrt(-4)";
  list = s21_smartcalc_manager(string_2, letter);
  result = list->value;
  ck_assert_double_nan(result);
  ck_assert_int_eq(error_target, 0);
  while (list) s21_pop_from(&list);
  list = NULL;
  char string_3[100] = "(-1)*sqrt(4)";
  list = s21_smartcalc_manager(string_3, letter);
  result = list->value;
  ck_assert_float_eq(result, -2);
  ck_assert_int_eq(error_target, 0);
  while (list) s21_pop_from(&list);
  list = NULL;
  char string_4[100] = "sqrt((((((4))))))";
  list = s21_smartcalc_manager(string_4, letter);
  result = list->value;
  ck_assert_float_eq(result, 2);
  ck_assert_int_eq(error_target, 0);
  while (list) s21_pop_from(&list);
}
END_TEST

START_TEST(Test_15) {
  char string_1[100] = "sin(3.14*2.2)";
  char letter[20] = "0";
  s21_list_t *list = s21_smartcalc_manager(string_1, letter);
  int error_target = list->type;
  long double result = list->value;
  ck_assert_float_eq(result, 0.584947);
  ck_assert_int_eq(error_target, 0);
  while (list) s21_pop_from(&list);
  list = NULL;
  char string_2[100] = "atan(3.14*2)";
  list = s21_smartcalc_manager(string_2, letter);
  result = list->value;
  ck_assert_double_eq_tol(result, 1.41288641, 1e-6);
  ck_assert_int_eq(error_target, 0);
  while (list) s21_pop_from(&list);
  list = NULL;
  char string_3[100] = "acos((((((-0.0001))))))";
  list = s21_smartcalc_manager(string_3, letter);
  result = list->value;
  ck_assert_double_eq_tol(result, 1.57089633, 1e-6);
  ck_assert_int_eq(error_target, 0);
  while (list) s21_pop_from(&list);
  list = NULL;
  char string_4[100] = "(-1)*ln(0.9)";
  list = s21_smartcalc_manager(string_4, letter);
  result = list->value;
  ck_assert_float_eq(result, 0.10536051565);
  ck_assert_int_eq(error_target, 0);
  while (list) s21_pop_from(&list);
}
END_TEST

START_TEST(Test_16) {
  char string_1[100] = "cos(3.14*2)";
  char letter[20] = "0";
  s21_list_t *list = s21_smartcalc_manager(string_1, letter);
  int error_target = list->type;
  long double result = list->value;
  ck_assert_float_eq(result, 0.99999492691);
  ck_assert_int_eq(error_target, 0);
  while (list) s21_pop_from(&list);
  list = NULL;
  char string_2[100] = "cos(1)";
  list = s21_smartcalc_manager(string_2, letter);
  result = list->value;
  ck_assert_float_eq(result, 0.54030230586);
  ck_assert_int_eq(error_target, 0);
  while (list) s21_pop_from(&list);
  list = NULL;
  char string_3[100] = "(-1)*cos(1)";
  list = s21_smartcalc_manager(string_3, letter);
  result = list->value;
  ck_assert_float_eq(result, -0.54030230586);
  ck_assert_int_eq(error_target, 0);
  while (list) s21_pop_from(&list);
  list = NULL;
  char string_4[100] = "cos((((((4))))))";
  list = s21_smartcalc_manager(string_4, letter);
  result = list->value;
  ck_assert_float_eq(result, -0.65364362086);
  ck_assert_int_eq(error_target, 0);
  while (list) s21_pop_from(&list);
}
END_TEST

START_TEST(Test_17) {
  char string_1[100] = "sin(1.0009-12.53)*cos(1.25*2^3)";
  char letter[20] = "0";
  s21_list_t *list = s21_smartcalc_manager(string_1, letter);
  int error_target = list->type;
  long double result = list->value;
  ck_assert_float_eq(result, -0.72245681954);
  ck_assert_int_eq(error_target, 0);
  while (list) s21_pop_from(&list);
  list = NULL;
  char string_2[100] = "log(15.3)*log(-10)+15-1*15/14";
  list = s21_smartcalc_manager(string_2, letter);
  result = list->value;
  ck_assert_double_nan(result);
  ck_assert_int_eq(error_target, 0);
  while (list) s21_pop_from(&list);
  list = NULL;
  char string_3[100] = "2^2^3*3^2^3";
  list = s21_smartcalc_manager(string_3, letter);
  result = list->value;
  ck_assert_float_eq(result, 1679616.000000);
  ck_assert_int_eq(error_target, 0);
  while (list) s21_pop_from(&list);
  list = NULL;
  char string_4[100] = "sin(30)+cos(30)*tan(30)/acos(0.15)^asin(0.15)";
  list = s21_smartcalc_manager(string_4, letter);
  result = list->value;
  ck_assert_float_eq(result, -1.92522789382);
  ck_assert_int_eq(error_target, 0);
  while (list) s21_pop_from(&list);
  list = NULL;
  char string_5[100] = "17 mod 13 mod 5";
  list = s21_smartcalc_manager(string_5, letter);
  result = list->value;
  ck_assert_float_eq(result, 4);
  ck_assert_int_eq(error_target, 0);
  while (list) s21_pop_from(&list);
}
END_TEST

START_TEST(Test_18) {
  char string[100] = "7*2+(2-3";
  char letter[20] = "0";
  s21_list_t *list = s21_smartcalc_manager(string, letter);
  int error_target = list->type;
  ck_assert_int_eq(error_target, ERROR);
  while (list) s21_pop_from(&list);
}
END_TEST

START_TEST(Test_19) {
  char string[100] = "7*2+(2-3*())";
  char letter[20] = "0";
  s21_list_t *list = s21_smartcalc_manager(string, letter);
  int error_target = list->type;
  ck_assert_int_eq(error_target, ERROR);
  while (list) s21_pop_from(&list);
}
END_TEST

START_TEST(Test_20) {
  char string[100] = "7*2.(+(2-3*())";
  char letter[20] = "0";
  s21_list_t *list = s21_smartcalc_manager(string, letter);
  int error_target = list->type;
  ck_assert_int_eq(error_target, ERROR);
  while (list) s21_pop_from(&list);
}
END_TEST

START_TEST(Test_21) {
  char string[100] = "7*2.(+(2-3*())";
  char letter[20] = "0";
  s21_list_t *list = s21_smartcalc_manager(string, letter);
  int error_target = list->type;
  ck_assert_int_eq(error_target, ERROR);
  while (list) s21_pop_from(&list);
}
END_TEST

START_TEST(Test_22) {
  char string[100] = "7.2.3*2.(+(2-3*())";
  char letter[20] = "0";
  s21_list_t *list = s21_smartcalc_manager(string, letter);
  int error_target = list->type;
  ck_assert_int_eq(error_target, ERROR);
  while (list) s21_pop_from(&list);
}
END_TEST

START_TEST(Test_23) {
  char string[100] = "((2-3*(2)2)";
  char letter[20] = "0";
  s21_list_t *list = s21_smartcalc_manager(string, letter);
  int error_target = list->type;
  ck_assert_int_eq(error_target, ERROR);
  while (list) s21_pop_from(&list);
}
END_TEST

START_TEST(Test_24) {
  char string[100] = "(-1.3)*4";
  char letter[20] = "0";
  s21_list_t *list = s21_smartcalc_manager(string, letter);
  int error_target = list->type;
  long double result = list->value;
  ck_assert_float_eq(result, -5.2);
  ck_assert_int_eq(error_target, 0);
  while (list) s21_pop_from(&list);
}
END_TEST

START_TEST(Test_25) {
  char string[100] = "sin(245)*((((cos(240)^2*2))))";
  char letter[20] = "0";
  s21_list_t *list = s21_smartcalc_manager(string, letter);
  int error_target = list->type;
  long double result = list->value;
  ck_assert_float_eq(result, -0.00938486453);
  ck_assert_int_eq(error_target, 0);
  while (list) s21_pop_from(&list);
}
END_TEST

START_TEST(Test_26) {
  char string[100] = "(sin(30)+cos(30)*tan(30)/acos(0.15)^asin(0.15))^2";
  char letter[20] = "0";
  s21_list_t *list = s21_smartcalc_manager(string, letter);
  int error_target = list->type;
  long double result = list->value;
  ck_assert_float_eq(result, 3.70650244314);
  ck_assert_int_eq(error_target, 0);
  while (list) s21_pop_from(&list);
}
END_TEST

START_TEST(Test_27) {
  char string[100] = "-1-(-1)";
  char letter[20] = "0";
  s21_list_t *list = s21_smartcalc_manager(string, letter);
  int error_target = list->type;
  long double result = list->value;
  ck_assert_float_eq(result, 0);
  ck_assert_int_eq(error_target, 0);
  while (list) s21_pop_from(&list);
}
END_TEST

START_TEST(Test_28) {
  char string[100] = "+1+(-1)";
  char letter[20] = "0";
  s21_list_t *list = s21_smartcalc_manager(string, letter);
  int error_target = list->type;
  long double result = list->value;
  ck_assert_float_eq(result, 0);
  ck_assert_int_eq(error_target, 0);
  while (list) s21_pop_from(&list);
}
END_TEST

START_TEST(Test_29) {
  char string[100] = "sin(x)*((((cos(240)^2*2))))";
  char letter[20] = "245";
  s21_list_t *list = s21_smartcalc_manager(string, letter);
  int error_target = list->type;
  long double result = list->value;
  ck_assert_float_eq(result, -0.00938486453);
  ck_assert_int_eq(error_target, 0);
  while (list) s21_pop_from(&list);
}
END_TEST

START_TEST(Test_30) {
  char string[100] = "x";
  char letter[20] = "255";
  s21_list_t *list = s21_smartcalc_manager(string, letter);
  int error_target = list->type;
  long double result = list->value;
  ck_assert_float_eq(result, 255);
  ck_assert_int_eq(error_target, 0);
  while (list) s21_pop_from(&list);
}
END_TEST

Suite *s21_smart_calc_tests_create() {
  Suite *s21_smart_calc = suite_create("s21_smart_calc");
  TCase *s21_smart_calc_tests = tcase_create("s21_smart_calc");
  tcase_add_test(s21_smart_calc_tests, Test_1);
  tcase_add_test(s21_smart_calc_tests, Test_2);
  tcase_add_test(s21_smart_calc_tests, Test_3);
  tcase_add_test(s21_smart_calc_tests, Test_4);
  tcase_add_test(s21_smart_calc_tests, Test_5);
  tcase_add_test(s21_smart_calc_tests, Test_6);
  tcase_add_test(s21_smart_calc_tests, Test_7);
  tcase_add_test(s21_smart_calc_tests, Test_8);
  tcase_add_test(s21_smart_calc_tests, Test_9);
  tcase_add_test(s21_smart_calc_tests, Test_10);
  tcase_add_test(s21_smart_calc_tests, Test_11);
  tcase_add_test(s21_smart_calc_tests, Test_12);
  tcase_add_test(s21_smart_calc_tests, Test_13);
  tcase_add_test(s21_smart_calc_tests, Test_14);
  tcase_add_test(s21_smart_calc_tests, Test_15);
  tcase_add_test(s21_smart_calc_tests, Test_16);
  tcase_add_test(s21_smart_calc_tests, Test_17);
  tcase_add_test(s21_smart_calc_tests, Test_18);
  tcase_add_test(s21_smart_calc_tests, Test_19);
  tcase_add_test(s21_smart_calc_tests, Test_20);
  tcase_add_test(s21_smart_calc_tests, Test_21);
  tcase_add_test(s21_smart_calc_tests, Test_22);
  tcase_add_test(s21_smart_calc_tests, Test_23);
  tcase_add_test(s21_smart_calc_tests, Test_24);
  tcase_add_test(s21_smart_calc_tests, Test_25);
  tcase_add_test(s21_smart_calc_tests, Test_26);
  tcase_add_test(s21_smart_calc_tests, Test_27);
  tcase_add_test(s21_smart_calc_tests, Test_28);
  tcase_add_test(s21_smart_calc_tests, Test_29);
  tcase_add_test(s21_smart_calc_tests, Test_30);
  suite_add_tcase(s21_smart_calc, s21_smart_calc_tests);
  return s21_smart_calc;
}

int main() {
  Suite *s21_smart_calc = s21_smart_calc_tests_create();
  SRunner *s21_smart_calc_runner = srunner_create(s21_smart_calc);
  int number_failed;
  srunner_run_all(s21_smart_calc_runner, FP_NORMAL);
  number_failed = srunner_ntests_failed(s21_smart_calc_runner);
  srunner_free(s21_smart_calc_runner);
  return number_failed == 0 ? 0 : 1;
}
