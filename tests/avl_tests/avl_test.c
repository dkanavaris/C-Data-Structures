#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "avl_tree.h"

typedef struct data{
    char *value;
}data_t;

int compare(void *d1, void *d2){

    data_t *data1 = d1;
    data_t *data2 = d2;


    return strcmp(data1->value, data2->value);
}

void free_data(void *d){
    free(d);
}

void print_preorder(tree_node_t *root){

    data_t *data = root->data;
    printf("%s-", data->value);

    if(root->left)
        print_preorder(root->left);
    if(root->right)
        print_preorder(root->right);
}

void print_inorder(tree_node_t *root){

    if(root->left)
        print_inorder(root->left);
    
    data_t *data = root->data;
    printf("%s-", data->value);

    if(root->right)
        print_inorder(root->right);
}

void print_postorder(tree_node_t *root){

    if(root->left)
        print_postorder(root->left);

    if(root->right)
        print_postorder(root->right);
    
    data_t *data = root->data;
    printf("%s-", data->value);

}

int main(int argc, char **agrv){

    avl_tree *tree = avl_init(compare, free_data);

    avl_destroy(tree);
    return 0;
}