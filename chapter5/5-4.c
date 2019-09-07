/**
 * return 1 if string t occurs at the end of s
 */
int strend(char *s, char *t) {
    char *bs = s;
    char *bt = t;
    while(*s++);
    while(*t++);

    for (;*s == *t; s--, t--)
        if (t == bt || s == bs)
            break;
    if(*s == *t && t == bt && *s != '\0')
        return 1;
    else return 0;
}