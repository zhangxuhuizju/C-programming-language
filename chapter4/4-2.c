#include <ctype.h>

/**
 * convert string to double
 */
double atof(char s[]) {
    double val, power;
    int exp, i, sign;
    for (i = 0; isspace(s[i]); ++i);

    if (s[i] == '+') {
        sign = 1;
        i++;
    } else if (s[i] == '-') {
        sign = -1;
        i++;
    } else {
        sign = 1;
    }

    for(val = 0.0; isdigit(s[i]); ++i)
        val = val * 10.0 + (s[i] - '0');
    
    if (s[i] == '.')
        i++;
    for (power = 1.0; isdigit(s[i]); ++i) {
        val = 10.0*val + (s[i]-'0');
        power *= 10;
    }

    val = sign * val / power;

    if (s[i] == 'e' || s[i] == 'E') {
        i++;
        if (s[i] == '+') {
            sign = 1;
            i++;
        } else if (s[i] == '-') {
            sign = -1;
            i++;
        } else sign = 1;
        for (exp = 0; isdigit(s[i]); ++i)
            exp = exp * 10 + (s[i] - '0');
        if (sign == 1) {
            while (exp-- > 0){
                val *= 10;
            }
        }   
        else{
            while (exp-- > 0){
                val /= 10;
            }
        }
    }
    return val;
}