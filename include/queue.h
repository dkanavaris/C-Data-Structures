#ifndef __QUEUE_H__
#define __QUEUE_H__

#include "list.h"

typedef struct queue{
    list_t *list;
}queue_t;

/* Initialize a new queue
 * Returns a pointer to queue_t struct
 * Params : 
 * @free_node_data function used to free the queue nodes data */
queue_t *queue_init(void (*free_node_data)(void *));

/* Destroy a queue
 * Params : 
 * @queue to be destroyed */		
void queue_destroy(queue_t *queue);

/* Insert data at the front of the queue
 * Params : 
 * @queue to insert data to
 * @data to be inserted */		
int queue_enqueue_front(queue_t *queue, void *data);

/* Insert data at the back of the queue
 * Params : 
 * @queue to insert data to
 * @data to be inserted */	
int queue_enqueue_back(queue_t *queue, void *data);

/* Remove data from the front of the queue
 * Params : 
 * @queue to insert data to
 */	
void *queue_dequeue_front(queue_t *queue);

/* Remove data from the back of the queue
 * Params : 
 * @queue to insert data to
 */	
void *queue_dequeue_back(queue_t *queue);

#endif