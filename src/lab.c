#include "lab.h"
#include <stdio.h>
#include <string.h>

list_t *list_init(void (*destroy_data)(void *), int ((*compare_to)(const void *, const void *))) {
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


list_t *list_add(list_t *list, void *data) {

    if(!list) return NULL;

    node_t *new_node = (node_t *)malloc(sizeof(node_t));
    if (!new_node) return NULL;

    new_node->data = data;

    node_t *sentinel = list->head;
    node_t *first = sentinel-> next;

    new_node->next = first;
    new_node->prev = sentinel;

    first->prev = new_node;
    sentinel->next = new_node;

    list->size++;
    return list;
}

void *list_remove_index(list_t *list, size_t index) {
    if(!list || index >= list->size) return NULL;

    node_t *current = list->head->next;

    for(size_t i = 0; i < index; i++) {
        current = current->next; 
    }

    node_t *prev = current ->prev;
    node_t *next = current->next;

    prev->next = next;
    next->prev = prev;

    void *data = current->data;
    free(current);
    list->size--;
    
    return data;
}

int list_indexof(list_t *list, void *data) {
    if(!list) return -1;

    node_t *current = list->head->next;
    size_t index = 0;

    while(current != list->head) {
        if(list->compare_to(data, current->data) ==0) {
            return index;
        }
        current = current->next;
        index++;
    }

    return -1;
}