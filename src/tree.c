#include <stdlib.h>
#include "tree.h"

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

/* Search for tree node containing @data
 * Returns a pointer to the tree node containing @data.
 * If the tree is empty NULL is returned.
 * If the data does not exist then the parent node of the data to be
 * inserted is returned. That means that the caller must check what @data
 * was returned 
 * */
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
