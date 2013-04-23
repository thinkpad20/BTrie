BTrie - A Versatile Byte-Keyed Trie in C
========================================

This is a versatile and fast data structure. A normal trie stores values based on a string of characters. This trie does the same, but allows the user to specify the length of the string being inserted and which order to traverse the characters in. This means that any string of bytes, namely, any binary data, can be used as a key, and the order of traversal can be chosen in a way that maximizes the similarity between keys.

The most simple use of this is as a normal string-keyed trie:

```c

/* see btrie_wordCount.c for more details */

struct BTrie t;

struct word {
	char text[MAX_WORD];
	int num;
};

void update_count(char *buf, int len) {
	struct word *word = (struct word *)btrie_lookup(&t, buf, len);
	if (!len) return;
	if (word) {
		word->num++;
	} else {
		word = (struct word *)calloc(1, sizeof(struct word));
		strncpy(word->text, buf, MAX_WORD);
		word->num = 1;
		btrie_insert(&t, word->text, len, word);
	}
}

```

One use that arises from this is hashing based on the pointer of an object. If many persistent heap-allocated objects are in use, especially when there may not be a guarantee of a unique key attribute, a data structure which can perform insertions and lookups based on pointers is very useful.

```c
typedef struct BTrie BTrie;

typedef struct person {
    char name[20];
    int age;
} Person;

for (i=0; i<num_entries/2; ++i) {
    Person *p = ppl[i];
    if (!btrie_insert(&pt, (char *)&p, sizeof(p), p)) {
        printf("error on insertion\n");
        break;
    }
}
for (i=0; i<(num_entries/2); ++i) {
    btrie_lookup(&pt, (char *)&ppl[i], sizeof(ppl[i]));
}

```