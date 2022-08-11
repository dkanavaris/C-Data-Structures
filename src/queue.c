#include <stdlib.h>
#include "queue.h"
#include "list.h"

queue_t *queue_init(){

    queue_t *queue = (queue_t *)malloc(sizeof(queue_t));

    if(!queue)
        return NULL;

    queue->list = list_init(NULL, NULL);

    if(!queue->list)
        return NULL;
    
    return queue;
}


void queue_destroy(queue_t *queue){
    list_destroy(queue->list);
    free(queue);
}

int queue_enqueue_front(queue_t *queue, void *data){
    return list_insert(queue->list, 0, data);
}

int queue_enqueue_back(queue_t *queue, void *data){
    return list_insert(queue->list, get_list_size(queue->list), data);
}


void *queue_dequeue_front(queue_t *queue){
    return list_pop(queue->list, 0);
}

void *queue_dequeue_back(queue_t *queue){
    return list_pop(queue->list, get_list_size(queue->list));
}