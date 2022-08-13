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

tree_t *tree_init(int (*compare)(void *d1, void *d2), 
					void (*free_node_data)(void *));

void tree_destroy(tree_t *tree);

int tree_contains(tree_t *tree, void *data);
tree_node_t *tree_insert(tree_t *tree, void *data);
int tree_remove(tree_t *tree, void *data);
#endif