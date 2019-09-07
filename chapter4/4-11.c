#include <stdio.h>
#include <ctype.h>

#define NUMBER '0'

int getop(char s[]) {
    static int last = -1;
    int i, c;
    if (last != -1) {
        s[0] = c = last;
        if (s[0] == ' ' || s[0] == '\t')
            while ((s[0] = c = getchar()) == ' ' || c == '\t');
        last = -1;
    }
    else while ((s[0] = c = getchar()) == ' ' || c == '\t');
    s[1] = '\0';

    i = 0;
    if (!isdigit(c) && c != '.' && c != '-')
        return c; //not a number
    if (c == '-') {
        if (isdigit(c = getchar()) || c == '.')
            s[++i] = c;
        else {
            if (c != EOF) {
                last = c;
            }
            return '-';
        }
    }
    if (isdigit(c))
        while(isdigit(s[++i] = c = getchar()));
    if (c == '.')
        while(isdigit(s[++i] = c = getchar()));
    s[i] = '\0';
    if (c != EOF) {
        last = c;
    }
    return NUMBER;    
}