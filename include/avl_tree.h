#ifndef __AVL_TREE_H__
#define __AVL_TREE_H__

#include "tree.h"

typedef tree_t avl_tree;

avl_tree *avl_init(int (*compare)(void *d1, void *d2), 
					void (*free_node_data)(void *));

void avl_destroy(avl_tree *tree);


#endif