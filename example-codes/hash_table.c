#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define TABLE_SIZE 64

int ascii_sum(char str[]) {
    int sum = 0;

    for (int i = 0; i < strlen(str); i++)
        sum += (int)str[i];

    return sum;
}

int hash(char key[]) {
    return ascii_sum(key) % TABLE_SIZE;
}

typedef struct {
    char key[64];
    int value;
} Node;

Node new_node(char key[], int value) {
    Node n;
    n.value = value;
    strcpy(n.key, key);

    return n;
}

Node empty_node(void) {
    return (Node) {
        .key = "__EMPTY__",
        .value = 0
    };
}

bool is_node_empty(Node n) {
    return strcmp(n.key, "__EMPTY__") == 0;
}

typedef struct {
    Node nodes[TABLE_SIZE];
} HashTable;

HashTable new_hashtable(void) {
    HashTable ht;

    for (int i = 0; i < TABLE_SIZE; i++)
        ht.nodes[i] = empty_node();

    return ht;
}

int get(HashTable ht, char key[]) {
    int index = hash(key);

    if (is_node_empty(ht.nodes[index]))
        return -1;

    return ht.nodes[index].value;
}

void set(HashTable* ht, char key[], int value) {
    int index = hash(key);
    ht->nodes[index] = new_node(key, value);
}

void del(HashTable* ht, char key[]) {
    int index = hash(key);
    ht->nodes[index] = empty_node();
}
