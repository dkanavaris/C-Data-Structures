#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tree.h"

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

    tree_t *tree = tree_init(compare, free_data);

    data_t *d1 = (data_t *)malloc(sizeof(data_t));
    data_t *d2 = (data_t *)malloc(sizeof(data_t));
    data_t *d3 = (data_t *)malloc(sizeof(data_t));
    data_t *d4 = (data_t *)malloc(sizeof(data_t));
    data_t *d5 = (data_t *)malloc(sizeof(data_t));
    data_t *d6 = (data_t *)malloc(sizeof(data_t));
    data_t *d7 = (data_t *)malloc(sizeof(data_t));
    data_t *d8 = (data_t *)malloc(sizeof(data_t));
    data_t *d9 = (data_t *)malloc(sizeof(data_t));

    d1->value = "A";
    d2->value = "B";
    d3->value = "C";
    d4->value = "D";
    d5->value = "E";
    d6->value = "F";
    d7->value = "G";
    d8->value = "H";
    d9->value = "I";

    tree_insert(tree, d6);
    tree_insert(tree, d2);
    tree_insert(tree, d1);
    tree_insert(tree, d4);
    tree_insert(tree, d3);
    tree_insert(tree, d5);
    tree_insert(tree, d7);
    tree_insert(tree, d9);
    tree_insert(tree, d8);



    // PRE_ORDER
    print_preorder(tree->root);
    printf("\n");

    // print_inorder(tree->root);
    // printf("\n");
    
    // print_postorder(tree->root);
    // printf("\n");

    tree_remove(tree, d6);
    tree_remove(tree, d5);
    tree_remove(tree, d4);
    tree_remove(tree, d3);
    tree_remove(tree, d2);
    tree_remove(tree, d1);
    tree_remove(tree, d7);
    tree_remove(tree, d8);
    tree_remove(tree, d9);

    // print_preorder(tree->root);
    // printf("\n");

    // data_t my_data;
    // my_data.value = "A";
    // printf("Tree contains A : %d\n", tree_contains(tree, &my_data));

    // my_data.value = "O";
    // printf("Tree contains O : %d\n", tree_contains(tree, &my_data));

    tree_destroy(tree);
    return 0;
}