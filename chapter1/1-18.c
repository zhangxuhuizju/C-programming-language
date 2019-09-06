#include <stdio.h>
#define MAXLEN 1000   //maximum input line size

int getlines(char s[], int limit); 
int removes(char s[]);

int main(int argc, char const *argv[])
{
    int len;
    char line[MAXLEN];

    while ((len = getlines(line, MAXLEN)) > 0)
    {
        if (removes(line) > 0)
            printf("%s", line);
    }
    
    return 0;
}

int getlines(char s[], int limit) {
    int c, i;

    for (i = 0; i < limit - 1 && (c = getchar()) != EOF && c != '\n'; ++i)
        s[i] = c;
    if (c == '\n') {
        s[i] = '\n';
        ++i;
    }
    s[i] = '\0';
    return i;
}

int removes (char s[]) {
    int i = 0;
    while (s[i] != '\n')
    {
        ++i;
    }
    --i;
    while (i >= 0 && (s[i] == ' ' || s[i] == '\t'))
    {
        --i;
    }
    if (i >= 0) {
        s[++i] = '\n';
        s[++i] = '\0';
    }
    return i;
}