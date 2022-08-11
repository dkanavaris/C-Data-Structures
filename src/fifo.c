#include <stdlib.h>
#include "fifo.h"
#include <stdio.h>

fifo_t *fifo_init(void (*free_data)(void *)){

    fifo_t *fifo = (fifo_t *)malloc(sizeof(fifo_t));

    if(!fifo)
        return NULL;

    fifo->list = list_init(NULL, free_data);
    if(!fifo->list)
        return NULL;
    
    return fifo;
}

void fifo_destroy(fifo_t *fifo){
    list_destroy(fifo->list);
    free(fifo);
}

int fifo_enqueue(fifo_t *fifo, void *data){
    return list_append(fifo->list, data);
}

void *fifo_dequeue(fifo_t *fifo){
    return list_pop(fifo->list, 0);
}