#ifndef __QUEUE_H__
#define __QUEUE_H__

#include "list.h"

typedef struct queue{
    list_t *list;
}queue_t;

queue_t *queue_init();

int queue_enqueue_front(queue_t *queue, void *data);
int queue_enqueue_back(queue_t *queue, void *data);

void *queue_dequeue_front(queue_t *queue);
void *queue_dequeue_back(queue_t *queue);

#endif