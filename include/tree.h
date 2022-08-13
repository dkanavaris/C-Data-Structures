#ifndef __TREE_H__
#define __TREE_H__

typedef struct tree_node {
    void *data;
    struct tree_node *parent;
    struct tree_node *left;
    struct tree_node *right;
}tree_node_t;

typedef struct tree{
    tree_node_t *root;
    int (*compare)(void *d1, void *d2);
	void (*free_node_data)(void *);

}tree_t;

/**
 * @brief Create and initialize a new tree
 * 
 * @param compare function to compare tree nodes
 * @param free_node_data function to free data of each tree node
 * @return tree_t* pointer to a new tree
 */
tree_t *tree_init(int (*compare)(void *d1, void *d2), 
					void (*free_node_data)(void *));


void tree_destroy(tree_t *tree);

/**
 * @brief Checks if tree contains data
 * 
 * @param tree to search
 * @param data to search tree for
 * @return int 0 if data exists non-zero integer otherwise
 */
int tree_contains(tree_t *tree, void *data);

/**
 * @brief Insert a new node containing data to the tree.
 * If the data already exists it is not added.
 *
 * @param tree to insert data to 
 * @param data to be inserted
 * @return tree_node_t* pointer to the newly inserted tree_node
 */
tree_node_t *tree_insert(tree_t *tree, void *data);

/**
 * @brief Remove the tree_node containg data from the tree
 * 
 * @param tree to remove data from
 * @param data to be removed
 * @return tree_node_t* pointer to the parent of the removed node
 *                        NULL if no such node exists
 */
tree_node_t *tree_remove(tree_t *tree, void *data);
#endif