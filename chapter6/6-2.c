#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

struct treenode
{
    char *word;  /*tree node words */
    int match;
    struct treenode *left;
    struct treenode *right;
};

#define MAXWORD 100
#define YES 1
#define NO 0

struct treenode *addtree(struct treenode *, char *, int, int *);
void treeprint(struct treenode *);
int getword(char *, int);

int main(int argc, char const *argv[])
{
    struct treenode *root;
    char word[MAXWORD];
    int found = NO;
    int num;

    num = (--argc && (*++argv)[0] == '-') ? atoi(argv[0] + 1) : 6;

    root = NULL;
    while (getword(word, MAXWORD) != EOF) {
        if (isalpha(word[0]) && strlen(word) >= num)
            root = addtree(root, word, num, &found);
        found = NO;
    }
    treeprint(root);
    return 0;
}

struct treenode *addtree(struct treenode * p, char *s, int num, int *found) {
    int cond;

    if (p == NULL) {
        p = (struct treenode*)malloc(sizeof(struct treenode));
        p->word = (char*)malloc(sizeof(strlen(s))+1);
        strcpy(p->word, s);
        p->match = *found;
        p->left = p->right = NULL;
    } else if ((cond = compare(s, p, num, found)) < 0){
        p->left = addtree(p->left, s, num, found);
    } else
        p->right = addtree(p->right, s, num, found);
    return p;
}

int compare(char *s, struct treenode *p, int num, int *found) {
    int cond;
    char *t = p->word;

    if (strcmp(s, t) == 0)
        return 0;
    cond = strncmp(s, t, num);
    if (cond == 0) {
        *found = YES;
        p->match = YES;
    }
    return strcmp(s, t);
}

void treeprint(struct treenode *p) {
    if (p) {
        treeprint(p->left);
        if (p->match)
            printf("%s\n", p->word);
        treeprint(p->right);
    }
}