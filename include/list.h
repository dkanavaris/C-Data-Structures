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

list_t *list_init(int (*compare)(void *d1, void *d2), 
					void (*free_node_data)(void *));
void list_destroy(list_t *list);

node_t *get_node(list_t *list, void *data);

unsigned long get_list_size(list_t *list);

int list_append(list_t *list, void *data);

void *list_remove(list_t *list, void *data);

int list_contains(list_t *list, void *data);

int list_insert_after(list_t *list, void *after, void *data);

void *list_pop(list_t *list, int index);
#endif