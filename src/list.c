#include <stdlib.h>
#include "list.h"

/* Initialize a new list
 * Returns a pointer to list_t struct
 * Params : 
 * @compare function used to compare list nodes,
 * @free_node_data function used to free the list nodes data */
list_t *list_init(int (*compare)(void *d1, void *d2), 
					        void (*free_node_data)(void *)){

    // Allocate memory for a new list
    list_t *list = (list_t *)malloc(sizeof(list_t)); 

    if(!list)
        return NULL;
    
    // Init the list
    list->head = NULL;
    list->tail = NULL;
    list->size = 0;
    list->compare = compare;
    list->free_node_data = free_node_data;

    // Return a pointer to the newly created list
    return list;
}

/* Destroy a list
 * Params : 
 * @list to be destroyed */
void list_destroy(list_t *list){

    if(!list)
        return;

    node_t *curr, *next;

    curr = list->head;

    while(curr){
        next = curr->next;
        list->free_node_data(curr->data); // Free the node data
        free(curr);  // Free the node
        curr = next;
    }

    free(list); // Finally free the list
}



/* Append to a list
 * Returns 0 on success
 * Params : 
 * @list to append data to,
 * @data to be appended */
int list_append(list_t *list, void *data){

    if(!list)
        return LIST_IS_NULL;

    node_t *node = (node_t *)malloc(sizeof(node_t));

    if(!node)
        return MALLOC_ERROR;

    node->next = node->prev = NULL;
    node->data = data;

    if(list->size == 0){
        list->head = list->tail = node;
        (list->size)++;
        return 0;
    }

    node->prev = list->tail;
    list->tail->next = node;
    list->tail = node;
    (list->size)++;

    return 0;
}

int list_contains(list_t *list, void *data){

    if(!list)
        return LIST_IS_NULL;
    
    node_t *curr;

    for(curr = list->head; curr != NULL; curr = curr->next){
        if(!(list->compare(curr->data, data)))
            return 1;
    }

    return 0;
}   