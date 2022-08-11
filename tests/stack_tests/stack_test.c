#include <stdio.h>
#include "stack.h"
#include <stdlib.h>

typedef struct data{
    int value;
}data_t;

void free_data(void *d){
    free(d);
}

int main(int argc, char **argv){

    stack_t *stack = stack_init(free_data);

    data_t *d1 = (data_t *)malloc(sizeof(data_t));
    data_t *d2 = (data_t *)malloc(sizeof(data_t));
    data_t *d3 = (data_t *)malloc(sizeof(data_t));
    data_t *d4 = (data_t *)malloc(sizeof(data_t));
    data_t *d5 = (data_t *)malloc(sizeof(data_t));
    data_t *d6 = (data_t *)malloc(sizeof(data_t));
    data_t *d7 = (data_t *)malloc(sizeof(data_t));
    data_t *d8 = (data_t *)malloc(sizeof(data_t));

    d1->value = 10;
    d2->value = 20;
    d3->value = 30;
    d4->value = 40;
    d5->value = 50;
    d6->value = 60;
    d7->value = 70;
    d8->value = 80;

    stack_push(stack, d1);
    stack_push(stack, d2);
    stack_push(stack, d3);
    stack_push(stack, d4);
    stack_push(stack, d5);
    stack_push(stack, d6);
    stack_push(stack, d7);
    stack_push(stack, d8);

    void *data;
    while(!stack_is_empty(stack)){
        data = stack_pop(stack);
        printf("Got data %d\n", *(int *)data);
        free(data);
    }

    stack_destroy(stack);

    return 0;
}