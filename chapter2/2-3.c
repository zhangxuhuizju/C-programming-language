#include <stdio.h>

int getNum(char c) {
    if (c >= '0' && c <= '9')
        return c - '0';
    else if (c >= 'a' && c <= 'f')
        return c - 'a' + 10;
    else if (c >= 'A' && c <= 'F')
        return c - 'A' + 10;
    else printf("error!!!");
    return -1;
}

int htoi(char s[]) {
    int result = 0;
    int weights = 1;
    int i = 0;
    while (s[i] != '\0')
    {
        i++;
    }
    for (--i; i >= 2; --i) {
        result += weights * getNum(s[i]);
        weights *= 16;
    }
    return result;
}

int main(int argc, char const *argv[])
{
    printf("%d", htoi("0xaa"));
    return 0;
}
