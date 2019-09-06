#include <stdio.h>

#define INSIDE 1
#define OUT 0

int main(int argc, char const *argv[])
{
    int c, state = OUT;
    while ((c = getchar()) != EOF)
    {
        if (c == ' ' || c == '\n' || c == '\t') {
            if (state == INSIDE) {
                putchar('\n');
                state = OUT;
            }
        } else if (state == OUT)
        {
            state = INSIDE;
            putchar(c);
        } else 
            putchar(c);
        
    }
    return 0;
}
