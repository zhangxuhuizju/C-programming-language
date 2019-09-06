#include <stdio.h>

int brace, brack, paren;

void in_quote(int c);
void in_commit(int c);
void search(int c);

int main(int argc, char const *argv[])
{
    int c;
    while ((c = getchar()) != EOF) {
        if (c == '/') {
            c = getchar();
            if (c == '*' || c == '/')
                in_commit(c);
            else search(c);
        } else if (c == '\'' || c == '"'){
            in_quote(c);
        } else search(c);
        if (brace < 0)
            printf ("error brace\n");
        else if (brack < 0)
            printf ("error brack\n");
        else if (paren < 0)
            printf ("error paren\n");
        if (brace < 0 || brack < 0 || paren < 0)
            return 0;
    }
    if (brace > 0)
        printf ("error brace\n");
    if (brack > 0)
        printf ("error brack\n");
    if (paren > 0)
        printf ("error paren\n");
    return 0;
}

void search(c){
    if (c == '{')
        brace++;
    else if (c == '}')
        brace--;
    else if (c == '[')
        brack++;
    else if (c == ']')
        brack--;
    else if (c == '(')
        paren++;
    else if (c == ')')
        paren--;
}

void in_commit(int c) {
    if (c == '/') {
        do {
            c = getchar();
        } while(c != '\n');
    } else {
        c = getchar();
        int d = getchar();
        while (c != "*" || d != "/")
        {
            c = d;
            d = getchar();
        }        
    }
}
