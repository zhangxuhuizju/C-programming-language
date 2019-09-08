#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAXLINES 5000
char *lineptr[MAXLINES];

int readlines(char *lineptr[], int nlines);
void writelines(char *lineptr[], int nlines);

void quicksort(void *lineptr[], int left, int right, int (*comp)(void *, void *));
int numcmp(char *, char *);

int main(int argc, char const *argv[])
{
    int nlines;
    int numsort = 0;

    if (argc > 1 && strcmp(argv[1], "-n") == 0)
        numsort = 1;
    if ((nlines = readlines(lineptr, MAXLINES)) > 0) {
        quicksort(lineptr, 0, nlines-1, numsort ? numcmp : strcmp);
        writelines(lineptr, nlines);
        return 0;
    } else {
        printf("too big to sort!\n");
        return 1;
    }
}

void quicksort(void *v[], int left, int right, int (*comp)(void *, void *)) {
    int i, last;
    void swap (void *v[], int, int);

    if (left >= right)
        return;
    swap(v, left, (left + right) / 2);
    last = left;
    for (i = left+1; i <= right; ++i)
        if((*comp)(v[i], v[left]) < 0)
            swap(v, ++last, i);
    swap(v, last, left);
    quicksort(v, left, last-1, comp);
    quicksort(v, last+1, right, comp);
}

void swap(void *v[], int i, int j) {
    void *temp;
    temp = v[i];
    v[i] = v[j];
    v[j] = temp;
}

int numcmp(char *s1, char *s2) {
    double v1 = atof(s1), v2 = atof(s2);
    if (v1 < v2)
        return -1;
    else if (v1 > v2)
        return 1;
    else return 0;
}

void writelines(char *lineptr[], int nlines) {
    int i;
    for (i = 0; i < nlines; ++i)
        printf ("%s\n", lineptr[i]);
}
