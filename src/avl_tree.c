#include <stdlib.h>
#include "avl_tree.h"
#include "tree.h"
#include <math.h>

//Helper functions
int get_right_son_height(avl_node *node){
    if(!node)
        return -1;
    
    return node->right != NULL ? ((info_t *)(node->right->info))->height : 0;
}

int get_left_son_height(avl_node *node){
    if(!node)
        return -1;
    
    return node->left != NULL ? ((info_t *)(node->left->info))->height : 0;
}

void remedy_height(avl_node *node){
    if(!node)
        return;
    
    
    ((info_t *)(node->info))->height = (1 + 
                                fmax(get_left_son_height(node), get_right_son_height(node)));
}

int is_balanced(avl_node *node){

    if(!node)
        return 0;
    
    int balance = get_left_son_height(node) - get_right_son_height(node);

    return ((-1 <= balance) && (balance <= 1));
}

avl_node *rebalance_son(avl_node *node){

    if(!node)
        return NULL;

    
    if(get_left_son_height(node) > get_right_son_height(node))
        return node->left;
    
    else if(get_left_son_height(node) < get_right_son_height(node))
        return node->right;

    else if(is_left_child(node))
        return node->left;
    
    return node->right;
}

avl_node *reconstruct(avl_node *v, avl_node *w, avl_node *u){
    return NULL;
}

void rebalance(avl_node *node){

    if(!node)
        return;
    
    while(node){
        remedy_height(node);
        if(!is_balanced(node)){
            avl_node *w = rebalance_son(node);
            avl_node *u = rebalance_son(w);
            node = reconstruct(node, w, u);
            remedy_height(node->left);
            remedy_height(node->right);
            remedy_height(node);
        }
        node = node->parent;
    }
}

// Main functions
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

    rebalance(node); // Rebalance the inserted node
    return 0;
}