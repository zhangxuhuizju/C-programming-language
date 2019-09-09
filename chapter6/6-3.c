#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#define MAXWORD 100

struct linklist {
    int linenum;
    struct linklist *next;
};

struct treenode {
    char *word;
    struct linklist *lines;
    struct treenode *left;
    struct treenode *right;
};

struct treenode *addtree(struct treenode *, char *, int);
void treeprint(struct treenode *);
int getword(char *, int);
int noiseword(char *);
void addlinklist(struct treenode *, int);

int main(int argc, char const *argv[])
{
    struct treenode *root;
    char word[MAXWORD];
    int linenum = 1;

    root = NULL;

    while (getword(word, MAXWORD) != EOF)
    {
        if (isalpha(word[0]) && noiseword(word) == -1)
            root = addtree(root, word, linenum);
        if (word[0] == '\n')
            linenum++;
    }
    treeprint(root);
    return 0;
}

struct treenode *addtree(struct treenode *p, char *s, int linenum) {
    int cond;

    if (p == NULL) {
        p = (struct treenode *)(malloc(sizeof(struct treenode)));
        p->word = (char *)(malloc(sizeof(s)+1));
        strcpy(p->word, s);
        p->left = p->right = NULL;
        p->lines = (struct linklist*)malloc(sizeof(struct linklist));
        p->lines->linenum = linenum;
        p->lines->next = NULL;
    } else if ((cond = strcmp(p->word, s)) == 0)
        addlinklist(p, linenum);
    else if (cond < 0)
        p->left = addtree(p->left, s, linenum);
    else
        p->right = addtree(p->right, s, linenum);
    
    return p;
}

void addlinklist(struct treenode *p, int linenum) {
    struct linklist *temp = p->lines;
    while (temp->next != NULL && temp->linenum != linenum){
        temp = temp->next;
    }
    if (temp->linenum != linenum) {
        temp->next = (struct linklist*)malloc(sizeof(struct linklist));
        temp->next->linenum = linenum;
        temp->next->next = NULL;
    }
}

void treeprint(struct treenode *p) {
    struct linklist *temp;
    if (p) {
        treeprint(p->left);
        printf("%10s: ", p->word);
        for (temp = p->lines; temp != NULL; temp = temp->next)
            printf("%4d ", temp->linenum);
        printf("\n");
        treeprint(p->right);
    }
}

int noiseword(char *s) {
    static char *nw = {
        "a",
        "an",
        "and",
        "are",
        "in",
        "is",
        "of",
        "or",
        "that",
        "the",
        "this",
        "to"
    };

    int cond, mid;
    int low = 0, high = sizof(nw) / sizeof(char*) - 1;

    while (low <= high){
        mid = (low + high) / 2;
        if ((cond = strcmp(s, nw[mid])) < 0)
            high = mid - 1;
        else if (cond > 0)
            low = mid + 1;
        else return mid;
    }
    return -1;
}