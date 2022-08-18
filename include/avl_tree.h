#ifndef __AVL_TREE_H__
#define __AVL_TREE_H__

#include "tree.h"

typedef tree_t avl_tree;
typedef tree_node_t avl_node;

typedef struct info{
    int height;
}info_t;

avl_tree *avl_init(int (*compare)(void *d1, void *d2), 
					void (*free_node_data)(void *));

void avl_destroy(avl_tree *tree);

int avl_insert(avl_tree *tree, void *data);

#endif