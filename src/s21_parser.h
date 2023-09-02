#ifndef SRC_S21_PARSER_H_
#define SRC_S21_PARSER_H_
#include "s21_stack.h"

int s21_is_long_num(char* string, int* step);
int s21_is_number_or_dot(char* string, int* step);
int s21_is_symbol(char* string, int step);
int s21_is_number(char* string, int step);
int s21_x_mistake(char* string, int* step);
int s21_is_unar(s21_list_t* list, char* string, int step);
int s21_string_to_float_converter(s21_list_t** list, char* string, char* letter,
                                  int* step);
int s21_number_parser(s21_list_t** list, char* string, char* letter, int* step);
void s21_arithmetic_parser(s21_list_t** list, char* string, int* step);
void s21_func_parser(s21_list_t** list, char* string, int* step);
int s21_brackets_parser(s21_list_t** list, char* string, int* step,
                        int* brackets_counter);
int s21_brackets_mistakes(char* string, int* step);
int s21_parser(s21_list_t** list, char* string, char* letter);

#endif  // SRC_S21_PARSER_H_
