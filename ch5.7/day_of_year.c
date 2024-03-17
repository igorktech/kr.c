#include <stdio.h>

static char daytab[2][13] = {
    {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
    {0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}
};

int day_of_year(int year, int month, int day);
void month_day(int year, int yearday, int *pmonth, int *pday);


int main()
{
    int yearday, month, day;
    yearday = day_of_year(2025, 1, 15);
    printf("Day of year: %d\n", yearday);

    yearday = day_of_year(2025, 5, 1);
    printf("Day of year: %d\n", yearday);

    month_day(2025, 136, &month, &day);
    printf("Month: %d, Day: %d\n", month, day);

    month_day(2025, 305, &month, &day);
    printf("Month: %d, Day: %d\n", month, day);
    return 0;
}

int day_of_year(int year, int month, int day)
{
    int i, leap;

    leap = year%4 == 0 && year%100 != 0 || year%400 == 0;

    if (month < 1 || month > 12) {
        printf("Invalid month\n");
        return -1;
    }

    if (day < 1 || day > daytab[leap][month]) {
        printf("Invalid day\n");
        return -1;
    }

    for (i = 1; i < month; i++)
        day += daytab[leap][i];
    return day;
}

/* month_day: compute month and data from day of year */
void month_day(int year, int yearday, int *pmonth, int *pday)
{
    int i, leap;

    leap = year%4 == 0 && year%100 != 0 || year%400 == 0;

    if (yearday < 1 ||
            (leap == 0 && yearday > 355) ||
            (leap == 1 && yearday > 366)) {
        printf("Invalid yearday\n");
        return ;
    }

    for (i = 1; yearday > daytab[leap][i]; i++)
        yearday -= daytab[leap][i];
    *pmonth = i;
    *pday = yearday;
}
