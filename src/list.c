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


/* Get the list size
 * Returns an unsigned long that is the list size
 * LIST_IS_NULL if list param is NULL
 * Params: 
 * @list to get the size of. */
unsigned long get_list_size(list_t *list){

    if(!list)
        return LIST_IS_NULL;
    
    return list->size;
}

/* Insert a node containing @data after node containing @after data.
 * Returns 0 on success
 * -1 if @after is not in list
 * MALLOC_ERROR on malloc error
 * Params : 
 * @list to append data to,
 * @after node to insert data after.
 * @data to be appended */
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

/* Remove node from list
 * Returns 0 on success
 * LIST_IS_NULL if list is NULL
 * Params : 
 * @list to append data to,
 * @data to be removed 
 * NOTICE the end user is responsible for freeing the memory allocated for data*/
void *list_remove(list_t *list, void *data){

    if(!list)
        return NULL;

    node_t *curr = get_node(list, data);


    // No such node was found
    if(!curr)
        return NULL;

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
    void *return_data = curr->data;
    free(curr);
    return return_data;
}

/* Remove node from list
 * Returns 0 on success
 * LIST_IS_NULL if list is NULL
 * Params : 
 * @list to append data to,
 * @index of node to be removed 
 * NOTICE the end user is responsible for freeing the memory allocated for data*/
void *list_pop(list_t *list, int index){
    if(index < 0 || index > (list->size - 1))
        return NULL;

    if(index == 0){
        return list_remove(list, list->head->data);
    }

    else if(index == (list->size - 1)){
        return list_remove(list, list->tail->data);
    }

    
    node_t *curr_node;
    int curr_index = 0;
    for(curr_node = list->head; curr_node != NULL && curr_index != index; 
                                curr_node = curr_node->next,curr_index++);

    return list_remove(list, curr_node->data);
    

}
/* Get node containing @data
 * Returns pointer to node on success
 * NULL otherwise
 * Params : 
 * @list to get node from
 * @data that the node contains */
node_t *get_node(list_t *list, void *data){

    node_t *curr;

    for(curr = list->head; curr != NULL; curr = curr->next){
        if(!(list->compare(curr->data, data)))
            return curr;
    }

    return NULL;
}

/* Check if list contains @data
 * Returns 1 if @data is in list
 * -1 otherwise
 * Params : 
 * @list to get node from
 * @data that the node contains */
int list_contains(list_t *list, void *data){

    if(!list)
        return LIST_IS_NULL;
    
    node_t *curr;

    for(curr = list->head; curr != NULL; curr = curr->next){
        if(!(list->compare(curr->data, data)))
            return 1;
    }

    return -1;
}   