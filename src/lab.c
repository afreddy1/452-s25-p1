#include "lab.h"
#include <stdio.h>
#include <string.h>

list_t *list_init(void (*destroy_data)(void *), int ((*compare_to)(const void *, const void *)) {
    list_t *list = (list_t *) malloc(sizeof(list_t));
    if (!list) return NULL;

    node_t *sentinel = (node_t *)malloc(sizeof(node_t));

    if (!sentinel) {
        free(list);
        return NULL;
    }

    sentinel->data = NULL;
    sentinel->next = sentinel;
    sentinel->prev = sentinel;

    list->head = sentinel;
    list->destroy_data = destroy_data;
    list->compare_to = compare_to;
    list->size = 0;

    return list;
}

void list_destroy(list_t **list) {
    if(!list || !(*list)) return;

    node_t *current = (*list)->head->next;

    while(current != (*list)->head) {
        node_t *next = current->next;
        if((*list)->destroy_data) {
            (*list)->destroy_data(current->data);
        }
        free(current);
        current = next;
    }
    
    free((*list)->head);
    free(*list);
    *list = NULL;
}