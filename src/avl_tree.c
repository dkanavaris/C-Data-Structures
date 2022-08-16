#include <stdlib.h>
#include "avl_tree.h"
#include <math.h>

// Helper functions 
int is_left_child(avl_node_t *node){

    if(!node)
        return -1;
    
    return (node->parent->left == node);
}

int is_right_child(avl_node_t *node){

    if(!node)
        return NULL;
    
    return (node->parent->right == node);
}

/**
 * @brief Get the sibling of a node
 * 
 * @param node to get sibling of
 * @return avl_node_t* NULL if no sibling exists,
                        pointer to sibling if it exists
 */
tree_node_t *get_sibling(avl_node_t *node){

    if(node->parent == NULL)
        return NULL;
    
    if(is_left_child(node)){
        return node->parent->right;
    }

    return node->parent->left;
}

/**
 * @brief Swaps two nodes data
 * 
 * @param d1 first node
 * @param d2 second node
 */
void swap_node_data(avl_node_t *d1, avl_node_t *d2){

    void *tmp = d1->data;
    d1->data = d2->data;
    d2->data = tmp;
}

int get_right_son_height(avl_node_t *node){

    if(!node || !node->right)
        return -1;
    
    return node->right->height;
}

int get_left_son_height(avl_node_t *node){
    
    if(!node || !node->left)
        return -1;

    return node->left->height;
}

int remedy_height(avl_node_t *node){

    if(!node)
        return -1;
    
    node->height = (1 + max(get_right_son_height(node), 
                                get_left_son_height(node)));
    return 0;
}

int is_balanced(avl_node_t *node){

    if(!node)
        return -1;
    
    int balance = abs(get_left_son_height(node) - get_right_son_height(node));
    return (balance == 1);
}

void clear_tree_nodes(avl_tree_t *avl_tree, avl_node_t *node){

    if(node->left)
        clear_tree_nodes(node->left);
    if(node->right)
        clear_tree_nodes(node->right);
    
    avl_tree->free_node_data(node);
    free(node);
}

// Main AVL Functions
avl_tree_t *avl_tree_init(int (*compare)(void *d1, void *d2), 
					void (*free_node_data)(void *))
{


    avl_tree_t *avl_tree = (avl_tree_t *)malloc(sizeof(avl_tree_t));
    if(!avl_tree)
        return NULL;
    
    avl_tree->root = NULL;
    avl_tree->compare = compare;
    avl_tree->free_node_data = free_node_data;

    return avl_tree;
}

void avl_tree_destroy(avl_tree_t *avl_tree) {

    if(!avl_tree || !avl_tree->root)
        return;

    clear_tree_nodes(avl_tree, avl_tree->root);
    free(avl_tree);
}
