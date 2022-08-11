#ifndef __FIFO_H__
#define __FIFO_H__

#include "list.h"


typedef struct fifo{
    list_t *list;
}fifo_t;

/* Initialize a new fifo
 * Returns a pointer to fifo_t struct
 * Params : 
 * @free_node_data function used to free the list nodes data */
fifo_t *fifo_init(void (*free_data)(void *));

/* Destroy a fifo
 * Params : 
 * @fifo to be destroyed */		
void fifo_destroy(fifo_t *fifo);

/* Add data to the fifo queue
 * Params : 
 * @fifo to add data to 
 * @data to be added*/		
int fifo_enqueue(fifo_t *fifo, void *data);

/* Remove data to the fifo queue
 * Params : 
 * @fifo to remove data from
 */	
void *fifo_dequeue(fifo_t *fifo);

#endif