#ifndef __AVL_TREE_H__
#define __AVL_TREE_H__

typedef struct avl_node{

    struct avl_node *left;
    struct avl_node *right;
    struct avl_node *parent;
    void *data;
    int height;
}avl_node_t;

typedef struct avl_tree{
    avl_node_t *root;
    int (*compare)(void *d1, void *d2);
	void (*free_node_data)(void *);
}avl_tree_t;

avl_tree_t *avl_tree_init(int (*compare)(void *d1, void *d2), 
					void (*free_node_data)(void *))

void avl_tree_destroy(avl_tree_t *avl_tree);

avl_node_t *avl_tree_insert(avl_tree_t *avl_tree, void *data);

#endif