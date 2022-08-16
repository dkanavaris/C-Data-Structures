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

/**
 * @brief Search the tree starting from root for data
 * 
 * @param tree to search
 * @param root to start from
 * @param data 
 * @return tree_node_t* pointer to tree_node containing data
 */
avl_node_t *search_node(avl_tree_t *tree, avl_node_t *root, void *data){

    if(!root)
        return NULL;
    
    if(tree->compare(root->data, data) == 0)
        return root;

    else if (tree->compare(root->data, data) < 0 && root->right)
        return search_node(tree, root->right, data);
    
    else if (tree->compare(root->data, data) > 0 && root->left) 
        return search_node(tree, root->left, data);
    
    return root;
}

// Find the node that will take part in recostrunction
// depending on the children height.
avl_node_t *rebalance_son(avl_node_t *node){
    if(!node)
        return NULL;

    if(get_left_son_height(node) > get_right_son_height())
        return node->left;
    else if(get_right_son_height(node) > get_left_son_height(node))
        return node->right;
    
    if(is_left_child(node))
        return node->left;
    
    return node->right;
}

//TODO: Implement this
avl_node_t *reconstruct(avl_node_t *v, avl_node_t *w, avl_node_t *u){
    return NULL;
}

// Rebalance node`
void rebalance(avl_node_t *node){

    // Go up the root
    while(node){
        remedy_height(node); // Updat the height
        if(!is_balanced(node)){ // Check if balancing is needed
            avl_node_t *w = rebalance_son(node);
            avl_node_t *u = rebalance_son(w);
            
            node = reconstruct(node, w, u); // Reconstruct the tree
            remedy_height(node->left); // Update children heights
            remedy_height(node->right);
            remedy_height(node);
        }
        node = node->parent; // Continue with rebalancing the parent
    }
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

avl_node_t *avl_tree_insert(avl_tree_t *tree, void *data){

    if(!tree){
        return NULL;
    }

    avl_node_t *parent_node = search_node(tree, tree->root, data);
    
    // Data already exists in the tree
    if(parent_node && tree->compare(parent_node->data, data) == 0)
        return parent_node;

    avl_node_t *node = (avl_node_t *)malloc(sizeof(avl_node_t));
    if(!node){
        return NULL;
    }

    node->data = data;
    node->left = node->right = NULL;
    node->parent = parent_node;
    node->height = 0;

    if(parent_node == NULL){
        tree->root = node;
        return tree->root;
    }

    if(tree->compare(parent_node->data, data) < 0)
        parent_node->right = node;
    else
        parent_node->left = node;

    rebalance(node);
    // Rebalance the son now
    return node;
}
