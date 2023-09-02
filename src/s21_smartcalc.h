#ifndef SRC_S21_SMARTCALC_H_
#define SRC_S21_SMARTCALC_H_

#include "s21_parser.h"
#include "s21_stack.h"

// Structure for working with math
typedef struct s21_math {
  int action;
  double a;
  double b;
  double result;
} s21_math;

// Main function
s21_list_t* s21_smartcalc_manager(char* string, char* letter);
// Reverse polish notation functions
int s21_not_bracket(s21_list_t* list);
int s21_is_function_or_bracket(s21_list_t* list);
int s21_is_double_pow(s21_list_t* list, s21_list_t* operands);
s21_list_t* s21_polish_notation(s21_list_t* list);
// Calculation functions
void s21_arithmetic(s21_math* math);
void s21_trigonometry(s21_math* math);
s21_list_t* s21_calculate(s21_list_t* list, int type_of_operand);
// Help function
int s21_is_correct(char* string, char* letter);
int s21_is_empty(char* string, char* letter);

#endif  // SRC_S21_SMARTCALC_H_
