#include <stdio.h>
#include <ctype.h>

/**
 * get next word or character from input
 */
int getword(char *word, int lim) {
    int c, d, comment(void), getch(void);
    void ungetch(int);
    char *w = word;

    while(isspace(c = getch()));

    if (c != EOF)
        *w++ = c;
    if (isalpha(c) || c == '_' || c == '#') {
        for (; --lim > 0; w++) {
            if (!isalnum(*w = getch())) {
                ungetch(w);
                break;
            }
        }
    } else if (c == '\'' || c == '\"') {
        for (; --lim > 0; w++) {
            if ((*w = getch()) == '\\')
                *++w = getch(); //遇到转义字符
            else if (*w == c){
                w++;
                break;
            }else if (*w == EOF)
                break;
        }
    } else if (c == '/'){
        if ((d = getch()) == '*')
            c = comment();
        else ungetch(d);
    }
    *w = '\0';
    return w[0];
}

/**
 * skip the commet and return the last character in the commet
 */
int commet(void) {
    int c;
    while ((c = getch()) != EOF)
    {
        if (c == '*')
            if ((c = getch()) == '/')
                break;
            else 
                ungetch(c);
    }
    return c;
}