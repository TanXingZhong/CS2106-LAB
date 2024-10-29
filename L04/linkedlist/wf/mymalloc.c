#include <stdio.h>
#include <stdlib.h>
#include "mymalloc.h"
#include "llist.h"
#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define MIN(a, b) ((a) < (b) ? (a) : (b))

char _heap[MEMSIZE] = {0};
TNode *_memlist = NULL; // To maintain information about length


// Do not change this. Used by the test harness.
// You may however use this function in your code if necessary.
    long get_index(void *ptr) {
        if(ptr == NULL)
        return -1;
    else
        return (long) ((char *) ptr - &_heap[0]);
}
// void process_list(TNode *llist, void (*func)(TNode *));

void printer(TNode *node) {
    printf("Status: %s Start index: %d Length: %d\n", node->pdata->status == 0 ? "FREE" : "ALLOCATED", node->key, node->pdata->length);
}

void print_memlist() {
    process_list(_memlist, printer);
}

// Allocates size bytes of memory and returns a pointer
// to the first byte.
void *mymalloc(size_t size) {
    if (_memlist == NULL) {
        TData *data = (TData *) malloc(sizeof(TData));
        data->status = 0;
        data->length = MEMSIZE;
        TNode *node = make_node(0, data);
        insert_node(&_memlist, node, ASCENDING);
    }

    reset_traverser(_memlist, FRONT);
    TNode *current = succ(_memlist);
    int biggest = -1;
    int worstfit_key = -1;
    while(current != NULL) {
        if(current->pdata->length >= size && current->pdata->status != 1) {
            if(biggest < current->pdata->length) {
                biggest = current->pdata->length;
                worstfit_key = current->key;
            }
        } current = succ(_memlist);
    }

    if(worstfit_key == -1) {
        return (void *) NULL;
    }

    TNode *worstfit_NODE = find_node(_memlist, worstfit_key);

    TData *new_Data = (TData *) malloc(sizeof(TData));
    new_Data->status = 1;
    new_Data->length = size;
    TNode *new_Node = make_node(worstfit_NODE->key, new_Data);

    worstfit_NODE->key += size;
    worstfit_NODE->pdata->length -= size;
    if(worstfit_NODE->pdata->length == 0) {
        delete_node(&_memlist, worstfit_NODE);
    }
    insert_node(&_memlist, new_Node, ASCENDING);

    return _heap + new_Node->key;
}

// Frees memory pointer to by ptr.
void myfree(void *ptr) {
    long idx = get_index(ptr);
    if(idx == -1) {
        return;
    }

    TNode *toFree = find_node(_memlist, idx);
    if (toFree == NULL) {
        return;
    }
    toFree->pdata->status = 0;

    if(toFree->next != NULL && toFree->next->pdata->status == 0) {
        toFree->pdata->length += toFree->next->pdata->length;
        merge_node(_memlist, toFree, SUCCEEDING);
    }

    if(toFree->prev != NULL && toFree->prev->pdata->status == 0) {
        toFree->prev->pdata->length += toFree->pdata->length;
        merge_node(_memlist, toFree, PRECEDING);
    }
}


