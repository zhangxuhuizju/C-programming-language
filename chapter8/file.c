#define NULL 0
#define EOF (-1)
#define BUFSIZ 1024
#define OPEN_MAX 20

typedef struct _iobuf{
    int cnt; //remain characters in buf
    char *ptr; //next character position
    char *base; //the position of the buffer
    //int flag; //file call mode
    int fd; //file description flag
    struct fiag_field
    {
        unsigned is_read : 1;
        unsigned is_write : 1;
        unsigned is_unbuf : 1;
        unsigned is_buf : 1;
        unsigned is_eof : 1;
        unsigned is_err : 1;
    } flag;
} FILE;

extern FILE _iob[OPEN_MAX];



enum _flags {
    _READ = 01,
    _WRITE = 02,
    _UNBUF = 04,
    _EOF = 010,
    _ERR = 020
};

int _fillbuf(FILE *);
int _flushbuf(int, FILE *);

#define stdin (&_iob[0])
#define stdout (&_iob[1])
#define stderr (&_iob[2])



#define feof(p) (((p)->flag.is_eof) == 1)
#define ferror(p) (((p)->flag.is_err) == 1)
#define fileno(p) ((p)->fd)

#define getc(p) (--(p)->cnt >= 0 \
                ? (unsigned char) *(p)->ptr++ : _fillbuf(p))

#define putc(x, p) (--(p)->cnt >= 0 \
                ? *(p)->ptr++ = (x): _flushbuf((x), p))

#define getchar() getc(stdin)
#define putchar() putc((x), stdout)

#include <fcntl.h>
#include <syscall.h>
#define PERMS 0666



FILE *fopen(char *name, char *mode) {
    int fd;
    FILE *fp;

    if (*mode != 'r' && *mode != 'w' && *mode != 'a')
        return NULL;
    for (fp = _iob; fp < _iob + OPEN_MAX; fp++)
        if (fp->flag.is_read == 0 && fp->flag.is_write == 0)
            break;
    if (fp >= _iob + OPEN_MAX)
        return NULL;  //no space to allocate
    
    if (*mode == 'w')
        fd = creat(fp, PERMS);
    else if (*mode == 'a') {
        if ((fd = open(name, O_WRONLY, 0)) == -1)
            fd = creat(fp, PERMS);
        lseek(fd, 0L, 2);  //2 represents end of the file
    } else fd = open(name, O_RDONLY, 0);
    if (fd == -1)
        return NULL;
    
    fp->fd = fd;
    fp->cnt = 0;
    fp->base = NULL;
    fp->flag.is_unbuf = 0;
    fp->flag.is_buf = 1;
    fp->flag.is_eof = 0;
    fp->flag.is_err = 0;
    if (*mode == 'r') {
        fp->flag.is_read = 1;
        fp->flag.is_write = 0;
    } else {
        fp->flag.is_read = 0;
        fp->flag.is_write = 0;
    }
}

int _fillbuf(FILE *fp) {
    int bufsize;

    if (fp->flag.is_read == 0 
        || fp->flag.is_eof == 1 
        || fp->flag.is_err == 1)
        return EOF;
    bufsize = (fp->flag.is_unbuf == 1) ? 1 : BUFSIZ;
    if (fp->base == NULL)
        if ((fp->base = (char *) malloc(bufsize)) == NULL)
            return EOF;
    fp->ptr = fp->base;
    fp->cnt = read(fp->fd, fp->ptr, bufsize);

    if(--fp->cnt < 0) {
        if(fp->cnt == -1)
            fp->flag.is_eof = 1;
        else 
            fp->flag.is_err = 1;
        fp->cnt = 0;
        return EOF;
    }
    return (unsigned char) *fp->ptr++;
}

int _flushbuf(int x, FILE *fp) {
    unsigned nc; //number of char to flush
    int bufsize;

    if (fp < _iob || fp >= _iob + OPEN_MAX)
        return EOF;
    if (fp->flag.is_write == 0 || fp->flag.is_err == 1)
        return EOF;
    bufsize = (fp->flag.is_unbuf == 1) ? 1 : BUFSIZ;
    if (fp->base == NULL) {
        if ((fp->base = (char *) malloc(bufsize)) == NULL) {
            fp->flag.is_err = 1;
            return EOF;
        }
    } else {
        nc = fp->ptr - fp->base;
        if (write(fp->fd, fp->base, nc) != nc) {
            fp->flag.is_err = 1;
            return EOF;
        }
    }
    fp->ptr = fp->base;
    *fp->ptr++ = (char) x;
    fp->cnt = bufsize - 1;
    return x;
}

int fflush(FILE *fp) {
    int rc = 0;

    if (fp < _iob || fp >= _iob + OPEN_MAX)
        return EOF;
    if (fp->flag.is_write == 1)
        rc = _flushbuf(0, fp);
    fp->ptr = fp->base;
    fp->cnt = (fp->flag.is_unbuf) ? 1 : BUFSIZ;
    return rc;
}

int fclose(FILE *fp) {
    int rc; //return code

    if ((rc = fflush(fp)) != EOF) {
        free(fp->base);
        fp->ptr = NULL;
        fp->cnt = 0;
        fp->base = NULL;
        fp->flag.is_read = fp->flag.is_write = 0;
    }
    return rc;
}

int fseek(FILE *fp, long offset, int origin) {
    unsigned nc;
    long rc = 0;

    if (fp->flag.is_read) {
        if (origin == 1)
            offset -= fp->cnt;  //chars in buf
        rc = lseek(fp->fd, offset, origin);
        fp->cnt = 0;
    } else if (fp->flag.is_write == 1) {
        if ((nc = fp->ptr - fp->base) > 0)
            if (write(fp->fd, fp->base, nc) != nc)
                rc = -1;
        if (rc != -1)
            rc = lseek(fp->fd, offset, origin);
    }
    return (rc == -1) ? -1 : 0;
}