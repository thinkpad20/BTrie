#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "../btrie_mod.h"

struct BTrie t;

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

void create_people(Person **arr, int num) {
    int i;
    clock_t cl;
    cl = clock();
    printf ("Creating...\n");
    for (i=0; i<num; ++i) {
        Person *p = make_person(i & 1);
        arr[i] = p;
    }
    cl = clock() - cl;
    printf("finished creating person objects. ");
    printf ("It took me %d clicks (%0.8LF seconds, %0.8LF each).\n",
                (int)cl,
                ((long double)cl)/CLOCKS_PER_SEC,
                ((long double)cl)/CLOCKS_PER_SEC/num);
}

void insert_people(Person **ppl, int num) {
    int i;
    clock_t cl = clock();
    printf("inserting...\n");
    for (i=0; i<num; ++i) {
        Person *p = ppl[i];
        // printf("inserting person %p\n", p);
        if (!btrie_insert(&t, (char *)&p, sizeof(p), p)) {
            printf("error on insertion\n");
            break;
        }
    }
    cl = clock()-cl;
    printf("finished inserting %d people, %d nodes. ", (int)t.size, num_nodes);
    printf ("It took me %d clicks (%0.8LF seconds, %0.8LF each).\n",
                (int)cl,
                ((long double)cl)/CLOCKS_PER_SEC,
                ((long double)cl)/CLOCKS_PER_SEC/num);
}

void lookup_people(Person **ppl, int num) {
    int i;
    clock_t cl = clock();
    printf("looking up...\n");
    for (i=0; i<(num); ++i) {
        btrie_lookup(&t, (char *)&ppl[i], sizeof(ppl[i]));
    }
    cl = clock() - cl;
    printf("Finished lookups. ");
    printf ("It took me %d clicks (%0.8LF seconds, %0.8LF each).\n",
                (int)cl,
                ((long double)cl)/CLOCKS_PER_SEC,
                ((long double)cl)/CLOCKS_PER_SEC/num);
}

int main(int argc, char **argv) {
    int num_entries = (argc > 1) ? atoi(argv[1]) : 200;
    btrie_init(&t);
    t.dir = (argc > 2) ? atoi(argv[2]) : BTRIE_BACKTOFRONT;
    Person **ppl = (Person **)malloc(num_entries * sizeof(Person*)); 

    create_people(ppl, num_entries);
    insert_people(ppl, num_entries);
    lookup_people(ppl, num_entries);
   
    btrie_printProfile(&t);
    return 0;
}