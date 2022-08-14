#include <stdlib.h>
#include "tree.h"

// Helper functions
/**
 * @brief Check if node is a left child
 * 
 * @param node to check
 * @return int 1 if node is left child, 0 otherwise
 */
int is_left_child(tree_node_t *node){

    if(!node)
        return -1;

    return (node->parent->left == node);
}

/**
 * @brief Check if node is a right child
 * 
 * @param node to check
 * @return int 1 if node is right child, 0 otherwise
 */
int is_right_child(tree_node_t *node){
    if(!node)
        return -1;
    
    return (node->parent->right == node);
}

/**
 * @brief Get the sibling of a node
 * 
 * @param tree 
 * @param node to get sibling of
 * @return tree_node_t* NULL if no sibling exists,
                        pointer to sibling if it exists
 */
tree_node_t *get_sibling(tree_t *tree, tree_node_t *node){

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
void swap_node_data(tree_node_t *d1, tree_node_t *d2){

    void *tmp = d1->data;
    d1->data = d2->data;
    d2->data = tmp;
}

/**
 * @brief Search the tree starting from root for data
 * 
 * @param tree to search
 * @param root to start from
 * @param data 
 * @return tree_node_t* pointer to tree_node containing data
 */
tree_node_t *search_node(tree_t *tree, tree_node_t *root, void *data){

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

// General tree functions
tree_t *tree_init(int (*compare)(void *d1, void *d2), 
					void (*free_node_data)(void *))
{

    tree_t *tree = (tree_t *)malloc(sizeof(tree_t));
    if(!tree){
        return NULL;
    }

    tree->root = NULL;
    tree->compare = compare;
    tree->free_node_data = free_node_data;

    return tree;
                
}

void clear_tree_nodes(tree_t *tree, tree_node_t *node){

    if(node->left)
        clear_tree_nodes(tree, node->left);
    if(node->right)
        clear_tree_nodes(tree, node->right);
    
    tree->free_node_data(node->data);
    free(node);
}

void tree_destroy(tree_t *tree){

    if(!tree || !tree->root)
        return;
    
    clear_tree_nodes(tree, tree->root);
    free(tree);
}

tree_node_t *tree_insert(tree_t *tree, void *data){

    if(!tree){
        return NULL;
    }

    tree_node_t *parent_node = search_node(tree, tree->root, data);
    
    // Data already exists in the tree
    if(parent_node && tree->compare(parent_node->data, data) == 0)
        return parent_node;

    tree_node_t *node = (tree_node_t *)malloc(sizeof(tree_node_t));
    if(!node){
        return NULL;
    }

    node->data = data;
    node->left = node->right = NULL;
    node->parent = parent_node;

    if(parent_node == NULL){
        tree->root = node;
        return tree->root;
    }

    if(tree->compare(parent_node->data, data) < 0)
        parent_node->right = node;
    else
        parent_node->left = node;

    return node;
}

int tree_contains(tree_t *tree, void *data){

    if(!tree)
        return -1;
    
    tree_node_t *node = search_node(tree, tree->root, data);

    if(!node)
        return -1;

    return (tree->compare(node->data, data));
}

tree_node_t *tree_remove(tree_t *tree, void *data){
    
    if(!tree)
        return NULL;

    tree_node_t *node = search_node(tree, tree->root, data);
    
    // No such data in the tree
    if(!node)
        return NULL;

    // No such data in the tree
    if(tree->compare(node->data, data) != 0)
        return NULL;

    tree_node_t *curr_node;
    tree_node_t *return_node;

    if(node->left && node->right){
        curr_node = node->right;

        while(curr_node->left)
            curr_node = curr_node->left;

        //Swap the data
        swap_node_data(node, curr_node);
        node = curr_node;
    }

    if(node->left)
        node->left->parent = node->parent;
    else if(node->right)
        node->right->parent = node->parent;

    if(tree->root == node){
        tree->root = (node->left != NULL ? node->left : node->right);
        return_node = tree->root;
    }

    else if(is_left_child(node)){
        node->parent->left = (node->left != NULL ? node->left : node->right);
        return_node = node->parent;
    }

    else{
        node->parent->right = (node->left != NULL ? node->left : node->right);
        return_node = node->parent;
    }

    tree->free_node_data(node->data);
    free(node);
    return return_node;
}