#include <stdio.h>
#include <stdlib.h>
#include "mymalloc.h"
#include "llist.h"
#include "bitmap.h"

typedef struct PtrSize {
    void *ptr;              
    int size;            
    struct PtrSize *next; 
} PtrSize;

PtrSize *ptrSizeList = NULL;

char _heap[MEMSIZE] = {0};
TNode *_memlist = NULL; // To maintain information about length
unsigned char bitmap[MEMSIZE / 8] = {0};

// Do not change this. Used by the test harness.
// You may however use this function in your code if necessary.
long get_index(void *ptr) {
    if(ptr == NULL)
        return -1;
    else
        return (long) ((char *) ptr - &_heap[0]);
}

void print_memlist() {
    print_map(bitmap, MEMSIZE / 8);
}

// Allocates size bytes of memory and returns a pointer
// to the first byte.
void *mymalloc(size_t size) {
    long idx = search_map(bitmap, MEMSIZE / 8, size);
    if (idx != -1) {
        allocate_map(bitmap, idx, size);
        PtrSize *newNode = malloc(sizeof(PtrSize));
        newNode->ptr = (void *)(&_heap[idx]);
        newNode->size = size;
        newNode->next = ptrSizeList; 
        ptrSizeList = newNode;      
        return (void *) (&_heap[idx]);
    } else {
        return (void *) NULL;
    }
}


// Frees memory pointer to by ptr.
void myfree(void *ptr) {
    if (ptr == NULL) {
        return;
    }

    PtrSize *current = ptrSizeList;
    PtrSize *previous = NULL;

    while (current != NULL) {
        if (current->ptr == ptr) {
            int size = current->size;
            long idx = get_index(ptr);
            free_map(bitmap, idx, size);
            if (previous == NULL) {
                ptrSizeList = current->next; 
            } else {
                previous->next = current->next;
            }
            free(current);
            return;
        }
        previous = current;
        current = current->next;
    }
}
