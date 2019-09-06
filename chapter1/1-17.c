#include <stdio.h>

#define MAXLEN 1000
#define LIMIT 80

int getlines(char s[], int limit); 

int main(int argc, char const *argv[])
{
    int len;
    char line[MAXLEN];

    while ((len = getlines(line, MAXLEN)) > 0)
    {
        if (len > LIMIT)
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