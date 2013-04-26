#include "stdio.h"
#include "stdlib.h"
#include "../btrie.h"

#define NUM_INTS 50

typedef struct BTrie Trie;

void int_print(void *i) { printf("%d\n", *(int *)i);}

int main() {
	int *nums = (int *)malloc(NUM_INTS * sizeof(int)),
		i;
	Trie t;
	btrie_init(&t);
	t.prnt = int_print;
	for (i=0; i<NUM_INTS; ++i) {
		nums[i] = rand();
		btrie_insert(&t, (const char *)&nums[i], sizeof(int), nums[i]);
	}
	btrie_print(&t);
	return 0;
}