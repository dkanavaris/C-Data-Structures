#include <stdlib.h>
#include "./include/fifo.h"
#include <stdio.h>

fifo_t *fifo_init(){

    fifo_t *fifo = (fifo_t *)malloc(sizeof(fifo_t));

    if(!fifo)
        return NULL;

    fifo->list = list_init(NULL, NULL);
    if(!fifo->list)
        return NULL;
    
    return fifo;
}

int fifo_enqueue(fifo_t *fifo, void *data){
    return list_append(fifo->list, data);
}

void *fifo_dequeue(fifo_t *fifo){
    return list_pop(fifo->list, 0);
}