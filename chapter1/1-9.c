#include <stdio.h>

int main(int argc, char const *argv[])
{
    int c, lastChar;
    lastChar = 'a';
    while ((c = getchar()) != EOF)
    {
        if (c != ' ' || lastChar != ' ')
            putchar(c);
        lastChar = c;
    }
    
    return 0;
}
