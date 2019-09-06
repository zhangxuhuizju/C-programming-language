#include <stdio.h>

#define MAXHISH 15 /*max length of histogram */
#define MAXWORD 11 /*max length of a word */
#define IN 1
#define OUT 0

int main(int argc, char const *argv[])
{
    int c ,i , number_of_char, state;
    int len;  //length of each bar
    int overflow; //number of overflow words
    int word_len[MAXWORD]; //word length counters

    state = OUT;
    number_of_char = 0;
    overflow = 0;

    for (i = 0; i < MAXWORD; ++i)
        word_len[i] = 0;
    while ((c = getchar()) != EOF)
    {
        if (c == ' ' || c == '\t' || c == '\n') {
            state = OUT;
            printf ("%d \n", number_of_char);
            if (number_of_char > 0)
                if (number_of_char < MAXWORD)
                    ++word_len[number_of_char];
                else
                    ++overflow;
            number_of_char = 0;
        } else if (state == OUT) {
            state = IN;
            number_of_char = 1;
        } else 
            ++number_of_char;
    }

    for (i = 1; i < MAXWORD; ++i) {
        printf("%d - %d : \n", i, word_len[i]);

        if (word_len[i] > 0) {
            len = word_len[i];
            while (len--)
            {
                putchar('*');
            }
            putchar('\n');
        }
    }

    if (overflow > 0)
        printf("There are %d words overflow!!!", overflow);
    return 0;
}
