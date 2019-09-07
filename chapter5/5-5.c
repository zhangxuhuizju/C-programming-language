/**
 * strncpy: copy at most n characters from t to s
 */
void strncpy(char *s, char *t, int n) {
    while (*t && n-- > 0)
        *s++ = *t++;
    if (n > 0)
        *s = '\0';
}

/**
 * concat at most n characters from t to s
 */
void strncat(char *s, char *t, int n) {
    while(*s++);
    while(*s++ = *t++ && n--);
    if (n > 0)
        *s = '\0';
    /**
     * another method:
     * strncpy(s + strlen(s), t, n);
     */
}

/**
 * compare at most n characters of s with t
 */
int strncmp(char *s, char *t, int n) {
    for (; *s == *t; s++, t++)
        if(*s == '\0' || --n <= 0)
            return 0;
    return *s - *t;
}