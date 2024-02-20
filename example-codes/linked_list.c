#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Node {
    int value;
    struct Node* next;
    struct Node* prev;
} Node;

Node* new_node(int value) {
    Node* node = (Node*) malloc(sizeof(Node));
    node->value = value;
    node->next = NULL;
    node->prev = NULL;

    return node;
}

Node* new_head(void) {
    return new_node(0);
}

void push_node(Node* head, int value) {
    Node* node = new_node(value);

    if (head->next == NULL) {
        node->prev = head;
        head->next = node;
    } else {
        push_node(head->next, value);
    }
}

void pop_node(Node* head) {
    if (head->next == NULL) {
        if (head->prev == NULL)
            return;

        head->prev->next = NULL;
        free(head);
    } else {
        pop_node(head->next);
    }
}

void destroy_head(Node* head) {
    Node *current = head->next;

    while (current != NULL) {
        Node* next = current->next;
        free(current);
        current = next;
    }

    free(head);
}
