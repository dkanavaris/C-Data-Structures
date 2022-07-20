#ifndef __LIST_H__
#define __LIST_H__

typedef enum list_return_codes{
	MALLOC_ERROR = -2,
	LIST_IS_NULL = -1
}list_return_t;

typedef struct node {

	struct node *next;
	struct node *prev;
	void *data;
}node_t;


typedef struct list {

	node_t *head;
	node_t *tail;
	unsigned long size;
	
	int (*compare)(void *d1, void *d2);
	void (*free_node_data)(void *);

}list_t;


/* Get node containing @data
 * Returns pointer to node on success
 * NULL otherwise
 * Params : 
 * @list to get node from
 * @data that the node contains */
node_t *get_node(list_t *list, void *data);

/* Initialize a new list
 * Returns a pointer to list_t struct
 * Params : 
 * @compare function used to compare list nodes,
 * @free_node_data function used to free the list nodes data */
list_t *list_init(int (*compare)(void *d1, void *d2), 
					void (*free_node_data)(void *));

/* Destroy a list
 * Params : 
 * @list to be destroyed */					
void list_destroy(list_t *list);

/* Get the list size
 * Returns an unsigned long that is the list size
 * LIST_IS_NULL if list param is NULL
 * Params: 
 * @list to get the size of. */
unsigned long get_list_size(list_t *list);

/* Append to a list
 * Returns 0 on success
 * Params : 
 * @list to append data to,
 * @data to be appended */
int list_append(list_t *list, void *data);

/* Remove node from list
 * Returns 0 on success
 * LIST_IS_NULL if list is NULL
 * Params : 
 * @list to append data to,
 * @data to be removed */
int list_remove(list_t *list, void *data);

/* Check if list contains @data
 * Returns 1 if @data is in list
 * -1 otherwise
 * Params : 
 * @list to check
 * @data that the node contains */
int list_contains(list_t *list, void *data);

/* Insert a node containing @data after node containing @after data.
 * Returns 0 on success
 * -1 if @after is not in list
 * MALLOC_ERROR on malloc error
 * Params : 
 * @list to append data to,
 * @after node to insert data after.
 * @data to be appended */
int list_insert_after(list_t *list, void *after, void *data);

#endif