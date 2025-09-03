#ifndef CONCURRENTLINKEDLIST_LINKEDLIST_H
#define CONCURRENTLINKEDLIST_LINKEDLIST_H

#include <stddef.h>

typedef struct Node {
    int data;
    struct Node *next;
} Node;

typedef struct {
    Node* head;
} linkedlist_t;

linkedlist_t* create_linkedlist();
void list_init(void);


int Member(int value);
int Insert(int value);
int Delete(int value);

void list_free(void);

size_t list_count(void);

void list_free(void);

void print_list(void);

#endif //CONCURRENTLINKEDLIST_LINKEDLIST_H
