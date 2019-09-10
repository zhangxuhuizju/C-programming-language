#include<stdio.h>
unsigned hash(char *);

struct nlist {
    struct nlist *next;
    char *name;
    char *defn;
};

static struct nlist *hashtab[1000];

void undef(char *s) {
    int key;
    struct nlist *prev, *ptr;

    prev = NULL;
    key = hash(s);
    for (ptr = hashtab[key]; ptr != NULL; ptr = ptr->next) {
        if (strcmp(s, ptr->name) == 0)
            break;
        prev = ptr;
    }
    if (ptr != NULL) {
        if (prev == NULL)
            hashtab[key] = ptr->next;
        else 
            prev->next = ptr->next;
        free((void *)ptr->name);
        free((void *)ptr->defn);
        free((void *)ptr);
    }
}