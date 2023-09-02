#include "s21_stack.h"

// Adds an element to the top of the stack
void s21_push(s21_list_t** old, double value, s21_type_t type, int priority) {
  s21_list_t* new_one = NULL;
  new_one = calloc(1, sizeof(s21_list_t));
  if (new_one != NULL) {
    new_one->value = value;
    new_one->type = type;
    new_one->priority = priority;
    new_one->next = *old;
    (*old) = new_one;
  }
}

// Adds an element to the top of the stack from another stack
void s21_push_from(s21_list_t** new_one, s21_list_t* old) {
  if (old != NULL) s21_push(new_one, old->value, old->type, old->priority);
}

// Removes an element from top of the stack
s21_list_t* s21_pop(s21_list_t** list) {
  s21_list_t* pop_list = NULL;
  if (list != NULL) {
    pop_list = *list;
    *list = pop_list->next;
  }
  return pop_list;
}

// Removes an element from top of the stack without return
void s21_pop_from(s21_list_t** list) {
  if (list != NULL) {
    s21_list_t* tmp = s21_pop(list);
    if (tmp) free(tmp);
  }
}

// Reverse the stack
s21_list_t* s21_list_reverse(s21_list_t* list) {
  s21_list_t* list_reverse = NULL;
  while (list != NULL) {
    s21_push(&list_reverse, list->value, list->type, list->priority);
    s21_pop_from(&list);
  }
  return list_reverse;
}
