#include <stdlib.h>
#include "avl_tree.h"
#include "tree.h"

avl_tree *avl_init(int (*compare)(void *d1, void *d2), 
					void (*free_node_data)(void *)){

    return tree_init(compare, free_node_data);
}

void avl_destroy(avl_tree *tree){
    tree_destroy(tree);
}