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
void btrie_printR(Node *node, void (*print) (void *));

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

void *btrie_insert(Trie *t, const char *keys, int size, void *data) {
    int start = (t->dir == BTRIE_BACKTOFRONT) ? size - 1 : 0,
        end = (t->dir == BTRIE_BACKTOFRONT) ? 0 : size - 1,
        delta = (t->dir == BTRIE_BACKTOFRONT) ? -1 : 1;
    void *res;
    if (!size) return NULL;
    res = btrie_insertR(t->root, keys, start, end, delta, data);
    if (res)
        t->size++;
    return res;
}

void *btrie_insertR(Node *node, const char *keys, int i, int end, int delta, void *data) {
    Node *next;
    unsigned char c = keys[i];
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
    if (!size) return NULL;
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
    } else {
        fprintf(stderr, "Error in memory allocation, exiting.\n");
        exit(1);
    }
    return newNode;
}

void btrie_printR(Node *node, void (*print) (void *)) {
    int i;
    if (node->data) 
        print(node->data);
    for (i=0; i<MAX_DICT; ++i) {
        if (node->links[i])
            btrie_printR(node->links[i], print);
    }
}

void btrie_print(Trie *t) {
    if (!t->prnt) return;
    btrie_printR(t->root, t->prnt);
}