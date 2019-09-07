#include <string.h>

#define MAXLEN 1000
#define MAXSTORE 5000

int getline(char *, int);

int readlines(char *lineptr, char *linestore, int maxlines) {
    int len, nlines;
    char line[MAXLEN];
    char *p = linestore;
    char *linestop = *p + MAXSTORE;

    nlines = 0;
    while ((len = getline(line, MAXLEN)) > 0){
        if (nlines >= maxlines || p + len > linestop)
            return -1;
        line[len-1] = '\0'; //delete \n;
        strcpy(p, line);
        lineptr[nlines++] = p; 
        p += len;
    }
    return nlines;
}