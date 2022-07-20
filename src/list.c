#include <stdlib.h>
#include "list.h"
#include <stdio.h>

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

unsigned long get_list_size(list_t *list){

    if(!list)
        return LIST_IS_NULL;
    
    return list->size;
}

int list_insert_after(list_t *list, void *after, void *data){
    
    if(!list)
        return LIST_IS_NULL;

    node_t *after_node = get_node(list, after);

    if(!after_node)
        return -1;

    node_t *node = (node_t *)malloc(sizeof(node_t));

    if(!node)
        return MALLOC_ERROR;

    node->next = node->prev = NULL;
    node->data = data;

    if(after_node == list->tail){
        list->tail->next = node;
        node->prev = list->tail;
        list->tail = node;
        (list->size)++;
        return 0;
    }

    node->next = after_node->next;
    node->prev = after_node;
    after_node->next->prev = node;
    after_node->next = node;
    (list->size)++;
    return 0;
}

int list_remove(list_t *list, void *data){

    if(!list)
        return LIST_IS_NULL;

    node_t *curr = get_node(list, data);


    // No such node was found
    if(!curr)
        return -1;

    if(list->size == 1){
        list->head = list->tail = NULL;
        list->size = 0;
    }
    
    else if(curr == list->head){
        curr->next->prev = NULL;
        list->head = curr->next;
        (list->size)--;
    }

    else if(curr == list->tail){
        curr->prev->next = NULL;
        list->tail = curr->prev;
        (list->size)--;
    }

    else{
        curr->next->prev = curr->prev;
        curr->prev->next = curr->next;
        (list->size)--;
    }

    // Free the node
    list->free_node_data(curr->data);
    free(curr);
    return 0;
}

node_t *get_node(list_t *list, void *data){

    node_t *curr;

    for(curr = list->head; curr != NULL; curr = curr->next){
        if(!(list->compare(curr->data, data)))
            return curr;
    }

    return NULL;
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