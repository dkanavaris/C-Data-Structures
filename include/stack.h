#ifndef __STACK_H__
#define __STACK_H__

#include "list.h"

typedef struct stack {
    list_t *list;
}stack_t;

/* Initialize a new stack
 * Returns a pointer to stack_t struct
 * Params : 
 * @free_node_data function used to free the list nodes data */
stack_t *stack_init(void (*free_data)(void *));

/* Destroy a stack
 * Params : 
 * @stack to be destroyed */
void stack_destroy(stack_t *stack);

/* Push data to stack
 * Params : 
 * @stack to push data to
 * @data to be pushed */

int stack_push(stack_t *stack, void *data);

/* Get the stack top element without removing it
 * Returns the top stack element
 * Params : 
 * @stack to get data from*/
void *stack_peek(stack_t *stack);

/* Get the stack top element while also removing it
 * Returns the top stack element
 * Params : 
 * @stack to get data from*/
void *stack_pop(stack_t *stack);

/* Check if stack is empty
 * Returns 1 if stack is empty, 0 otherwise
 * Params : 
 * @stack to check*/
int stack_is_empty(stack_t *stack);

#endif