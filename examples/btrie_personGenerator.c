#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../btrie.h"

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
    }
    printf("finished creating person objects\n");

    for (i=0; i<num_entries/2; ++i) {
        Person *p = ppl[i];
        printf("inserting person %p\n", p);
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
}