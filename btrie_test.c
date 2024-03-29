#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "btrie.h"

const char *test[] = {
    "say",
    "so",
    "hell",
    "hello",
    "help",
    "zizzer"
};

const int numstrs = sizeof(test)/sizeof(char *);

struct BTrie t;

int main() {
    int i;
    btrie_init(&t);
    for (i=0; i<numstrs; ++i) {
        printf("Inserting '%s'\n", test[i]);
        btrie_insert(&t, test[i], strlen(test[i]), test[i]);
    }

    for (i=0; i<numstrs; ++i) {
        printf("Looking up '%s'\n", test[i]);
        printf("%s\n", (char *)btrie_lookup(&t, test[i], strlen(test[i])));
    }
    printf("looking up plop: %s\n", (char *)btrie_lookup(&t, "plop", 4));
    return 0;
}

/*
typedef struct BTrie BTrie;

typedef struct person {
    char name[20];
    int age;
} Person;

void free_person(void *p) { free(p); }
void print_person(void *pvp) { 
    Person *p = (Person *)pvp; 
    printf("%s: %d years old\n", p->name, p->age); 
}
Person *make_person(int bang) {
    Person *p = (Person *)malloc(sizeof(Person));
    int i;
    p->age = rand() % 100;
    p->name[0] = (rand() % 26) + 'A';
    for (i=1; i<10; ++i) {
        p->name[i] = (rand() % 26) + 'a';
    }
    p->name[10] = ' ';
    p->name[11] = (rand() % 26) + 'A';
    for (i=12; i<18; ++i) {
        p->name[i] = (rand() % 26) + 'a';
    }
    p->name[18] = (bang)? '!' : '\0';
    p->name[19] = '\0';
    return p;
}

extern int num_nodes;

int main(int argc, char **argv) {
    int i, j=0;
    int num_entries = (argc > 1) ? atoi(argv[1]) : 200;
    BTrie pt;
    btrie_init(&pt);
    pt.dir = (argc > 2) ? atoi(argv[2]) : BTRIE_BACKTOFRONT;
    Person *ppl[num_entries/2];
    for (i=0; i<num_entries; ++i) {
        Person *p = make_person(i & 1);
        if (i & 1) ppl[j++] = p;
        // printf("inserting person %p\n", p);
        if (!btrie_insert(&pt, (char *)&p, sizeof(p), p)) {
            printf("error on insertion\n");
            break;
        }
    }
    printf("finished inserting %d people, %d nodes\n", num_entries, num_nodes);
    for (i=0; i<(num_entries/2); ++i) {
        btrie_lookup(&pt, (char *)&ppl[i], sizeof(ppl[i]));
    }
    printf("Finished lookups\n");
    return 0;
}*/





/*//
//  btrie_test.c
//  BTrie
//
//  Created by Allen Nelson on 4/22/13.
//  Copyright (c) 2013 Allen Nelson. All rights reserved.
//

#include <stdio.h>
#include <string.h>
#include "btrie.h"

typedef struct BTrie BTrie;

int main(int argc, const char * argv[])
{
    const char *strings[] = {
        "hello",
        "hi",
        "how are you?",
        "I'm fine thanks" };
    
    // int ints[] = {1, 2, 3, 4, 5, 234, 456, 23, 678, 98457,
    //               230498, 20394, 39, 48, 10};
    BTrie pt;
    btrie_init(&pt);
    for (int i=0; i<4; ++i) {
        printf("inserting %p (%s)\n", strings[i], strings[i]);
        btrie_insert(&pt, strings[i], strlen(strings[i]), (void *)strings[i]);
    }
    
    // for (int i=0; i<20; ++i) {
    //     printf("inserting %p (%d)\n", ints + i, ints[i]);
    //     btrie_insert(&pt, (void *)(ints + i));
    // }
    
    for (int i=0; i<4; ++i) {
        char *temp = (char *)btrie_lookup(&pt, strings[i], strlen(strings[i]));
        printf("lookup result: %p (%s)\n", temp, temp);
    }
    
    // for (int i=0; i<20; ++i) {
    //     printf("lookup result: %p (%d)\n", btrie_lookup(&pt, (void *)(ints + i)),
    //            *((int *)btrie_lookup(&pt, (void *)(ints + i))));
    // }
    return 0;
}

*/