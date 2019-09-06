#include <stdio.h>

void delete (int c) {
    int d;
    if (c == '/') {
        d = getchar();
        if (d == '/') {
            do {
                d = getchar();
            } while (d != '\n');
            
        } else if (d == '*') {
            do {
                c = d;
                d = getchar();
            } while (c != '*' || d != '/'); 
        } else {
            putchar(c);
            putchar(d);
        }
    } else if (c == '\'' || c == '"') {
        putchar(c);
        do {
            d = getchar();
            putchar(d);
            if (d == '\\')
                putchar(getchar());
        } while (d != c);
    } else
        putchar(c);
}

int main(int argc, char const *argv[])
{
    int c;
    while ((c = getchar()) != EOF)
        delete(c);
    return 0;
}
