#include "s21_parser.h"

// Determine is it number or not
int s21_is_number(char* string, int step) {
  return string[step + 1] >= '0' && string[step + 1] <= '9';
}

// Determine is it trigonometry operand/symbol or not
int s21_is_symbol(char* string, int step) {
  return string[step + 1] == 'a' || string[step + 1] == 's' ||
         string[step + 1] == 'c' || string[step + 1] == 't' ||
         string[step + 1] == 'l' || string[step + 1] == '(';
}

// Determine is it number/dot or not
int s21_is_number_or_dot(char* string, int* step) {
  return (string[*step] >= '0' && string[*step] <= '9') ||
         string[*step] == '.' || s21_is_long_num(string, step);
}

// Determine does number have a 'e' and '-' symbols
int s21_is_long_num(char* string, int* step) {
  return (string[*step] == 'e' && string[*step + 1] == '-') ||
         (string[*step] == '-' && string[*step - 1] == 'e');
}

//  Determine is it x mistake or not
int s21_x_mistake(char* string, int* step) {
  return s21_is_number(string, *step) || string[*step + 1] == '.';
}

//  Determine is it unar plus or minus
int s21_is_unar(s21_list_t* list, char* string, int step) {
  int result = 0;
  if (list &&
      ((list->type > 1 && list->type < 9) || list->type == OPEN_BRACKETS)) {
    if (s21_is_number(string, step) || s21_is_symbol(string, step)) {
      if (string[step] == '+') {
        result = 2;
      } else if (string[step] == '-') {
        result = 1;
      }
    }
  }
  return result;
}

// Convert string to float
int s21_string_to_float_converter(s21_list_t** list, char* string, char* letter,
                                  int* step) {
  int result = 0, dot_counter = 0;
  double return_number = 0.0;
  char str[30] = {'\0'};
  if (string[*step] == 'x') {
    if (letter != NULL) {
      return_number = atof(letter);
    } else {
      return_number = 0;
    }
    if (s21_x_mistake(string, step)) result = 1;
  } else {
    for (int i = 0; s21_is_number_or_dot(string, step) && result == 0;
         (*step)++, i++) {
      if (string[*step] == '.') {
        if (string[*step + 1] == 'x') result = 1;
        dot_counter++;
      }
      if (dot_counter > 1) result = 1;
      str[i] = string[*step];
    }
    return_number = atof(str);
  }
  s21_push(list, return_number, NUMBER, LOW);
  return result;
}

// Search numbers in string
int s21_number_parser(s21_list_t** list, char* string, char* letter,
                      int* step) {
  int result = 0;
  if ((string[*step] >= '0' && string[*step] <= '9') || string[*step] == 'x' ||
      string[*step] == '.') {
    if (s21_string_to_float_converter(list, string, letter, &*step) == 1)
      result = 1;
    if ((string[*step] >= 'a' && string[*step] <= 'w') ||
        (string[*step] >= 'y' && string[*step] <= 'z'))
      result = 1;
  }
  return result;
}

// Search symbol of arithmetic operation
void s21_arithmetic_parser(s21_list_t** list, char* string, int* step) {
  if (string[*step] == '+') s21_push(list, 0, PLUS, LOW);
  if (string[*step] == '-') s21_push(list, 0, MINUS, LOW);
  if (string[*step] == '*') s21_push(list, 0, MULTIPLY, MIDDLE);
  if (string[*step] == '/') s21_push(list, 0, DIVIDE, MIDDLE);
  if (strncmp(string + *step, "mod", 3) == 0) {
    s21_push(list, 0, MOD, MIDDLE);
    *step += 2;
  }
  if (string[*step] == '^') s21_push(list, 0, POW, UNARY);
}

// Search name of trigonometry functions
void s21_function_parser(s21_list_t** list, char* string, int* step) {
  if (strncmp(string + *step, "cos", 3) == 0) {
    s21_push(list, 0, COS, HIGH);
    *step += 2;
  }
  if (strncmp(string + *step, "sin", 3) == 0) {
    s21_push(list, 0, SIN, HIGH);
    *step += 2;
  }
  if (strncmp(string + *step, "tan", 3) == 0) {
    s21_push(list, 0, TAN, HIGH);
    *step += 2;
  }
  if (strncmp(string + *step, "acos", 4) == 0) {
    s21_push(list, 0, ACOS, HIGH);
    *step += 3;
  }
  if (strncmp(string + *step, "asin", 4) == 0) {
    s21_push(list, 0, ASIN, HIGH);
    *step += 3;
  }
  if (strncmp(string + *step, "atan", 4) == 0) {
    s21_push(list, 0, ATAN, HIGH);
    *step += 3;
  }
  if (strncmp(string + *step, "ln", 2) == 0) {
    s21_push(list, 0, LN, HIGH);
    *step += 1;
  }
  if (strncmp(string + *step, "sqrt", 4) == 0) {
    s21_push(list, 0, SQRT, HIGH);
    *step += 3;
  }
  if (strncmp(string + *step, "log", 3) == 0) {
    s21_push(list, 0, LOG, HIGH);
    *step += 2;
  }
}

// Search symbol of brackets
int s21_brackets_parser(s21_list_t** list, char* string, int* step,
                        int* brackets_counter) {
  int result = 0;
  if (string[*step] == '(') {
    s21_push(list, 0, OPEN_BRACKETS, BRACKET);
    (*brackets_counter)++;
    result = s21_brackets_mistakes(string, step);
  }
  if (string[*step] == ')') {
    s21_push(list, 0, CLOSE_BRACKETS, BRACKET);
    if (s21_is_number(string, *step)) result = 1;
    (*brackets_counter)--;
  }
  return result;
}
// Search mistakes with brackets
int s21_brackets_mistakes(char* string, int* step) {
  int result = 0;
  if (*step > 0 && string[*step - 1] == '.') result = 1;
  if (string[*step + 1] == '.') result = 1;
  if (string[*step + 1] == ')') result = 1;
  if (string[*step + 1] == '-' && string[*step + 2] == ')') result = 1;
  return result;
}

// Main function of parser
int s21_parser(s21_list_t** list, char* string, char* letter) {
  int result = 0, step = 0, brackets_counter = 0;
  int length = strlen(string);
  for (; step < length && result != 1; step++) {
    if (string[step] == ' ') continue;
    // unars in begining
    if (string[step] == '-' && step == 0) {
      s21_push(list, -1, NUMBER, LOW);
      s21_push(list, 0, MULTIPLY, UNARY);
      continue;
    }
    if (string[step] == '+' && step == 0) {
      s21_push(list, 1, NUMBER, LOW);
      s21_push(list, 0, MULTIPLY, UNARY);
      continue;
    }
    if (s21_number_parser(list, string, letter, &step)) {
      result = 1;
    }
    // unars in middle
    if (s21_is_unar((*list), string, step) == 1) {
      s21_push(list, -1, NUMBER, LOW);
      s21_push(list, 0, MULTIPLY, UNARY);
      continue;
    }
    if (s21_is_unar((*list), string, step) == 2) {
      s21_push(list, 1, NUMBER, LOW);
      s21_push(list, 0, MULTIPLY, UNARY);
      continue;
    }
    // arithmetic operands
    s21_arithmetic_parser(list, string, &step);
    s21_function_parser(list, string, &step);
    if (s21_brackets_parser(list, string, &step, &brackets_counter)) {
      result = 1;
    }
  }
  if (brackets_counter != 0) result = 1;
  return result;
}