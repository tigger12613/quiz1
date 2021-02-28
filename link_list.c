#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "link_list.h"


void list_add_node_t(node_t **list, node_t *node_t) {
    node_t->next = *list;
    *list = node_t;
}

void list_concat(node_t **left, node_t *right) {
    while (*left)
        left = &((*left)->next);
    *left = right;
}

void quicksort(node_t **list)
{
    if (!*list)
        return;

    node_t *pivot = *list;
    int value = pivot->value;
    node_t *p = pivot->next;
    pivot->next = NULL;

    node_t *left = NULL, *right = NULL;
    while (p) {
        node_t *n = p;
        p = p->next;
        list_add_node_t(n->value > value ? &right : &left, n);
    }

    quicksort(&left);
    quicksort(&right);

    node_t *result = NULL;
    list_concat(&result, left);
    list_concat(&result, pivot); list_concat(&result, right);
    *list = result;
}

void quicksort_iterative(node_t **list)
{
    #define  MAX_LEVELS  1000
    if (!*list)
        return;
    int i = 0, j = 0;
    node_t *stack[MAX_LEVELS];
    node_t *sorted;
    sorted = NULL;
    stack[0] = *list;
    //printf("s1\n");
    while(i>=0 && i<MAX_LEVELS){
        if(!stack[i]){
            i--;
            continue;
        }
        if(!stack[i]->next){
            stack[i]->next = sorted;
            sorted = stack[i];
            i--;
            /*
            printf("sorted ");
            list_display(sorted);
            */
            continue;
        }
        node_t *pivot = stack[i];
        int value = pivot->value;
        node_t *p = pivot->next;
        pivot->next = NULL;
        node_t *left = NULL, *right = NULL;
        while (p) {
            node_t *n = p;
            p = p->next;
            list_add_node_t(n->value > value ? &right : &left, n);
        }
        /*
        printf("l ");
        list_display(left);
        printf("p ");
        list_display(pivot);
        printf("r ");
        list_display(right);
        */
        stack[i] = left;
        stack[i+1] = pivot;
        stack[i+2] = right;
        i +=2;
    }
    *list = sorted;
}

bool list_is_ordered(node_t *list) {
    bool first = true;
    int value;
    while (list) {
        if (first) {
            value = list->value;
            first = false;
        } else {
            if (list->value < value)
                return false;
            value = list->value;
        }
        list = list->next;
    }
    return true;
}

void list_display(node_t *list) {
    printf("%s IN ORDER : ", list_is_ordered(list) ? "   " : "NOT");
    while (list) {
        printf("%d ", list->value);
        list = list->next;
    }
    printf("\n");
}

node_t *list_make_node_t(node_t *list, long num){
    node_t *tmp = malloc(sizeof(node_t));
    if (!tmp){
        return list;
    }
    tmp->value = num;
    tmp->next = list;
    return tmp;
}

void list_free(node_t **list){
    node_t *tmp;
    while (*list)
    {
        tmp = *list;
        *list = (*list)->next;
        free(tmp);
    }
}

int main(int argc, char **argv) {
    size_t count = 100;

    node_t *list = NULL;
    srand(time(NULL));
    while (count--)
        list = list_make_node_t(list, random() % 1024);

    list_display(list);
    quicksort_iterative(&list);
    list_display(list);

    if (!list_is_ordered(list))
        return EXIT_FAILURE;

    list_free(&list);
    return EXIT_SUCCESS;
}