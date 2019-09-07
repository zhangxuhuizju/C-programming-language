/**
 * expand newline and tab into visible sequences
 */
void escape(char s[], char t[]) {
    int i = 0, j = 0;
    while (t[i] != '\0')
    {
        switch (t[i])
        {
        case '\n':
            s[j++] = '\\';
            s[j++] = 'n';
            break;
        case '\t':
            s[j++] = '\\';
            s[j++] = 't';
            break;
        default:
            s[j++] = t[i];
            break;
        }
        ++i;
    }
    s[j] = '\0';
}

/**
 * convert escape sequences into real characters
 */
void unescape(char s[], char t[]) {
    int i = 0, j = 0;
    while(t[i] != '\0') {
        if (t[i] != '\\')
            s[j++] = t[i];
        switch (t[++i])
        {
        case 'n':
            s[j++] = '\n';
            break;
        case 't':
            s[j++] = '\t';
            break;
        default:
            s[j++] = '\\';
            s[j++] = t[i];
            break;
        }
        i++;
    }
}