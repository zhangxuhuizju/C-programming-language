#include <stdio.h>
#include <fcntl.h>
#include <sys/syscall.h>

int main(int argc, char const *argv[])
{
    int fp;
    void filecopy(int , int);

    if (argc == 1)
        filecopy(0, 1);   //0-stdin, 1-stdout
    else
        while (--argc > 0)
            if ((fp = open(*++argv, O_RDONLY)) == -1) {
                printf("Cannot open the file %s\n", *argv);
                return 1;
            } else {
                filecopy(fp, 1);
                close(fp);
            }
    return 0;
}

void filecopy(int ifp, int ofp) {
    int n;
    char buf[BUFSIZ];

    while ((n = read(ifp, buf, BUFSIZ)) > 0){
        if (write(ofp, buf, n) != n)
            printf ("error!");   
    }
}