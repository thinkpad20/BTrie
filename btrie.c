//
//  btrie.c
//  BTrie
//
//  Created by Allen Nelson on 4/22/13.
//  Copyright (c) 2013 Allen Nelson. All rights reserved.
//

#include <stdio.h>
#include "btrie.h"

typedef struct BTrieNode Node;
typedef struct BTrie Trie;

int num_nodes = 0;

void *btrie_insertR(Node *node, const char *keys, int i, int end, int delta, void *data);
void *btrie_lookupR(Node *node, const char *keys, int i, int end, int delta);
Node *btrie_addNode(Node *node, unsigned char c, void *ptr);
Node *btrie_nextNode(Node *node, unsigned char c);

Node *btrie_makeNode(void *data) {
    Node *node = (Node *)calloc(1, sizeof(Node));
    if (node) {
        node->data = data;
    }
    return node;
}

void btrie_init(Trie *t) {
    if (t) {
        t->size = 0;
        t->root = btrie_makeNode(NULL);
    }
}

/*

say we have a person object Bob
Bob's info is located at address 0xAB12
then if p points to Bob, the value of p is 0xAB12


*/

void *btrie_insert(Trie *t, const char *keys, int size, void *data) {
    int start = (t->dir == BTRIE_BACKTOFRONT) ? size - 1 : 0,
        end = (t->dir == BTRIE_BACKTOFRONT) ? 0 : size - 1,
        delta = (t->dir == BTRIE_BACKTOFRONT) ? -1 : 1;
    // unsigned k = (unsigned)keys[start];
    // printf("k = %d, k %% 256 = %d\n", k, k % 256);
    // printf("received keys of size %d. First key is %x\n", size, k % 256);
    void *res = btrie_insertR(t->root, keys, start, end, delta, data);
    if (res)
        t->size++;
    return res;
}

void *btrie_insertR(Node *node, const char *keys, int i, int end, int delta, void *data) {
    Node *next;
    unsigned char c = keys[i];
    // printf("hashing key %x\n", ((unsigned)c) % 256);
    if (i == end)
        return btrie_addNode(node, c, data);
    else {
        next = btrie_nextNode(node, c);
        if (!next)
            next = btrie_addNode(node, c, NULL);
        return btrie_insertR(next, keys, i + delta, end, delta, data);
    }
}

void *btrie_lookup(Trie *t, const char *keys, int size) {
    int start = (t->dir == BTRIE_BACKTOFRONT) ? size - 1 : 0,
        end = (t->dir == BTRIE_BACKTOFRONT) ? 0 : size - 1,
        delta = (t->dir == BTRIE_BACKTOFRONT) ? -1 : 1;
    return btrie_lookupR(t->root, keys, start, end, delta);
}

void *btrie_lookupR(Node *node, const char *keys, int i, int end, int delta) {
    unsigned char c = keys[i];
    Node *next = btrie_nextNode(node, c);
    return (!next) ? NULL :
        (i == end) ? next->data :
            btrie_lookupR(next, keys, i + delta, end, delta);
}

Node *btrie_nextNode(Node *node, unsigned char c) {
    return node->links[(unsigned)c];
}

Node *btrie_addNode(Node *node, unsigned char c, void *ptr) {
    Node *newNode = btrie_makeNode(ptr);
    if (newNode) {
        node->links[(unsigned)c] = newNode;
        num_nodes++;
    }
    return newNode;
}
