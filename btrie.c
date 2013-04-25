//
//  btrie.c
//  BTrie
//
//  Created by Allen Nelson on 4/22/13.
//  Copyright (c) 2013 Allen Nelson. All rights reserved.
//

#include <stdio.h>
#include <string.h>
#include "btrie.h"

typedef struct BTrieNode Node;
typedef struct BTrie Trie;

int num_nodes = 0;

void *btrie_insertR(Node *node, const char *keys, int i, int end, int delta, const void *data);
void *btrie_lookupR(Node *node, const char *keys, int i, int end, int delta);
Node *btrie_addNode(Node *node, char c, const void *ptr);
Node *btrie_nextNode(Node *node, char c);
size_t btrie_deleteR(Node *node);
void btrie_mapR(Node *node, void (*func) (void *));

Node *btrie_makeNode(char c, const void *data) {
    Node *node = (Node *)calloc(1, sizeof(Node));
    if (node) {
        node->data = (void *)data;
        node->c = c;
    }
    return node;
}

void btrie_init(Trie *t) {
    if (t) {
        t->size = 0;
        t->root = btrie_makeNode(0, NULL);
    }
}

void *btrie_insert(Trie *t, const char *keys, int size, const void *data) {
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

void *btrie_insertR(Node *node, const char *keys, int i, int end, int delta, const void *data) {
    Node *next;
    char c = keys[i];
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
    
    void *res = btrie_lookupR(t->root, keys, start, end, delta);
    
    return res;
}

void *btrie_lookupR(Node *node, const char *keys, int i, int end, int delta) {
    char c = keys[i];
    Node *next = btrie_nextNode(node, c);
    return (!next) ? NULL :
    (i == end) ? next->data :
    btrie_lookupR(next, keys, i + delta, end, delta);
}

Node *btrie_nextNode(Node *node, char c) {
    Node *cur = node->down;
    while (cur) {
        if (cur->c == c)
            return cur;
        cur = cur->right;
    }
    return NULL;
}

Node *btrie_addNode(Node *node, char c, const void *ptr) {
    Node *newNode, *cur = node->down, *prev = NULL;
    while (cur) {
        prev = cur;
        if (cur->c == c) {
            cur->data = (void *)ptr;
            return cur;
        }
        cur = cur->right;
    }
    
    /* no node with current character exists */
    newNode = btrie_makeNode(c, ptr);
    if (newNode) {
        if (!prev)
            node->down = newNode;
        else
            prev->right = newNode;
        num_nodes++;
    } else {
        fprintf(stderr, "Error in memory allocation, exiting.\n");
        exit(1);
    }
    return newNode;
}

void btrie_print(Trie *t) {
    if (!t->prnt) return;
    btrie_map(t, t->prnt);
}

void btrie_printProfile(Trie *t) {
    printf("Trie has %lu objects in %d nodes. "
           "Size of one node is %lu bytes. "
           "Total memory usage is %lu bytes.",
           t->size, num_nodes, sizeof(Node), num_nodes * sizeof(Node) + sizeof(Trie));
}

size_t btrie_deleteR(Node *node) {
    size_t num_deleted = 1;
    Node *cur = node->down;
    while (cur) {
        num_deleted += btrie_deleteR(cur);
        cur = cur->right;
    }
    free(node);
    return num_deleted;
}

void btrie_delete(Trie *t) {
    size_t num_deleted = btrie_deleteR(t->root);
    t->size -= num_deleted;
}

void btrie_mapR(Node *node, void (*func) (void *)) {
    Node *cur = node->down;
    if (node->data)
        func(node->data);
    while (cur) {
        btrie_mapR(cur, func);
        cur = cur->right;
    }
}

void btrie_map(struct BTrie *t, void (*func) (void *)) {
    btrie_mapR(t->root, func);
}

void *btrie_applyR(Node *node, void *(*func) (void*)) {
    Node *cur = node->down;
    if (node->data)
        func(node->data);
    while (cur) {
        btrie_applyR(cur, func);
        cur = cur->right;
    }
    return NULL;
}

void *btrie_apply(Trie *t, void *(*func) (void *)) {
    return btrie_applyR(t->root, func);
}