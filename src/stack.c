#include <stdlib.h>
#include "stack.h"
#include "list.h"

stack_t *stack_init(void (*free_data)(void *)){

    stack_t *stack = (stack_t *)malloc(sizeof(stack_t));

    if(!stack)
        return NULL;
    
    stack->list = list_init(NULL, free_data);

    if(!stack->list)
        return NULL;

    return stack;
}

void stack_destroy(stack_t *stack){
    list_destroy(stack->list);
    free(stack);
}

int stack_push(stack_t *stack, void *data){

	return list_append(stack->list, data);
}

void *stack_peek(stack_t *stack){
	return stack->list->tail->data;
}

void *stack_pop(stack_t *stack){
	return list_pop(stack->list, get_list_size(stack->list) - 1);
}

int stack_is_empty(stack_t *stack){
	return (get_list_size(stack->list) == 0);
}