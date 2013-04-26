BTrie - A Versatile Byte-Keyed Trie in C
========================================

This is a versatile, powerful, sorted data structure. A normal trie stores values based on a string of characters. This trie does the same, but allows the user to specify the length of the string being inserted and which order to traverse the characters in. This means that any string of bytes, namely, any binary data, can be used as a key, and the order of traversal can be chosen in a way that maximizes the similarity between keys, minimizing memory usage. The BTrie implementation also imposes a lexicographic ordering as it is added to.

Using a BTrie
=============

The most simple use of this is as a normal string-keyed trie. Let's use one to build a tool that can count all instances of individual words in a text file.

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
	/* see btrie_personGenerator.c for more details */
	typedef struct BTrie BTrie;

	typedef struct person {
	    char name[20];
	    int age;
	} Person;

	[...]

	for (i=0; i<num_entries/2; ++i) {
	    Person *p = ppl[i];
	    btrie_insert(&pt, (char *)&p, sizeof(p), p))
	}
	for (i=0; i<(num_entries/2); ++i) {
	    btrie_lookup(&pt, (char *)&ppl[i], sizeof(ppl[i]));
	}

```

Insertion/Lookup speed
======================

BTrie is very fast and nearly as memory-efficient as a hash table. Running the `personGenerator` a few times shows a lookup and insertion time which is both rapid and independent of size.

```
./person 20 && ./person 200 && ./person 2000 && ./person 20000 && ./person 200000 && ./person 2000000 && ./person 20000000
Creating...
finished creating person objects. It took me 35 clicks (0.00003500 seconds, 0.00000175 each).
inserting...
finished inserting 20 people, 29 nodes. It took me 10 clicks (0.00001000 seconds, 0.00000050 each).
looking up...
Finished lookups. It took me 5 clicks (0.00000500 seconds, 0.00000025 each).
Trie has 20 objects in 29 nodes. Size of one node is 32 bytes. Total memory usage is 968 bytes.Creating...
finished creating person objects. It took me 68 clicks (0.00006800 seconds, 0.00000034 each).
inserting...
finished inserting 200 people, 232 nodes. It took me 63 clicks (0.00006300 seconds, 0.00000031 each).
looking up...
Finished lookups. It took me 50 clicks (0.00005000 seconds, 0.00000025 each).
Trie has 200 objects in 232 nodes. Size of one node is 32 bytes. Total memory usage is 7464 bytes.Creating...
finished creating person objects. It took me 477 clicks (0.00047700 seconds, 0.00000024 each).
inserting...
finished inserting 2000 people, 2258 nodes. It took me 1101 clicks (0.00110100 seconds, 0.00000055 each).
looking up...
Finished lookups. It took me 1044 clicks (0.00104400 seconds, 0.00000052 each).
Trie has 2000 objects in 2258 nodes. Size of one node is 32 bytes. Total memory usage is 72296 bytes.Creating...
finished creating person objects. It took me 3790 clicks (0.00379000 seconds, 0.00000019 each).
inserting...
finished inserting 20000 people, 22516 nodes. It took me 9084 clicks (0.00908400 seconds, 0.00000045 each).
looking up...
Finished lookups. It took me 10114 clicks (0.01011400 seconds, 0.00000051 each).
Trie has 20000 objects in 22516 nodes. Size of one node is 32 bytes. Total memory usage is 720552 bytes.Creating...
finished creating person objects. It took me 38007 clicks (0.03800700 seconds, 0.00000019 each).
inserting...
finished inserting 200000 people, 225110 nodes. It took me 114199 clicks (0.11419900 seconds, 0.00000057 each).
looking up...
Finished lookups. It took me 112969 clicks (0.11296900 seconds, 0.00000056 each).
Trie has 200000 objects in 225110 nodes. Size of one node is 32 bytes. Total memory usage is 7203560 bytes.Creating...
finished creating person objects. It took me 353269 clicks (0.35326900 seconds, 0.00000018 each).
inserting...
finished inserting 2000000 people, 2251034 nodes. It took me 1509067 clicks (1.50906700 seconds, 0.00000075 each).
looking up...
Finished lookups. It took me 1388560 clicks (1.38856000 seconds, 0.00000069 each).
Trie has 2000000 objects in 2251034 nodes. Size of one node is 32 bytes. Total memory usage is 72033128 bytes.Creating...
finished creating person objects. It took me 3571571 clicks (3.57157100 seconds, 0.00000018 each).
inserting...
finished inserting 20000000 people, 22510282 nodes. It took me 16687109 clicks (16.68710900 seconds, 0.00000083 each).
looking up...
Finished lookups. It took me 11332055 clicks (11.33205500 seconds, 0.00000057 each).
Trie has 20000000 objects in 22510282 nodes. Size of one node is 32 bytes. Total memory usage is 720329064 bytes.
```