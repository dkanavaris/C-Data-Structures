#include <stdio.h>
#include <stdlib.h>
#include "list.h"

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

void print_list(list_t *list){
    node_t *curr;

    for(curr = list->head; curr != NULL; curr = curr->next){
        data_t *node_data = curr->data;
        printf("%d-", node_data->value);
    }

    printf("\n");
    // if(list->head){
    //     data_t *head = list->head->data;
    //     data_t *tail = list->tail->data;
    //     printf("Head at %d\nTail at %d\n", head->value, tail->value);
    // }
}

int main(int argc, char **argv){

    list_t *my_list = list_init(compare, free_data);

    data_t *d1 = (data_t *)malloc(sizeof(data_t));
    data_t *d2 = (data_t *)malloc(sizeof(data_t));
    data_t *d3 = (data_t *)malloc(sizeof(data_t));
    data_t *d4 = (data_t *)malloc(sizeof(data_t));
    data_t *d5 = (data_t *)malloc(sizeof(data_t));
    data_t *d6 = (data_t *)malloc(sizeof(data_t));
    data_t *d7 = (data_t *)malloc(sizeof(data_t));
    data_t *d8 = (data_t *)malloc(sizeof(data_t));

    d1->value = 10;
    d2->value = 20;
    d3->value = 30;
    d4->value = 40;
    d5->value = 50;
    d6->value = 60;
    d7->value = 70;
    d8->value = 80;

    list_append(my_list, d1);
    list_append(my_list, d2);
    list_append(my_list, d3);
    list_append(my_list, d4);
    list_append(my_list, d5);


    print_list(my_list);
    
    list_insert_after(my_list, d5, d6);
    print_list(my_list);

    list_insert_after(my_list, d1, d7);
    print_list(my_list);
    
    list_insert_after(my_list, d3, d8);
    print_list(my_list);


    void *get_data = list_pop(my_list, 0);
    print_list(my_list);
    free(get_data);

    list_reverse(my_list);
    print_list(my_list);
    
    // Remove head
    list_remove(my_list, d6);
    free(d6);
    print_list(my_list);

    // Remove tail
    list_remove(my_list, d7);
    free(d7);
    print_list(my_list);

    // Remove middle
    list_remove(my_list, d8);
    free(d8);
    print_list(my_list);


    list_destroy(my_list);

    
    return 0;
}