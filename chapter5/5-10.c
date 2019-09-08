#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

#define MAXSIZE 100
#define NUMBER '0'
double stack[MAXSIZE];
int sp = 0;

char getop(char *s) {
    if (strcmp(s, "+") == 0)
        return '+';
    if (strcmp(s, "-") == 0)
        return '-';
    if (strcmp(s, "*") == 0)
        return '*';
    if (strcmp(s, "/") == 0)
        return '/';
    return NUMBER;
}

void push(double num) {
    stack[sp++] = num;
}

double pop() {
    return stack[--sp];
}

int main(int argc, char const *argv[])
{
    double op2;
    char *arg;
    char op;

    while (--argc)
    {
        arg = *++argv;
        op = getop(arg);
        //printf("---%s\n", arg);
        switch (op)
        {
        case '+':
            push(pop() + pop());
            break;
        case '*':
            push(pop() * pop());
            break;
        case '-':
            op2 = pop();
            push(pop() - op2);
            break;
        case '/':
            op2 = pop();
            push(pop() / op2);
            break;
        case NUMBER:
            push(atof(arg));
            //printf("%f\n", atof(arg));
            break;
        default:
            break;
        }
    }
    printf("%.8g\n", pop());
    return 0;
}
