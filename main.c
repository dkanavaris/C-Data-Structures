#include <stdio.h>
#include <stdlib.h>
#include "./include/list.h"

typedef struct data{
    int value;
}data_t;

int compare(void *d1, void *d2){

    data_t *data1 = d1;
    data_t *data2 = d2;


    return data1->value - data2->value;
}

void free_data(void *d){
    free(d);
}

int main(int argc, char **argv){

    list_t *my_list = list_init(compare, free_data);

    data_t *d1 = (data_t *)malloc(sizeof(data_t));
    data_t *d2 = (data_t *)malloc(sizeof(data_t));
    data_t *d3 = (data_t *)malloc(sizeof(data_t));
    data_t *d4 = (data_t *)malloc(sizeof(data_t));

    d1->value = 10;
    d2->value = 20;
    d3->value = 20;
    d4->value = 40;

    list_append(my_list, d1);
    list_append(my_list, d2);
    list_append(my_list, d3);
    list_append(my_list, d4);

    node_t *curr;

    for(curr = my_list->head; curr != NULL; curr = curr->next){
        data_t *node_data = curr->data;
        printf("%d-", node_data->value);
    }

    printf("\n");

    list_destroy(my_list);
    return 0;
}