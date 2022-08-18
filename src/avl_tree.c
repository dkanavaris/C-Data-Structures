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

int avl_contains(avl_tree *tree, void *data){
    return tree_contains(tree, data);
}

int avl_insert(avl_tree *tree, void *data){

    tree_node_t *node = tree_insert(tree, data);
    
    if(!node)
        return -1;
    
    info_t *info = (info_t *)malloc(sizeof(info_t));

    if(!info)
        return -1;

    info->height = 1;
    node->info = info;

    return 0;
}