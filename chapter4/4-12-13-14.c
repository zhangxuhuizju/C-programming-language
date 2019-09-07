#include <math.h>

/**
 * convert n to characters in s
 */
void itoa(int n, char s[]) {
    static int i;

    if (n / 10)
        itoa(n/10, n);
    else {
        i = 0;
        if (n < 0)
            s[i++] = '-';
    }
    s[i++] = abs(n) % 10 + '0';
    s[i] = '\0';
}

#include <string.h>
void reverse(char s[]) {
    void reverser(char s[], int i, int len);

    reverser(s, 0, strlen(s));
}

void reverser(char s[], int i, int len) {
    int c, j;

    j = len - (i + 1);
    if (i < j) {
        c = s[i];
        s[i] = s[j];
        s[j] = c;
        reverser(s, ++i, len);
    }
}

#define swap(t, x, y) { t _z;\
                        _z = y;\
                        y = x;\
                        x = _z;}