static int daytab[2][13] = {
    {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30 ,31},
    {0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30 ,31}
};

/**
 * transfer yy-mm-dd to the n days in the year
 */
int day_of_year(int year, int month, int day) {
    int i, leap;
    int d = 0;
    leap = year % 4 == 0 && year % 100 != 0 || year % 400 == 0;
    if (month < 1 || month > 12)
        return -1;
    if (day < 1 || day > daytab[leap][month])
        return -1;
    for (i = 1; i < month; ++i)
        d += daytab[leap][i];
    d += day;
    return d;
}

void month_day(int year, int yearday, int *pmonth, int *pday) {
    int i, leap;
    if (year < 1) {
        *pmonth = -1;
        *pday = -1;
        return;
    }
    leap = year % 4 == 0 && year % 100 != 0 || year % 400 == 0;
    if ((leap && yearday > 366) || (!leap && yearday > 365) || yearday < 1) {
        *pmonth = -1;
        *pday = -1;
        return;
    }
    for (i = 1; yearday > daytab[leap][i]; ++i)
        yearday -= daytab[leap][i];
    *pmonth = i;
    *pday = yearday;
}