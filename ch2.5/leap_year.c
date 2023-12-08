#include <stdio.h>

int main() {
    int year = 0;
    printf("plese, insert year: ");
    if (scanf("%d", &year) != 1)
        return 0;
    if ((year % 4 == 0 && year % 100 != 0) || year % 400 == 00)
        printf("%d is a leap year\n", year);
    else
        printf("%d is not a leap year\n", year);
    return 0;
}
