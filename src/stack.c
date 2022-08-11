#include <stdlib.h>
#include "stack.h"
#include "list.h"


/* Initialize a new stack
 * Returns a pointer to stack_t struct
 * Params : 
 * @free_node_data function used to free the list nodes data */
stack_t *stack_init(void (*free_data)(void *)){

    stack_t *stack = (stack_t *)malloc(sizeof(stack_t));

    if(!stack)
        return NULL;
    
    stack->list = list_init(NULL, free_data);

    if(!stack->list)
        return NULL;

    return stack;
}

/* Destroy a stack
 * Params : 
 * @stack to be destroyed */
void stack_destroy(stack_t *stack){
    list_destroy(stack->list);
    free(stack);
}

/* Push data to stack
 * Params : 
 * @stack to push data to
 * @data to be pushed */
int stack_push(stack_t *stack, void *data){

	return list_append(stack->list, data);
}

/* Get the stack top element without removing it
 * Returns the top stack element
 * Params : 
 * @stack to get data from*/
void *stack_peek(stack_t *stack){
	return stack->list->tail->data;
}

/* Get the stack top element while also removing it
 * Returns the top stack element
 * Params : 
 * @stack to get data from*/
void *stack_pop(stack_t *stack){
	return list_pop(stack->list, get_list_size(stack->list) - 1);
}

/* Check if stack is empty
 * Returns 1 if stack is empty, 0 otherwise
 * Params : 
 * @stack to check*/
int stack_is_empty(stack_t *stack){
	return (get_list_size(stack->list) == 0);
}