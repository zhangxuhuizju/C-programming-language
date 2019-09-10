#include <stdio.h>

int main(int argc, char const *argv[])
{
    FILE *fp;
    void filecopy(FILE *, FILE *);

    if (argc == 1)
        filecopy(stdin, stdout);
    else
        while (--argc > 0)
            if ((fp = fopen(*++argv, "r")) == NULL) {
                printf("Cannot open the file %s\n", *argv);
                return 1;
            } else {
                filecopy(fp, stdout);
                fclose(fp);
            }
    return 0;
}

void filecopy(FILE *src, FILE *dst) {
    int c;
    while ((c = getc(src)) != EOF){
        putc(c, dst);
    }
    putc('\n', dst);
}