#include <stdio.h>
#include <stdlib.h>
#include "Linkedlist.h"

static Node *head = NULL;

void list_init(void){
    head = NULL;
}

int Member(int value) {
    Node *curr = head;
    while (curr != NULL) {
        if (curr->data == value) return 1;
        curr = curr->next;
    }
    return 0;
}

int Insert(int value) {
    Node *curr = head;
    while (curr != NULL) {
        curr = curr->next;
    }
    Node *n = (Node*) malloc(sizeof(Node));
    if (!n) return 0;
    n->data = value;
    n->next = head;
    head = n;
    return 1;
}

int Delete(int value) {
    Node *curr = head;
    Node *prev = NULL;
    while (curr !=NULL && curr->data != value) {
        prev = curr;
        curr = curr->next;
    }
    if (curr == NULL) return 0;
    if (prev == NULL) {
        head = curr->next;
    } else {
        prev->next = curr->next;
    }
    free(curr);
    return 1;
}

size_t list_count(void) {
    size_t c = 0;
    Node *curr = head;
    while (curr) {c++; curr = curr->next; }
    return c;
}

void list_free(void) {
    Node *curr = head;
    while (curr != NULL) {
        Node *next = curr->next;
        free(curr);
        curr = next;
    }
    head = NULL;
}

void print_list(void) {
    Node *curr = head;
    printf("List: ");
    while (curr) {
        printf("%d -> ", curr->data);
        curr = curr->next;
    }
    printf("NULL\n");
}