#ifndef SRC_S21_STACK_H_
#define SRC_S21_STACK_H_

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Definition of data type
typedef enum s21_type_t {
  NUMBER,          // 0-9
  PLUS,            // '+'
  MINUS,           // '-'
  MULTIPLY,        // '*'
  DIVIDE,          // '/'
  MOD,             // '%'
  POW,             // '^'
  SQRT,            // 'sqrt(x)'
  COS,             // cos(x)
  SIN,             // sin(x)
  TAN,             // tan(x)
  ACOS,            // acos(x)
  ASIN,            // asin(x)
  ATAN,            // atan(x)
  LN,              // ln(x)
  LOG,             // log(x)
  OPEN_BRACKETS,   // '('
  CLOSE_BRACKETS,  // ')'
  ERROR            // ERROR
} s21_type_t;

// Definition of priorities
typedef enum s21_priority_t {
  LOW,     // 0
  MIDDLE,  // 1
  UNARY,   // 2
  HIGH,    // 3
  BRACKET  // 4
} s21_priority_t;

// Structure for working with stack
typedef struct s21_list_t {
  double value;
  int type;
  s21_priority_t priority;
  struct s21_list_t* next;
} s21_list_t;

void s21_push(s21_list_t** old, double value, s21_type_t type, int priority);
void s21_push_from(s21_list_t** new_one, s21_list_t* old);
s21_list_t* s21_pop(s21_list_t** list);
void s21_pop_from(s21_list_t** list);
s21_list_t* s21_list_reverse(s21_list_t* list);

#endif  // SRC_S21_STACK_H_
