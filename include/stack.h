#ifndef __STACK_H__
#define __STACK_H__

#include "list.h"

typedef struct stack {
    list_t *list;
}stack_t;

stack_t *stack_init(void (*free_data)(void *));

void stack_destroy(stack_t *stack);

int stack_push(stack_t *stack, void *data);
void *stack_peek(stack_t *stack);
void *stack_pop(stack_t *stack);
int stack_is_empty(stack_t *stack);

#endif