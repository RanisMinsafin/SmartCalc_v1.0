#include "s21_smartcalc.h"

// Determine is function/bracket or not
int s21_is_function_or_bracket(s21_list_t* list) {
  return list && (list->type == OPEN_BRACKETS || list->priority == HIGH);
}

// Determine is it pow in list stack and in operands stack
int s21_is_double_pow(s21_list_t* list, s21_list_t* operands) {
  return list && list->type == POW && operands->type == POW;
}

// Determine is it bracket or not
int s21_not_bracket(s21_list_t* list) {
  return list && list->type != CLOSE_BRACKETS && list->type != OPEN_BRACKETS;
}

// Convert normal stack to RPN and then it is calculates
s21_list_t* s21_polish_notation(s21_list_t* list) {
  s21_list_t* numbers = NULL;
  s21_list_t* operands = NULL;
  list = s21_list_reverse(list);
  while (list) {
    if (list->type == NUMBER) {
      s21_push_from(&numbers, list);
    } else {
      if (operands == NULL || s21_is_function_or_bracket(list)) {
        s21_push_from(&operands, list);
      } else if (list->type == CLOSE_BRACKETS) {
        while (operands->type != OPEN_BRACKETS) {
          numbers = s21_calculate(numbers, (int)operands->type);
          s21_pop_from(&operands);
        }
        if (operands->type == OPEN_BRACKETS) s21_pop_from(&operands);
        s21_pop_from(&list);
        continue;
      } else if (list->priority > operands->priority ||
                 s21_is_double_pow(list, operands)) {
        s21_push_from(&operands, list);
      } else if (list->priority <= operands->priority) {
        while (operands && operands->priority >= list->priority) {
          if (operands->type == OPEN_BRACKETS) break;
          numbers = s21_calculate(numbers, (int)operands->type);
          s21_pop_from(&operands);
        }
        if (list) s21_push_from(&operands, list);
      }
    }
    s21_pop_from(&list);
  }
  if (numbers && !s21_not_bracket(numbers)) s21_pop_from(&numbers);
  while (operands) {
    numbers = s21_calculate(numbers, (int)operands->type);
    s21_pop_from(&operands);
  }
  // numbers = s21_list_reverse(numbers);
  if (operands) free(operands);
  if (list) free(list);
  return numbers;
}

// Determine the value of expression
s21_list_t* s21_calculate(s21_list_t* list, int type_of_operand) {
  if (list != NULL) {
    s21_math math = {0};
    math.action = type_of_operand;
    s21_list_t* pop_list = NULL;
    if (math.action < 7) {
      for (int i = 0; i < 2; i++) {
        if (list) pop_list = s21_pop(&list);
        if (i == 0) {
          math.a = pop_list->value;
        } else {
          math.b = pop_list->value;
        }
        if (pop_list != NULL) free(pop_list);
      }
      s21_arithmetic(&math);
    } else {
      pop_list = s21_pop(&list);
      math.a = pop_list->value;
      s21_trigonometry(&math);
      if (pop_list != NULL) free(pop_list);
    }
    s21_push(&list, math.result, NUMBER, LOW);
  }
  return list;
}

// Calculation of arithmetic operations
void s21_arithmetic(s21_math* math) {
  switch (math->action) {
    case PLUS:
      math->result = math->a + math->b;
      break;
    case MINUS:
      math->result = math->b - math->a;
      break;
    case MULTIPLY:
      math->result = math->a * math->b;
      break;
    case DIVIDE:
      math->result = math->b / math->a;
      break;
    case POW:
      math->result = pow(math->b, math->a);
      break;
    case MOD:
      math->result = fmod(math->b, math->a);
      break;
  }
}

// Calculation of trigonometry operations
void s21_trigonometry(s21_math* math) {
  switch (math->action) {
    case COS:
      math->result = cos(math->a);
      break;
    case SIN:
      math->result = sin(math->a);
      break;
    case TAN:
      math->result = tan(math->a);
      break;
    case ACOS:
      math->result = acos(math->a);
      break;
    case ASIN:
      math->result = asin(math->a);
      break;
    case ATAN:
      math->result = atan(math->a);
      break;
    case SQRT:
      math->result = sqrt(math->a);
      break;
    case LN:
      math->result = log(math->a);
      break;
    case LOG:
      math->result = log10(math->a);
      break;
  }
}
// Determine strings are correct or not
int s21_is_correct(char* string, char* letter) {
  return string != NULL && letter != NULL && strlen(string) < 256 &&
         strlen(letter) < 17 && s21_is_empty(string, letter) &&
         strncmp(string, "Error", 5) != 0;
}

// Determine strings are empty or not
int s21_is_empty(char* string, char* letter) {
  return *string != '\0' && *string != ' ' && *letter != '\0';
}

// Main function of SmartCalculator
s21_list_t* s21_smartcalc_manager(char* string, char* letter) {
  s21_list_t* list = NULL;
  if (s21_is_correct(string, letter)) {
    if (s21_parser(&list, string, letter) == 0) {
      list = s21_polish_notation(list);
    } else {
      while (list) s21_pop_from(&list);
      list = calloc(1, sizeof(s21_list_t));
      list->type = ERROR;
    }
  } else {
    list = calloc(1, sizeof(s21_list_t));
    list->type = ERROR;
  }
  return list;
}

// int main() {
//   char* tmp = "1+2";
//   char* letter = " ";
//   s21_list_t* list = s21_smartcalc_manager(tmp, letter);
//   printf("\tResult = %lf\n", list->value);
//   return 0;
// }
