void reverse(char s[]) {
    int i = 0;
    while (s[i] != '\0')
    {
        ++i;
    }
    --i;
    if (s[i] == '\n')
        --i;
    int j = 0;
    while (j < i)
    {
        char temp = s[i];
        s[i] = s[j];
        s[j] = temp;
        i--;
        j++;
    }
}