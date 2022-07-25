#ifndef __FIFO_H__
#define __FIFO_H__

#include "list.h"

typedef struct fifo{
    list_t *list;
}fifo_t;

fifo_t *fifo_init();

int fifo_enqueue(fifo_t *fifo, void *data);
void *fifo_dequeue(fifo_t *fifo);

#endif