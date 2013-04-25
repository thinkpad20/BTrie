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
	char c;
    void *data;
    struct BTrieNode *down, *right;
};

struct BTrie {
    size_t size;
    int dir; /* back-to-front or front-to-back */
    void (*prnt) (void *); 	/* print function */
    void (*del) (void *); 	/* delete function */
    struct BTrieNode *root;
};

struct ArbitraryReturn {
	size_t size;
	void *content;
};

void btrie_init(struct BTrie *t);
void *btrie_insert(struct BTrie *t, const char *keys, int size, const void *data);
void *btrie_lookup(struct BTrie *t, const char *keys, int size);
void btrie_print(struct BTrie *t);
void btrie_printProfile(struct BTrie *t);
void btrie_delete(struct BTrie *t);
void btrie_map(struct BTrie *t, void (*func) (void *));
void *btrie_apply(struct BTrie *t, void *(*func) (void *));

#endif
