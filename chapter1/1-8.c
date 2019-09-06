#include <stdio.h>

int main(int argc, char const *argv[])
{
    int c, blank = 0, tabs = 0, lines = 0;
    while ((c = getchar()) != EOF) 
    {
        switch (c)
        {
        case ' ':
            blank++;
            break;
        case '\n':
            lines++;
            break;
        case '\t':
            tabs++;
            break;
        default:
            break;
        }
    }
    printf("%d %d %d\n", blank, tabs, lines);
    return 0;
}
