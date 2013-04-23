//
//  btrie.h
//  BTrie
//
//  Created by Allen Nelson on 4/22/13.
//  Copyright (c) 2013 Allen Nelson. All rights reserved.
//

#ifndef BTrie_btrie_h
#define BTrie_btrie_h
#define BTRIE_BACKTOFRONT 0
#define BTRIE_FRONTTOBACK 1

#include <stdlib.h>
#include <stdbool.h>

struct BTrieNode {
    void *data;
    struct BTrieNode *links[256];
};

struct BTrie {
    size_t size;
    int dir; /* back-to-front or front-to-back */
    struct BTrieNode *root;
};

void btrie_init(struct BTrie *t);
void *btrie_insert(struct BTrie *t, const char *keys, int size, void *data);
void *btrie_lookup(struct BTrie *t, const char *keys, int size);

#endif
