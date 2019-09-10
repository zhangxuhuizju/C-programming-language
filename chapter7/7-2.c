#include <stdio.h>
#include <ctype.h>
#include <stdarg.h>

void minprintf(char *fmt, ...) {
    va_list para;
    char *p, *sval;
    char localfmt[100];
    int i, ival;
    double dval;
    unsigned uval;

    va_start(para, fmt);
    for (p = fmt; *p; ++p) {
        if (*p != '%') {
            putchar(*p);
            continue;
        }
        i = 0;
        localfmt[i++] = '%';
        while(*(p+1) && isalpha(*(p+1)))
            localfmt[i++] = *++p;
        localfmt[i++] = *(p+1);
        localfmt[i] = '\0';
        switch (*++p)
        {
        case 'd':
        case 'i':
            ival = va_arg(para, int);
            printf(localfmt, ival);
            break;
        case 'x':
        case 'X':
        case 'o':
        case 'u':
            uval = va_arg(para, unsigned);
            printf(localfmt, uval);
            break;
        case 'f':
            dval = va_arg(para,double);
            printf(localfmt, dval);
            break;
        case 's':
            sval = va_arg(para, char *);
            printf(localfmt, sval);
            break;
        default:
            printf(localfmt);
            break;
        }
    }
    va_end(para);
}