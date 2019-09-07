#include <stdio.h>
#include <math.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#define MAXOP 100 //操作数or运算符的最大长度
#define NUMBER '0'
#define MAXVAL 100 //栈的最大深度

int getop(char []);
void push(double);
double pop(void);

int main(int argc, char const *argv[])
{
    int type;
    double op2;
    char s[MAXOP];

    while ((type = getop(s)) != EOF){
        switch (type)
        {
        case NUMBER:
            push(atof(s));
            break;
        case '+':
            push(pop()+pop());
            break;
        case '*':
            push(pop()*pop());
            break;
        case '-':
            op2 = pop();
            push(pop()-op2);
            break;
        case '/':
            op2 = pop();
            if (op2 == 0.0) {
                printf("ERROR!");
                return -1;
            }
            push(pop()/op2);
            break;
        case '%':
            op2 = pop();
            if (op2 != 0.0) push(fmod(pop(), op2));
            else {
                printf("ERROR!");
                return -1;
            }
            break;
        case '\n':
            printf("\t %.8g\n", pop());
            break;
        default:
            printf("ERROR!");
            return -1;
            break;
        }
    }
    return 0;
}

int sp = 0;
double val[MAXVAL];

void push(double f) {
    if (sp < MAXVAL)
        val[sp++] = f;
    else printf("ERROR!");
}

double pop(void) {
    if(sp > 0)
        return val[--sp];
    else {
        printf("ERROR!");
        return 0.0;
    }
}

int getch(void);
void ungetch(int);

int getop(char s[]) {
    int i, c;
    while ((s[0] = c = getch()) == ' ' || c == '\t');
    s[1] = '\0';

    i = 0;
    if (!isdigit(c) && c != '.' && c != '-')
        return c; //not a number
    if (c == '-') {
        if (isdigit(c = getch()) || c == '.')
            s[++i] = c;
        else {
            if (c != EOF)
                ungetch(c);
            return '-';
        }
    }
    if (isdigit(c))
        while(isdigit(s[++i] = c = getch()));
    if (c == '.')
        while(isdigit(s[++i] = c = getch()));
    s[i] = '\0';
    if (c != EOF)
        ungetch(c);
    return NUMBER;    
}

#define BUFSIZE 100

char buf[BUFSIZE];
int bufp = 0;

int getch(void) {
    return (bufp > 0) ? buf[--bufp] : getchar();
}

void ungetch(int c) {
    if (bufp >= BUFSIZE)
        printf("ERROR!");
    else buf[bufp++] = c;
}