#include <stdio.h>
#include <stdlib.h>
#include <strings.h>

#define MAXLINE 100

int main(int argc, char const *argv[])
{
    FILE *fp1, *fp2;
    void filecomp(FILE *fp1, FILE *fp2);

    if (argc != 3) {
        fprintf(stderr, "comp: need two file names\n");
        exit(1);
    } else {
        if ((fp1 = fopen(*++argv, "r")) == NULL) {
            fprintf(stderr, "comp: can not open %s\n", *argv);
            exit(1);
        } else if ((fp2 = fopen(*++argv, "r")) == NULL) {
            fprintf(stderr, "comp: can not open %s\n", *argv);
            exit(1);
        } else {
            filecomp(fp1, fp2);
            fclose(fp1);
            fclose(fp2);
            exit(0);
        }
    }
    return 0;
}

void filecomp(FILE *fp1, FILE *fp2) {
    char line1[MAXLINE], line2[MAXLINE];
    char *lp1, *lp2;

    do {
        lp1 = fgets(line1, MAXLINE, fp1);
        lp2 = fgets(line2, MAXLINE, fp2);
        if (lp1 == line1 && lp2 == line2) {
            if (strcmp(line1, line2) != 0) {
                printf("first difference in line\n%s\n%s\n", line1, line2);
                lp1 = lp2 = 0;
                break;
            }
        } else if (lp1 != line1 && lp2 == line2) {
            printf("end of first file at line\n%s\n", line2);
        } else if (lp1 == line1 && lp2 != line2) {
            printf("end of second file at line\n%s\n", line1);
        }
    } while(lp1 == line1 && lp2 == line2);
}