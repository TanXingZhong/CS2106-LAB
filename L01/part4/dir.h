#include "llist.h"

// Add prototypes and other declarations below
void writelog(char *);
void init_hashtable(TLinkedList *[], int);
TLinkedList *get_filelist(char *, int (*hashfun)(char *, int), TLinkedList *[], int);
void update_hashtable(char *, int (*hashfun)(char *, int), TLinkedList *[], int, TLinkedList *);
TLinkedList *find_file(char *, int (*hashfun)(char *, int), TLinkedList *[], int);
void add_file(char *, int, int, int (*hashfun)(char *, int), TLinkedList *[], int);
void delete_file(char *, int (*hashfun)(char *, int), TLinkedList *[], int);
void rename_file(char *, char *, int (*hashfun)(char *, int), TLinkedList *[], int);
void print_node(TLinkedList *node);
void listdir(TLinkedList *[], int);
void clear_hashtable(TLinkedList *[], int);

