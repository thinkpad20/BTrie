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
int isS = 0;

void *btrie_insertR(Node *node, const char *keys, int i, int end, int delta, void *data);
void *btrie_lookupR(Node *node, const char *keys, int i, int end, int delta);
Node *btrie_addNode(Node *node, char c, void *ptr);
Node *btrie_nextNode(Node *node, char c);
void btrie_printR(Node *node, void (*print) (void *));

Node *btrie_makeNode(char c, void *data) {
    Node *node = (Node *)calloc(1, sizeof(Node));
    if (node) {
        node->data = data;
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

void *btrie_insert(Trie *t, const char *keys, int size, void *data) {
    int start = (t->dir == BTRIE_BACKTOFRONT) ? size - 1 : 0,
        end = (t->dir == BTRIE_BACKTOFRONT) ? 0 : size - 1,
        delta = (t->dir == BTRIE_BACKTOFRONT) ? -1 : 1;
    void *res;
    if (!size) return NULL;
    if (!strcmp(keys, "s")) isS = 1;
    res = btrie_insertR(t->root, keys, start, end, delta, data);
    if (res)
        t->size++;
    isS = 0;
    return res;
}

void *btrie_insertR(Node *node, const char *keys, int i, int end, int delta, void *data) {
    Node *next;
    char c = keys[i];
    if (isS) printf("hey!hey!hey!hey!hey!hey!hey!hey!hey!hey!hey!hey!hey!hey!hey!hey!hey!hey!hey!\n");
    if (i == end)
        return btrie_addNode(node, c, data);
    else {
        // printf("hey, key = %x, node = %p\n", (int)c % 256, node); fflush(stdout);
        next = btrie_nextNode(node, c);
        // printf("wazzup\n"); fflush(stdout);
        if (!next)
            next = btrie_addNode(node, c, NULL);
        // printf("yoyoyo"); fflush(stdout);
        return btrie_insertR(next, keys, i + delta, end, delta, data);
    }
}

void *btrie_lookup(Trie *t, const char *keys, int size) {
    int start = (t->dir == BTRIE_BACKTOFRONT) ? size - 1 : 0,
        end = (t->dir == BTRIE_BACKTOFRONT) ? 0 : size - 1,
        delta = (t->dir == BTRIE_BACKTOFRONT) ? -1 : 1;
    if (!size) return NULL;
    if (!strcmp(keys, "s")) isS = 1;
    void *res = btrie_lookupR(t->root, keys, start, end, delta);
    isS = 0;
    return res;
}

void *btrie_lookupR(Node *node, const char *keys, int i, int end, int delta) {
    char c = keys[i];
    Node *next = btrie_nextNode(node, c);
    if (isS) printf("hey!hey!hey!hey!hey!hey!hey!hey!hey!hey!hey!hey!hey!hey!hey!hey!hey!hey!hey!\n");
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

Node *btrie_addNode(Node *node, char c, void *ptr) {
    Node *newNode = btrie_makeNode(c, ptr), *cur = node->down, *prev = NULL;
    if (newNode) {
        while (cur) { 
            prev = cur; 
            cur = cur->right;
        }
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

void btrie_printR(Node *node, void (*print) (void *)) {
    Node *cur = node->down;
    if (node->data) 
        print(node->data);
    while (cur) {
        btrie_printR(cur, print);
        cur = cur->right;
    }
}

void btrie_print(Trie *t) {
    if (!t->prnt) return;
    btrie_printR(t->root, t->prnt);
}

void btrie_printProfile(Trie *t) {
    printf("Trie has %lu objects in %d nodes. "
           "Size of one node is %lu bytes. "
           "Total memory usage is %lu bytes.",
            t->size, num_nodes, sizeof(Node), num_nodes * sizeof(Node) + sizeof(Trie));
}